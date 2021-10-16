/**
 * THIS SHOULD BE THE LAST FILE TO LOAD.  
 * 
 * This contains the Arduino required setup() and loop() functions.  These functions depend upon everything else already being loaded, 
 *   so should be last in the compile process.
 * 
 */

/*
 * Objects that we'll need.  They'll auto construct, but the pattern we're using will require them to have their init() method called.
 */
Eeprom eeprom;
Configuration configuration;
Joystick joystick;
Steering steering;
Throttle throttle;
RemoteControl remoteControl;
Logger logger;

boolean isLogging = false;
boolean isConfiguring = false;

/*
 * Interrupt request handlers.  The Arduino environment appears to require these to be global methods with no parms, so defining them here.
 *   Really just wrappers to call the proper RemoteControl methods.  
 */
 void handleRCSteeringInterrupt() { remoteControl.steeringIRQHandler(); }
 void handleRCThrottleInterrupt() { remoteControl.throttleIRQHandler(); }
 void handleJoystickSteeringInterrupt() { joystick.steeringIRQHandler(); }
 void handleJoystickThrottleInterrupt() { joystick.throttleIRQHandler(); }

/*
 * Now a couple of variables that help us do a bit of logging
 */
boolean rcInControl = false;
boolean joystickInControl = false;
boolean badStartMessageDisplayed = false;

/*
 * Arduino defined setup function.  Automatically run once at restart of the device.
 */
void setup() {
  // set up the logger
  logger.init(LOGGER_UPDATE_TIME, &eeprom, &configuration, &joystick, &remoteControl, &steering, &throttle);

  eeprom.init();
  logger.addLogLine("Eeprom initialized");
    
  configuration.init(&eeprom, PIN_MAX_SPEED);
  logger.addLogLine("configuration initialized");
    
  joystick.init(PIN_JOYSTICK_STEERING, PIN_JOYSTICK_THROTTLE);
  logger.addLogLine("joystick initialized");

  if (configuration.useRc()) {
    remoteControl.init(PIN_RC_STEERING, PIN_RC_THROTTLE);
    logger.addLogLine("remote control initialized");
  }

  throttle.init(PIN_THROTTLE_DIRECTION_LEFT, PIN_THROTTLE_PWM_LEFT, PIN_THROTTLE_DIRECTION_RIGHT, PIN_THROTTLE_PWM_RIGHT);
  logger.addLogLine("throttle initialized");
  
  steering.init(PIN_STEERING_DIRECTION, PIN_STEERING_PWM, PIN_STEERING_POSITION);
  logger.addLogLine("steering initialized");

  // Set steering limits from configuration
  steering.setSteeringCenterScaled(configuration.getSteeringCenter());
  steering.setSteeringMinScaled(configuration.getSteeringMin());
  steering.setSteeringMaxScaled(configuration.getSteeringMax());

  // Set Joystick configuration
  joystick.setXAxisRange(configuration.getJoystickSteeringMin(), configuration.getJoystickSteeringCenter(), configuration.getJoystickSteeringMax());
  joystick.setYAxisRange(configuration.getJoystickThrottleMin(), configuration.getJoystickThrottleCenter(), configuration.getJoystickThrottleMax());
  joystick.setInvertXAxis(configuration.getInvertJoystickX());
  joystick.setInvertYAxis(configuration.getInvertJoystickY());

  // Set RC/Parental Control Configuration
  remoteControl.setSteeringRange(configuration.getRcSteeringMin(), configuration.getRcSteeringCenter(), configuration.getRcSteeringMax());
  remoteControl.setThrottleRange(configuration.getRcThrottleMin(), configuration.getRcThrottleCenter(), configuration.getRcThrottleMax());

  // set up the interrupt handlers
  if (configuration.useRc()) {
    attachInterrupt(digitalPinToInterrupt(PIN_RC_STEERING), &handleRCSteeringInterrupt, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_RC_THROTTLE), &handleRCThrottleInterrupt, CHANGE);    
  }

  if (configuration.usePwmJoystickX()) {
    attachInterrupt(digitalPinToInterrupt(PIN_JOYSTICK_STEERING), &handleJoystickSteeringInterrupt, CHANGE);    
    joystick.setUseSteeringPwm(true);
  } else {
    joystick.setUseSteeringPwm(false);    
  }

  if (configuration.usePwmJoystickY()) {
    attachInterrupt(digitalPinToInterrupt(PIN_JOYSTICK_THROTTLE), &handleJoystickThrottleInterrupt, CHANGE);        
    joystick.setUseThrottlePwm(true);
  } else {
    joystick.setUseThrottlePwm(false);    
  }

}

/*
 * Arduino defined loop function.  Automatically run repeatedly (after setup).
 */
void loop() {
  if (!isConfiguring && !isLogging && Serial) {
    // We have detected a Serial connection, check to see if we want logging or configuration
    Serial.println("Press c to configure or any other key to run with logging");
    throttle.setThrottle(0);
    steering.forceStop();

    while (!isConfiguring && !isLogging) {
      if (Serial.available() > 0) {
        if (Serial.read() == 'c') {
          Serial.println("Start Configuring");
          isConfiguring = true;
        } else {
          Serial.println("Start Logging");
          isLogging = true;
        }
      }
    }

    // Read and discard other input. This will also include the carriage return
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
  
  if (isConfiguring) {
    // When configuration is active, the car cannot be driven.
    throttle.setThrottle(0);
    steering.forceStop();

    configuration.configureCar();
    // We will never return from this method.
    // The microcontroller will have to be reset for the car to begin running normally again
  } else if (configuration.useRc() && remoteControl.isBadRcStart()) {
    // A bad RC start is when the throttle trigger on the RC remote is pulled 
    // when the remote is turned on. This creates a situation where the 
    // failsafe setting used if the RC remote is turned off or loses connection,
    // will cause the car will drive at whatever speed was set when the remote was switched on.
    // To prevent this from happening, we disable the car if this is detected.
    // A full power cycle is required to break out of this condition.
    logger.addLogLine("Bad Start");
    throttle.setThrottle(0);
    steering.forceStop();
  } else {
    // recalculate the scaled RC throttle and steering values
    // this is necessary to know whether or not the RC is active
    if (configuration.useRc()) {
      remoteControl.updateThrottleScaled();
      remoteControl.updateSteeringScaled();
    }
    
    // Is the parent overriding and taking control?
    if (configuration.useRc() && remoteControl.isActive()) {
      
      // Yep, the parent has taken over ... parent inputs only
      if (joystickInControl) {
        logger.addLogLine("RC has gone active, taking over from Joystick");
        joystickInControl=false;
        rcInControl=true;
      }
  
      // set the inputs from the RC
      steering.setSteeringPosition(remoteControl.getSteeringScaled());
      throttle.setThrottle(remoteControl.getThrottleScaled());
    } else {
      
      // Nope... the parent isn't controlling
      // check to see if the joystick active (e.g. has it centered at least once?)
      if (joystick.isActive()) {  
        // Yeah!  The kid is in control!
        if (rcInControl) {
          logger.addLogLine("Joystick is now in control, taking over from RC");
          joystickInControl=true;
          rcInControl=false;
        }

        // set the inputs from the Joystick
        // we need to get the speed multiplier each time,
        // because the speed potentiometer can be turned at any time to adjust the max speed
        steering.setSteeringPosition(joystick.getXAxisScaled());
        throttle.setThrottle(joystick.getYAxisScaled() * configuration.getSpeedMultiplier());
      } else {
  
        // Whoops ... we got here becuase neither control is active.  Nobody is going anywhere until that changes.
        logger.addLogLine("RC in not active, Joystick is not active");
      }
    }      
  }

  // When Configuration is active we use the Serial output for logging message directly from that module
  if (isLogging) {
    // Only write the log messages if there is an active serial connection
    logger.writeLog();
  }

  delay(LOOP_DELAY_MILLIS);
}

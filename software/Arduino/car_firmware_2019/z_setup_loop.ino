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
Bluetooth bluetooth;
Configuration configuration;
Joystick joystick;
SteeringPotGoButton potGo;
Steering steering;
Throttle throttle;
RemoteControl remoteControl;
ButtonDrive buttonDrive;
Logger logger;

/*
 * Interrupt request handlers.  The Arduino environment appears to require these to be global methods with no parms, so defining them here.
 *   Really just wrappers to call the proper RemoteControl methods.  
 */
 void handleRCSteeringInterrupt() {remoteControl.steeringIRQHandler();}
 void handleRCThrottleInterrupt() {remoteControl.throttleIRQHandler();}

/*
 * Now a couple of variables that help us do a bit of logging
 */
boolean rcInControl = false;
boolean joystickInControl = false;
boolean bluetoothInitialized = false;

/*
 * Arduino defined setup function.  Automatically run once at restart of the device.
 */
void setup() {
  // set up the logger
  logger.init(LOGGER_UPDATE_TIME, &eeprom, &bluetooth, &configuration, &joystick, &potGo, &remoteControl, &steering, &throttle, &buttonDrive);

  eeprom.init();
  logger.addLogLine("eeprom initialized");

  bluetooth.init(PIN_ENABLE_BLUETOOTH_BUTTON, &eeprom);
  logger.addLogLine("bluetooth button initialized");
  
  configuration.init(&eeprom);
  logger.addLogLine("configuration initialized");
    
  if (configuration.useSteeringPotentiometerAndGoButton()) {
    joystick.init(PIN_JOYSTICK_STEERING, PIN_JOYSTICK_THROTTLE);
    logger.addLogLine("joystick initialized");
  }

  if (configuration.useSteeringPotentiometerAndGoButton()) {
    potGo.init(PIN_STEERING_POTENTIONMETER, PIN_GO_BUTTON, PIN_REVERSE_SWITCH);
    logger.addLogLine("steering potentiometer and go button initialized");
  }

  if (configuration.useRc()) {
    remoteControl.init(PIN_RC_STEERING, PIN_RC_THROTTLE);
    logger.addLogLine("remote control initialized");
  }

  if (configuration.usePushButtonDrive()) {
    buttonDrive.init(PIN_BUTTON_LEFT, PIN_BUTTON_RIGHT, PIN_BUTTON_STRAIGHT, PIN_REVERSE_SWITCH);
    logger.addLogLine("drive buttons initialized");
  }

  throttle.init(PIN_THROTTLE_FORWARD, PIN_THROTTLE_REVERSE, PIN_THROTTLE_SPEED);
  logger.addLogLine("throttle initialized");
  
  steering.init(PIN_STEERING_LEFT, PIN_STEERING_RIGHT, PIN_STEERING_ENABLE, PIN_STEERING_POSITION);
  logger.addLogLine("steering initialized");


  // set up the interrupt handlers
  attachInterrupt(digitalPinToInterrupt(PIN_RC_STEERING), &handleRCSteeringInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_RC_THROTTLE), &handleRCThrottleInterrupt, CHANGE);
  logger.addLogLine("interrupts attached");

  // Set steering limits from configuration
  steering.setSteeringCenterScaled(configuration.getSteeringCenter());
  steering.setSteeringMinScaled(configuration.getSteeringMin());
  steering.setSteeringMaxScaled(configuration.getSteeringMax());
}

/*
 * Arduino defined loop function.  Automatically run repeatedly (after setup).
 */
void loop() {

  bluetooth.processEnableButton();

  if (bluetooth.isActive()) {
    // When Bluetooth is active, the car cannot be driven.
    // The only way to deactivate Bluetooth is to turn off the power
    throttle.setThrottle(0);

    if (bluetoothInitialized) {
      bluetooth.processBluetooth();
    } else {
      bluetooth.initBluetooth();
      bluetoothInitialized = true;
    }
  } else if (configuration.useRc() && remoteControl.isBadRcStart()) {
    // TODO: Play a sound to indicate that the car did not start properly
    logger.addLogLine("RC did not start up properly do NOT run the car");
    throttle.setThrottle(0);
  } else {
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
  
    } else if (configuration.useSteeringPotentiometerAndGoButton()) {
        if (rcInControl) {
          logger.addLogLine("Steering Potentiometer and Go Button are now in control, taking over from RC");
          joystickInControl=true;
          rcInControl=false;
        }
  
        // set the inputs from the steering potentiometer and go button
        steering.setSteeringPosition(potGo.getXAxisScaled());
        throttle.setThrottle(potGo.getYAxisScaled()*configuration.getSpeedMultiplier());
    } else if (configuration.usePushButtonDrive()) {
      steering.setSteeringPosition(buttonDrive.getXAxisScaled());
      throttle.setThrottle(buttonDrive.getYAxisScaled() * configuration.getSpeedMultiplier());
    } else {
      
      // Nope... the parent isn't controlling
      // check to see if the joystick active (e.g. has it centered at least once?)
      if (joystick.isActive()) {
        // TODO move configuration settings so they aren't in the main loop
        joystick.setInvertXAxis(configuration.getInvertJoystickX());
        joystick.setInvertYAxis(configuration.getInvertJoystickY());
  
        // Yeah!  The kid is in control!
        if (rcInControl) {
          logger.addLogLine("Joystick is now in control, taking over from RC");
          joystickInControl=true;
          rcInControl=false;
        }
  
        // set the inputs from the Joystick
        steering.setSteeringPosition(joystick.getXAxisScaled());
        throttle.setThrottle(joystick.getYAxisScaled()*configuration.getSpeedMultiplier());
      } else {
  
        // Whoops ... we got here becuase neither control is active.  Nobody is going anywhere until that changes.
        logger.addLogLine("RC in not active, Joystick is not active");
      }
    }      
  }

  // When Bluetooth is active we use the Serial output for logging message directly from that module
  // In addition, we need full speed processing so we don't miss any message fragments so the delay is eliminated.
  if (!bluetooth.isActive()) {
    // OK, now let's see if it's time to write out the log
    logger.writeLog();

    // now delay for the loop delay time... we really don't want to try and run this loop at full CPU speed
    delay(LOOP_DELAY_MILLIS);
  }
}

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
DIPSwitches dips;
Configuration configuration;
Joystick joystick;
SteeringPotGoButton potGo;
Steering steering;
Throttle throttle;
RemoteControl remoteControl;
Logger logger;
TFTDisplay tftDisplay;
AdminScreenManager admin;

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


/*
 * Arduino defined setup function.  Automatically run once at restart of the device.
 */
void setup() {
  // set up the logger
  logger.init(LOGGER_UPDATE_TIME, &dips, &configuration, &joystick, &potGo, &remoteControl, &steering, &throttle, &tftDisplay);

  // initialize everything with the correct pins
  joystick.init(PIN_JOYSTICK_STEERING, PIN_JOYSTICK_THROTTLE);
  logger.addLogLine("joystick initialized");

  potGo.init(PIN_STEERING_POTENTIONMETER, PIN_GO_BUTTON, PIN_REVERSE_SWITCH);
  logger.addLogLine("steering potentiometer and go button initialized");

  throttle.init(PIN_THROTTLE_FORWARD, PIN_THROTTLE_REVERSE, PIN_THROTTLE_SPEED);
  logger.addLogLine("throttle initialized");
  
  steering.init(PIN_STEERING_LEFT, PIN_STEERING_RIGHT, PIN_STEERING_ENABLE, PIN_STEERING_POSITION);
  logger.addLogLine("steering initialized");
  
  remoteControl.init(PIN_RC_STEERING, PIN_RC_THROTTLE); 
  logger.addLogLine("remote control initialized"); 

  dips.init(DIP_SWITCH_1, DIP_SWITCH_2, DIP_SWITCH_3, DIP_SWITCH_4, DIP_SWITCH_5, DIP_SWITCH_6);
  logger.addLogLine("dips initialized"); 

  configuration.init(&dips);
  logger.addLogLine("configuration initialized");

  tftDisplay.init(PIN_TFT_CS, PIN_TFT_DC, PIN_TFT_MOSI, PIN_TFT_CLK, PIN_TFT_RST, PIN_TFT_MISO);
  logger.addLogLine("TFT display initialized");

  admin.init(ADMIN_UPDATE_TIME, &dips, &configuration, &joystick, &potGo, &remoteControl, &steering, &throttle, &tftDisplay);
  logger.addLogLine("Admin Manager initialized");

  // set up the interrupt handlers
  attachInterrupt(digitalPinToInterrupt(PIN_RC_STEERING), &handleRCSteeringInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_RC_THROTTLE), &handleRCThrottleInterrupt, CHANGE);
  logger.addLogLine("interrupts attached");
  
}

/*
 * Arduino defined loop function.  Automatically run repeatedly (after setup).
 */
void loop() {

  if (remoteControl.isBadRcStart()) {
    // TODO: Play a sound to indicate that the car did not start properly
    logger.addLogLine("RC did not start up properly do NOT run the car");
    throttle.setThrottle(0);
  } else {
    // Is the parent overriding and taking control?
    if (remoteControl.isActive()) {
      
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
    } else {
      
      // Nope... the parent isn't controlling
      // check to see if the joystick active (e.g. has it centered at least once?)
      if (joystick.isActive()) {
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

  // OK, now let's see if it's time to write out the log
  logger.writeLog();

  admin.update();
  
  // now delay for the loop delay time... we really don't want to try and run this loop at full CPU speed
  delay(LOOP_DELAY_MILLIS);
}

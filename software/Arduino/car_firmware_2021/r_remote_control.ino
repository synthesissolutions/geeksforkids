/**
 * RemoteControl Class
 * 
 * This class serves to be the interface to the to the parental remote control unit
 */
class RemoteControl {
  private:

    int pinRCSteering;
    int pinRCThrottle;

    // initial values of -1 ... used to help figure out if we've seen a 0 signal yet
    int steeringScaled = -1;
    int throttleScaled = -1;

    // Track the first 10 PWM signal readings and mark a bad start if any of those readings
    // are outside of a small dead zone
    boolean badControlStart = false;
    unsigned long throttlePWMStart[10];
    int throttlePWMStartIndex = 0;
    unsigned long steeringPWMStart[10];
    int steeringPWMStartIndex = 0;

    boolean steeringSignalHigh;
    unsigned long steeringPulseStart;
    unsigned long steeringPWM;
    boolean throttleSignalHigh;
    unsigned long throttlePulseStart;
    unsigned long throttlePWM;

    unsigned long lastSignificantInputMillis = 0;

    // settting default values here ... being a little lazy by defaulting from constants.  
    unsigned int throttleRcMin = THROTTLE_RC_MIN;
    unsigned int throttleRcCenter = THROTTLE_RC_CENTER;
    unsigned int throttleRcMax = THROTTLE_RC_MAX;
    unsigned int steeringRcMin = STEERING_RC_MIN;
    unsigned int steeringRcCenter = STEERING_RC_CENTER;
    unsigned int steeringRcMax = STEERING_RC_MAX;
    unsigned int rcLimit = RC_LIMIT;
    unsigned int overrideTimeout = RC_OVERRIDE_TIMEOUT;        
    int steeringDeadzoneLow = RC_STEERING_DEADZONE_LOW;
    int steeringDeadzoneHigh = RC_STEERING_DEADZONE_HIGH;
    int throttleDeadzoneLow = RC_THROTTLE_DEADZONE_LOW;
    int throttleDeadzoneHigh = RC_THROTTLE_DEADZONE_HIGH; 

    // direction inversion if necessary
    boolean  invertSteering = RC_INVERT_STEERING;
    boolean  invertThrottle = RC_INVERT_THROTTLE;

    boolean hasCentered = false;
  

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).
    RemoteControl() {
    }

    // initial setup
    void init(int steeringPin, int throttlePin) {
      pinRCSteering = steeringPin;
      pinRCThrottle = throttlePin;

      // set the pins with pullup resistors enabled
      pinMode(pinRCSteering, INPUT_PULLUP); 
      pinMode(pinRCThrottle, INPUT_PULLUP);       
    }

    /*
     * get the current steering position (scaled units -100 to 100)
     */
    int getSteeringScaled() {
      return steeringScaled;
    }

    /*
     * get the current throttle position (scaled units -100 to 100)
     */
    int getThrottleScaled() {  
      return throttleScaled;
    }

    boolean isBadRcStart() {
      return badControlStart;
    }
    
    /*
     * Is the remote control "hot" ... meaning does the parent have control.  This also accounts for the timeout... e.g. has the parent had control recently.
     */
    boolean isActive() {
       
      /*
       * If we've not yet centered the controls, then we're not active yet
       */
      if (!hasCentered) {
        if (steeringScaled==0 && throttleScaled==0) {
          
          // controls are centered, OK to go on
          hasCentered=true;
          
        } else {

          // controls have not yet centered, we're not active!
          return false;
          
        }
      }

      /* 
       *  we're active if we've had a significant input recently enough
       */
      if (millis()-lastSignificantInputMillis < overrideTimeout) {
        return true;
      }
      
      return false;
    }

    void getStatus(char * status) {
      sprintf(status, "[RemoteControl] throttlePWM:%lu throttleScaled:%i%s steeringPWM:%lu steeringScaled:%i%s isActive:%s Bad Start:%s PWM Th Start: ",
        throttlePWM,
        throttleScaled,
        invertThrottle ? "true" : "false",
        steeringPWM,
        steeringScaled,
        invertSteering ? "true" : "false",
        isActive() ? "true" : "false",
        badControlStart ? "true" : "false");

        //TODO!  Still need to convert the PWM array

//      ret.concat(String(" PWM Th Start: "));
//
//      for (int i = 0; i < 10; i++) {
//        ret.concat(throttlePWMStart[i]);
//        ret.concat(String(" ") );
//      }
//
//      ret.concat(String(" PWM St Start: "));
//
//      for (int i = 0; i < 10; i++) {
//        ret.concat(steeringPWMStart[i]);
//        ret.concat(String(" ") );
//      }
//
//      return ret;
    }

    /* 
     * Handler for IRQ updates for steering.
     * 
     * NOTE: This code is considered critical (should not be interrupted), but does not disable interrupts.  This is because we assume it's being 
     *       called in an IRQ handler and therefore interrupts are already disabled until we exit.  We are doing the math to figure out the pulse width
     *       and the scaled signal here, which is based on the assumption that the board in use (e.g. teensy) is much faster in clock speed than the 
     *       resolution of the PWM signal.  
     */
    void steeringIRQHandler() {

      // which state are we handling
      if(digitalRead(pinRCSteering) == 1){
        // rising signal
        if (!steeringSignalHigh) {

          // record when the pulse started
          steeringPulseStart = micros();

          // set us up to look for the pulse end
          steeringSignalHigh = true;
        }
        
      } else {

        // falling signal
        if (steeringSignalHigh) {
          // and we haven't seen this pulse drop previously

          // calculate the pulse width in microseconds
          steeringPWM = micros()-steeringPulseStart;

          if (steeringPWMStartIndex < 10) {
            steeringPWMStart[steeringPWMStartIndex] = steeringPWM;
            steeringPWMStartIndex++;

            // CRITICAL NOTE: If the RC steering is not centered when it is turned on
            // then when it is turned off it will return a non-centered result.
            // !!!!! IMPORTANT !!!!! This means that when the RC remote is turned off in this
            // case and the car is still it will turn the wheel in that direction
            // and prevent the child from controlling via the joystick
//            if (steeringPWM < throttleDeadzoneLow || steeringPWM > throttleDeadzoneHigh) {
            if (steeringPWM < 1400 || steeringPWM > 1600) {
              badControlStart = true;
            }
          }

          // is the pulse width in the expected range?
          if ((steeringPWM > 0) && (steeringPWM < rcLimit)) {
            
            // we have a complete pulse ... calculate the signal
            // just a linear scaling of PWM min/max to -100 - 100
            steeringScaled = constrain(map(steeringPWM,steeringRcMin,steeringRcMax,-100,100),-100,100);
            
            // invert if necessary
            if (invertSteering) {
              steeringScaled = -steeringScaled;
            }

            // are we in the deadzone?
            if (steeringScaled > steeringDeadzoneLow && steeringScaled < steeringDeadzoneHigh) {
              // yes ... apply the deadzone
              steeringScaled = 0;
            } else {
              // no... leave the value alone, but record that we had a significant input
              lastSignificantInputMillis = millis();
            }
            
          }
          steeringSignalHigh = false;
        }

      }
      
    }
   
    /* 
     * Handler for IRQ updates for throttle.
     * 
     * NOTE: This code is considered critical (should not be interrupted), but does not disable interrupts.  This is because we assume it's being 
     *       called in an IRQ handler and therefore interrupts are already disabled until we exit.  We are doing the math to figure out the pulse width
     *       and the scaled signal here, which is based on the assumption that the board in use (e.g. teensy) is much faster in clock speed than the 
     *       resolution of the PWM signal.  
     */
    void throttleIRQHandler() {
      
      // which state are we handling
      if(digitalRead(pinRCThrottle) == 1){
        // rising signal
        if (!throttleSignalHigh) {
          
          // record when the pulse started
          throttlePulseStart = micros();

          // set us up to look for the pulse end
          throttleSignalHigh = true;
        }
        
      } else {

        // falling signal
        if (throttleSignalHigh) {
          // and we haven't seen this pulse drop previously

          // calculate the pulse width in microseconds
          throttlePWM = micros()-throttlePulseStart;

          if (throttlePWMStartIndex < 10) {
            throttlePWMStart[throttlePWMStartIndex] = throttlePWM;
            throttlePWMStartIndex++;

            // CRITICAL NOTE: If the RC throttle is not centered when it is turned on
            // then when it is turned off it will return a non-centered result.
            // !!!!! IMPORTANT !!!!! This means that when the RC remote is turned off in this
            // case and the car is still it will drive in that direction with the child having
            // no control via the joystick.
//            if (throttlePWM < throttleDeadzoneLow || throttlePWM > throttleDeadzoneHigh) {
            if (throttlePWM < 1400 || throttlePWM > 1600) {
              badControlStart = true;
            }
          }

          // is the pulse width in the expected range?
          if ((throttlePWM > 0) && (throttlePWM < rcLimit)) {
            
            // we have a good and complete pulse ... calculate the signal
            // the throttle is not symmetrical with a min 1200 and a max of 2000, but a center of 1500
            // so we need to calculate the throttle in each direction indpendently
            if (throttlePWM < throttleRcCenter) {
              throttleScaled = constrain(map(throttleRcCenter-throttlePWM,0,throttleRcCenter-throttleRcMin,0,-100),-100,0);
            } else {
              throttleScaled = constrain(map(throttlePWM-throttleRcCenter,0,throttleRcMax-throttleRcCenter,0,100),0,100);
            }

            // invert if necessary
            if (invertThrottle) {
              throttleScaled = -throttleScaled;
            }
            
            // are we in the deadzone?
            if (throttleScaled > throttleDeadzoneLow && throttleScaled < throttleDeadzoneHigh) {
              // yes ... apply the deadzone
              throttleScaled = 0;
            } else {
              // no... leave the value alone, but record that we had a significant input
              lastSignificantInputMillis = millis();
            }
          }

          // now set us up to look for the next pulse
          throttleSignalHigh = false;
        }

      }
      
    }
  
};

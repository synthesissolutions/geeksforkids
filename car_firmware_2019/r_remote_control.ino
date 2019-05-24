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

    boolean steeringSignalHigh;
    unsigned long steeringPulseStart;
    unsigned long steeringPWM;
    boolean throttleSignalHigh;
    unsigned long throttlePulseStart;
    unsigned long throttlePWM;

    unsigned long lastSignificantInputMillis = 0;

    // settting default values here ... being a little lazy by defaulting from constants.  
    unsigned int rcMin = RC_MIN;
    unsigned int rcMax = RC_MAX;
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


    String getStatus() {
      String ret = String("[RemoteControl] ");
      ret.concat(String("throttlePWM:"));ret.concat(throttlePWM);
      ret.concat(String(" throttleScaled:"));ret.concat(throttleScaled);if (invertThrottle) ret.concat("(inverted)");
      ret.concat(String(" steeringPWM:"));ret.concat(steeringPWM);
      ret.concat(String(" steeringScaled:"));ret.concat(steeringScaled);if (invertSteering) ret.concat("(inverted)");
      ret.concat(String(" isActive:"));ret.concat(isActive());
      return ret;
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

          // is the pulse width in the expected range?
          if ((steeringPWM > 0) && (steeringPWM < rcLimit)) {
            
            // we have a complete pulse ... calculate the signal
            // just a linear scaling of 1000micros-2000micros to -100 - 100
            steeringScaled = constrain(map(steeringPWM,1000,2000,-100,100),-100,100);
            
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

          // is the pulse width in the expected range?
          if ((throttlePWM > 0) && (throttlePWM < rcLimit)) {
            
            // we have a good and complete pulse ... calculate the signal
            // just a linear scaling of 1000micros-2000micros to -100 - 100
            throttleScaled = constrain(map(throttlePWM,1000,2000,-100,100),-100,100);

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

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

    unsigned long lastSignificantInputMillis = 0;
    unsigned long lastThrottleInputMillis = 0;
    unsigned long lastSteeringInputMillis = 0;

    boolean hasCentered = false;
  

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).
    RemoteControl() {
    }

    // initial setup
    void init(int steeringPin, int throttlePin) {
      pinRCSteering = steeringPin;
      pinRCThrottle = throttlePin;  
    }

    int getSteeringRaw() {
      return analogRead(pinRCSteering);      
    }
    
    /*
     * get the current steering position (scaled units -100 to 100)
     */
    int getSteeringScaled() {
      int steeringRaw = getSteeringRaw();

      if ((steeringRaw < STEERING_RC_MIN - 5) || (steeringRaw > STEERING_RC_MAX + 5)) {
        lastSteeringInputMillis = 0;
        return 0;
      }
      
      steeringScaled = constrain(map(steeringRaw, STEERING_RC_MIN, STEERING_RC_MAX, -100, 100), -100, 100);

      if (steeringScaled >= RC_STEERING_DEADZONE_LOW && steeringScaled <= RC_STEERING_DEADZONE_HIGH) {
        lastSteeringInputMillis = 0;
        return 0;
      }

      if (lastSteeringInputMillis == 0) {
        lastSteeringInputMillis = millis();
      }

      if (millis() - lastSteeringInputMillis < RC_INPUT_DELAY) {
        return 0;
      }
      
      lastSignificantInputMillis = millis();
      
      return steeringScaled;
    }

    int getThrottleRaw() {
      return analogRead(pinRCThrottle);      
    }
    
    /*
     * get the current throttle position (scaled units -100 to 100)
     */
    int getThrottleScaled() {  
      int throttleRaw = getThrottleRaw();

      if ((throttleRaw < THROTTLE_RC_MIN - 5) || (throttleRaw > THROTTLE_RC_MAX + 5)) {
        lastSteeringInputMillis = 0;
        return 0;
      }

      throttleScaled = constrain(map(throttleRaw, THROTTLE_RC_MIN, THROTTLE_RC_MAX, -100, 100), -100, 100);

      if (throttleScaled >= RC_THROTTLE_DEADZONE_LOW && throttleScaled <= RC_THROTTLE_DEADZONE_HIGH) {
        lastThrottleInputMillis = 0;
        return 0;
      }
      
      if (lastThrottleInputMillis == 0) {
        lastThrottleInputMillis = millis();
      }

      if (millis() - lastThrottleInputMillis < RC_INPUT_DELAY) {
        return 0;
      }

      lastSignificantInputMillis = millis();

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
        if (getSteeringScaled() == 0 && getThrottleScaled() == 0) {
          
          // controls are centered, OK to go on
          hasCentered=true;
          
        } else {

          // controls have not yet centered, we're not active!
          return false;
          
        }
      }

      // Call get scaled methods to update input millis
      getSteeringScaled();
      getThrottleScaled();
      
      /* 
       *  we're active if we've had a significant input recently enough
       */
      if (millis()-lastSignificantInputMillis < RC_OVERRIDE_TIMEOUT) {
        return true;
      }
      
      return false;
    }

    void getStatus(char * status) {
      int testValue = 500;
      
      sprintf(status, "[RemoteControl] throttleRaw:%lu throttleScaled:%i steeringRaw:%lu steeringScaled:%i isActive:%s Bad Start:%s PWM Th Start: ",
        getThrottleRaw(),
        getThrottleScaled(),
        getSteeringRaw(),
        getSteeringScaled(),
        isActive() ? "true" : "false",
        badControlStart ? "true" : "false");
    }  
};

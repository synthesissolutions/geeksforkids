 /**
 * RemoteControl Class
 * 
 * This class serves to be the interface to the to the parental remote control unit
 */

// The number of throttle and steering readings to average to smooth results
#define RC_THROTTLE_READINGS 15
#define RC_STEERING_READINGS 15

// The number of readings to take to check for unusual values that would indicate
// a bad RC start. Typically caused by someone holding the throttle in while turning on the remote.
#define RC_START_LENGTH 10

class RemoteControl {
  private:

    int pinRCSteering;
    int pinRCThrottle;

    // initial values of -1 ... used to help figure out if we've seen a 0 signal yet
    int steeringScaled = -1;
    int throttleScaled = -1;

    unsigned long lastSignificantInputMillis = 0;
    unsigned long lastThrottleInputMillis = 0;
    unsigned long lastSteeringInputMillis = 0;


    int throttleReadings[RC_THROTTLE_READINGS];
    int throttleIndex = 0;

    int steeringReadings[RC_STEERING_READINGS];
    int steeringIndex = 0;
    
    boolean hasCentered = false;
  

  public: 
    // Track the first few signal readings and mark a bad start if any of those readings
    // are outside of a small dead zone
    boolean badControlStart = false;
    int throttleStart[RC_START_LENGTH];
    int throttleStartIndex = 0;
    int steeringStart[RC_START_LENGTH];
    int steeringStartIndex = 0;

    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).
    RemoteControl() {
    }

    // initial setup
    void init(int steeringPin, int throttlePin) {
      pinRCSteering = steeringPin;
      pinRCThrottle = throttlePin;  
    }

    int getSteeringRaw() {
      int newSteering = analogRead(pinRCSteering);

      steeringIndex++;
      if (steeringIndex >= RC_STEERING_READINGS) {
        steeringIndex = 0;
      }

      steeringReadings[steeringIndex] = newSteering;
      
      int total = 0;

      for (int i = 0; i < RC_STEERING_READINGS; i++) {
        total += steeringReadings[i];
      }
      
      return total / RC_STEERING_READINGS;
    }
    
    /*
     * get the current steering position (scaled units -100 to 100)
     */
    int getSteeringScaled() {
      int steeringRaw = getSteeringRaw();

      // Anything outside of the expected range will be ignored
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
      int newThrottle = analogRead(pinRCThrottle);

      throttleIndex++;
      if (throttleIndex >= RC_THROTTLE_READINGS) {
        throttleIndex = 0;
      }

      throttleReadings[throttleIndex] = newThrottle;
      
      int total = 0;

      for (int i = 0; i < RC_THROTTLE_READINGS; i++) {
        total += throttleReadings[i];
      }
      
      return total / RC_THROTTLE_READINGS;
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

    boolean rcStartComplete() {
      return throttleStartIndex >= RC_START_LENGTH;
    }

    boolean isBadThrottleStartValue(int value) {
      return (value > 10) && (value < THROTTLE_RC_CENTER - 5) || (value > THROTTLE_RC_CENTER + 5);
    }

    boolean isBadSteeringStartValue(int value) {
      return (value > 10) && (value < STEERING_RC_CENTER - 5) || (value > STEERING_RC_CENTER + 5);      
    }
    
    void recordRCStartValue() {
      // Don't start checking for a bad start immediately, give it a brief time to settle
      if (millis() < 100) {
        return;
      }
      
      int newThrottle = analogRead(pinRCThrottle);
      int newSteering = analogRead(pinRCSteering);

      // Until the RC remote is turned on, the values should be 0 or very close to it
      // We don't want to start checking for a bad start until the RC is turned on.
      if (newThrottle < 5 && newSteering < 5) {
        return;
      }

      if (throttleStartIndex < RC_START_LENGTH) {
        throttleStart[throttleStartIndex] = newThrottle;
        throttleStartIndex++;

        if (isBadThrottleStartValue(newThrottle)) {
          //badControlStart = true;
        }
      }

      if (steeringStartIndex < RC_START_LENGTH) {
        steeringStart[steeringStartIndex] = newSteering;
        steeringStartIndex++;

        if (isBadSteeringStartValue(newSteering)) {
          //badControlStart = true;
        }
      }
    }
    
    /*
     * Is the remote control "hot" ... meaning does the parent have control.  This also accounts for the timeout... e.g. has the parent had control recently.
     */
    boolean isActive() {
      if (!rcStartComplete()) {
        recordRCStartValue();
        return false;
      }

      if (badControlStart) {
        return false;
      }
       
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

    void getBadStartData(char *buffer) {
      //sprintf(buffer, "%i %i %i %i %i %i %i %i %i %i", throttleStart[0], throttleStart[1], throttleStart[2], throttleStart[3], throttleStart[4], throttleStart[5], throttleStart[6], throttleStart[7], throttleStart[8], throttleStart[9]);
      buffer = "Test";
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

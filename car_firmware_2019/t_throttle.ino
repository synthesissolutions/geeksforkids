/**
 * Throttle class
 * 
 * This class serves to be the actual interface to driving the throttle for the car.  The intent of this class is to 
 *   allow for a throttle position to be set in scaled units (-100 to 100), and this class will take care of making the 
 *   changes to the steering as appropriate.
 *   
 *   A key feature of this class is the idea of moving the throttle to a new value over time (rather than an imeediate change), 
 *     to help minimize jerky behavior.  
 */

class Throttle {

  private:

    int forwardPin;
    int reversePin;
    int speedPin;

    int throttleMin = THROTTLE_PWM_MIN;
    int throttleMax = THROTTLE_PWM_MAX;
    unsigned long targetThrottleUpdateMillis = THROTTLE_UPDATE_MILLIS;
    float throttleChangeRate = THROTTLE_CHANGE_RATE;

    int targetThrottleScaled = 0;
    float currentThrottleScaled = 0;
    int currentPwmOut = 0;

    unsigned long lastThrottleUpdateMillis = 0;

  public: 

    // default constructor that really does nothing
    Throttle() {
    }

    // initial setup
    void init(int fwdPin, int revPin, int spdPin) {
      // set the pins
      forwardPin = fwdPin;
      reversePin = revPin;
      speedPin = spdPin;

      // set the pin modes
      pinMode(forwardPin, OUTPUT);
      pinMode(reversePin, OUTPUT);
      pinMode(speedPin, OUTPUT);

      // and do an initial update to get the timer kicked off
      updateThrottle();
    }

    /*
     * set the scaled throttle target.  Expected range is -100 to 100, 0=stopped
     */
    void setThrottle(int target) {
      if (target < -100) target = -100;
      if (target > 100) target = 100;
      
      this->targetThrottleScaled = target;

      updateThrottle();
    }

    /*
     * gets the current throttle
     */
    int getCurrentThrottleScaled() {
      return this->currentThrottleScaled;
    }

    /*
     * gets the target throttle
     */
    int getTargetThrottleScaled() {
      return this->targetThrottleScaled;
    }

    /*
     * gets the target throttle
     */
    int getCurrentPWMOut() {
      return this->currentPwmOut;
    }
    
    /* 
     * updateThrottle
     * 
     * This is usually not necessary to call as it will get called by setThrottleScaled().  But it is safe to call as necessary.
     */
    void updateThrottle() {

      // check to see if it's time yet to actually update.  If not, don't do anything.
      if (millis() - lastThrottleUpdateMillis < targetThrottleUpdateMillis) {
        return;
      }

      // Looks like it's time to update the throttle.  Now ... figure out the new current throttle should be.
      if (lastThrottleUpdateMillis == 0) {
        // Case 1: just starting up.  Set the throttle to 0, and get set up for further running
        currentThrottleScaled = 0;
        
      } else {
        // Case 2: not starting up, so let's do some work
        
        // figure how how much to change the throttle based upon the rate and the amount of time that has elapsed
        int throttleDelta = float(millis() - lastThrottleUpdateMillis) * throttleChangeRate / 1000.;
         
        // Figure out what to do with the current throttle (which direction do we apply the delta)
        /*
         * NOTE: This is the simplest application of a throttle rate change that is possible.  Nothing fancy, just decide in which direction to apply the 
         *        throttle change and apply it.  No special logic about stopping or anything.
         */
        if (targetThrottleScaled < currentThrottleScaled) {
          // calling for the throttle to be reduced in value
          currentThrottleScaled -= throttleDelta;        
        } else if (targetThrottleScaled > currentThrottleScaled) {
          // calling for the throttle to be increased in value
          currentThrottleScaled += throttleDelta;
        }
        
      }

      // figure out the throttle pwm setting (ignoring the direction)
      currentPwmOut = map(abs(currentThrottleScaled), 0.0, 100.0, THROTTLE_PWM_MIN, THROTTLE_PWM_MAX);

      // now set the direction and the throttle
      if (int(currentThrottleScaled)==0) {
        // stop
        digitalWrite(PIN_THROTTLE_FORWARD, LOW);
        digitalWrite(PIN_THROTTLE_REVERSE, LOW);
        analogWrite(PIN_THROTTLE_SPEED, THROTTLE_PWM_MIN); 
               
      } else if (currentThrottleScaled<0) {
        //reverse
        digitalWrite(PIN_THROTTLE_FORWARD, LOW);
        digitalWrite(PIN_THROTTLE_REVERSE, HIGH);
        analogWrite(PIN_THROTTLE_SPEED, currentPwmOut);   
          
      } else if (currentThrottleScaled>0) {
        //forward
        digitalWrite(PIN_THROTTLE_FORWARD, HIGH);
        digitalWrite(PIN_THROTTLE_REVERSE, LOW);
        analogWrite(PIN_THROTTLE_SPEED, currentPwmOut);       
      }

      lastThrottleUpdateMillis = millis();
       
    }

    String getStatus() {
      String ret = String("[Throttle] ");
      ret.concat(String("target:"));ret.concat(targetThrottleScaled);
      ret.concat(String(" current:"));ret.concat(currentThrottleScaled);
      ret.concat(String(" PWM:"));ret.concat(currentPwmOut);
      return ret;
    }

    String getMinimalStatus() {
      String ret = String("Th ");
      ret.concat(String("t:"));ret.concat(targetThrottleScaled);
      ret.concat(String(" c:"));ret.concat(currentThrottleScaled);
      ret.concat(String(" PWM:"));ret.concat(currentPwmOut);
      return ret;
    }
};

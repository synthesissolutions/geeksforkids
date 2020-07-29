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
 #include <Servo.h>

class Throttle {

  private:

    Servo throttleMotorController;
    
    int pwmPin;
    
    unsigned long targetThrottleUpdateMillis = THROTTLE_UPDATE_MILLIS;
    float throttleChangeRate = THROTTLE_CHANGE_RATE;

    int throttleTargetScaled = 0;
    float currentThrottleScaled = 0;
    int currentPwmOut = 1500;

    unsigned long lastThrottleUpdateMillis = 0;

  public: 

    // default constructor that really does nothing
    Throttle() {
    }

    // initial setup
    void init(int pwmMotorControllerPin) {
      // set the pins
      pwmPin = pwmMotorControllerPin;
      throttleMotorController.attach(pwmPin);

      // and do an initial update to get the timer kicked off
      updateThrottle();
    }

    /*
     * set the scaled throttle target.  Expected range is -100 to 100, 0=stopped
     */
    void setThrottle(int target) {
      if (target < -100) target = -100;
      if (target > 100) target = 100;
      
      this->throttleTargetScaled = target;

      updateThrottle();
      
    }

    /*
     * gets the current throttle
     */
    int getCurrentThrottleScaled() {
      return this->currentThrottleScaled;
    }

    /* 
     * updateThrottle
     * 
     * This is usually not necessary to call as it will get called by setThrottleScaled().  But it is safe to call as necessary.
     */
    void updateThrottle() {

      // check to see if it's time yet to actually update.  If not, don't do anything.
      if (millis() - lastThrottleUpdateMillis < targetThrottleUpdateMillis) {
        // Note ... abs was used just in case we had a rollover in the millis() timer
        return;
      }

      // Looks like it's time to update the throttle.  Now ... figure out the new current throttle should be.
      if (lastThrottleUpdateMillis == 0) {
        // Case 1: just starting up.  Set the throttle to 0, and get set up for further running
        currentThrottleScaled = 0;
        
      } else {
        // Case 2: not staring up, so let's do some work
        
        // figure how how much to change the throttle based upon the rate and the amount of time that has elapsed
        int throttleDelta = float(millis() - lastThrottleUpdateMillis) * throttleChangeRate / 1000.;
         
        // Figure out what to do with the current throttle (which direction do we apply the delta)
        /*
         * NOTE: This is the simplest application of a throttle rate change that is possible.  Nothing fancy, just decide in which direction to apply the 
         *        throttle change and apply it.  No special logic about stopping or anything.
         */
        if (throttleTargetScaled < currentThrottleScaled) {
          // calling for the throttle to be reduced in value
          currentThrottleScaled -= throttleDelta;        
        } else if (throttleTargetScaled > currentThrottleScaled) {
          // calling for the throttle to be increased in value
          currentThrottleScaled += throttleDelta;
        }
        
      }

      // figure out the throttle pwm setting (ignoring the direction)
      currentPwmOut = map(currentThrottleScaled, -100.0, 100.0, THROTTLE_PWM_MIN, THROTTLE_PWM_MAX);
      
      throttleMotorController.writeMicroseconds(currentPwmOut);

      lastThrottleUpdateMillis = millis();
       
    }

    String getStatus() {
      String ret = String("[Throttle] ");
      ret.concat(String("target:"));ret.concat(throttleTargetScaled);
      ret.concat(String(" current:"));ret.concat(currentThrottleScaled);
      ret.concat(String(" PWM:"));ret.concat(currentPwmOut);
      return ret;
    }
};

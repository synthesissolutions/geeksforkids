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
 
//TODO Talk to William to Update Motor driving code correctly from new board changes

class Throttle {

  private:

    int frontForwardPin;
    int frontReversePin;
    int rearForwardPin;
    int rearReversePin;

    int throttleTargetScaled = 0;
    float currentThrottleScaled = 0;
    int currentPwmOut = 0;

    unsigned long lastThrottleUpdateMillis = 0;
  public: 

    // default constructor that really does nothing
    Throttle() {
    }

    // Used during a bad start scenario or when the car is being configured
    void forceStop() {
      // Set both Pins HIGH for brake, LOW for coast
        digitalWrite(frontForwardPin, HIGH);
        digitalWrite(frontReversePin, HIGH);
        digitalWrite(rearForwardPin, HIGH);
        digitalWrite(rearReversePin, HIGH);
    }
    
    // initial setup
    void init(int dirLeftPin, int pwmLeftPin, int dirRightPin, int pwmRightPin) {
      // set the pins
      frontForwardPin = dirLeftPin;
      frontReversePin = pwmLeftPin;
      rearForwardPin = dirRightPin;
      rearReversePin = pwmRightPin;

      // set the pin modes
      pinMode(frontForwardPin, OUTPUT);
      pinMode(frontReversePin, OUTPUT);
      pinMode(rearForwardPin, OUTPUT);
      pinMode(rearReversePin, OUTPUT);

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
      if (millis() - lastThrottleUpdateMillis < THROTTLE_UPDATE_MILLIS) {
        // Note ... abs was used just in case we had a rollover in the millis() timer
        return;
      }

      // Looks like it's time to update the throttle.  Now ... figure out the new current throttle should be.
      if (lastThrottleUpdateMillis == 0 || millis() - lastThrottleUpdateMillis > THROTTLE_UPDATE_MILLIS * 3) {
        // Case 1: just starting up.  Set the throttle to 0, and get set up for further running
        //         or we have a very large delta - this happens when there is no drive system and the remote is used for the first time
        currentThrottleScaled = 0;
      } else {
        // Case 2: not staring up, so let's do some work
        
        // figure how how much to change the throttle based upon the rate and the amount of time that has elapsed
        int throttleDelta = float(millis() - lastThrottleUpdateMillis) * THROTTLE_CHANGE_RATE / 1000.;
         
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
      currentPwmOut = map(abs(currentThrottleScaled), 0.0, 100.0, THROTTLE_PWM_MIN, THROTTLE_PWM_MAX);

      // now set the direction and the throttle
      if (int(currentThrottleScaled)==0) {
        // stop
        // TODO decide on brake vs. coast behavior
        // TODO decide whether or not to use the switch on dash for brake vs. coast
        digitalWrite(frontForwardPin, HIGH);
        digitalWrite(frontReversePin, HIGH); 
        digitalWrite(rearForwardPin, HIGH);
        digitalWrite(rearReversePin, HIGH);                
      } else if (currentThrottleScaled<0) {
        //reverse
        digitalWrite(frontForwardPin, LOW);
        analogWrite(frontReversePin, currentPwmOut);   
        digitalWrite(rearForwardPin, LOW);
        analogWrite(rearReversePin, currentPwmOut);             
      } else if (currentThrottleScaled>0) {
        //forward
        analogWrite(frontForwardPin, currentPwmOut);       
        digitalWrite(frontReversePin, LOW);
        analogWrite(rearForwardPin, currentPwmOut);       
        digitalWrite(rearReversePin, LOW);
      }

      lastThrottleUpdateMillis = millis();
    }

    void getStatus(char * status) {
      sprintf(status, "[Throttle] target:%i current:%f PWM:%i",
        throttleTargetScaled,
        currentThrottleScaled,
        currentPwmOut);
    }
};

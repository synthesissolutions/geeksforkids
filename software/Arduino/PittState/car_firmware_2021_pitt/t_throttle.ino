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
#include <Adafruit_MCP4728.h>
Adafruit_MCP4728 mcp;

#define MIN_STOP_TIME 1000
#define DAC_MIN 750
#define DAC_MAX 2000

// Define this here for now, need to refactor once things are clearer
#define REVERSE_OUTPUT_PIN  20

class Throttle {

  private:
    // throttle is not ready until the currentThrottleScaled has reached 0
    // this prevents the car from jerking forward as soon as it is turned on
    // it also allows time for the joystick and PWM readings to settle
    boolean throttleReady = false;
    
    long timeStopped = 0;
    boolean isMovingForward = true;
    boolean isStopped = true;

    int throttleTargetScaled = -1;
    float currentThrottleScaled = 0;
    int currentDacOut = DAC_MIN;
    int throttleDelta = 0;

    unsigned long tempMillis = 0;

    unsigned long lastThrottleUpdateMillis = 0;

  public: 

    // default constructor that really does nothing
    Throttle() {
    }

    // initial setup
    void init() {
      // Try to initialize!
      if (!mcp.begin()) {
        Serial.println("Failed to find MCP4728 chip");
        while (1) {
          delay(10);
        }
      }

      pinMode(REVERSE_OUTPUT_PIN, OUTPUT);
      digitalWrite(REVERSE_OUTPUT_PIN, HIGH);
  
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
      tempMillis = millis();
              
      if (tempMillis < 1000) {
        // Don't do anything for the first second
        // give various systems time to settle
        mcp.setChannelValue(MCP4728_CHANNEL_A, DAC_MIN);
        return;
      }
      // Looks like it's time to update the throttle.  Now ... figure out the new current throttle should be.
      if (lastThrottleUpdateMillis == 0) {
        // Case 1: just starting up.  Set the throttle to 0, and get set up for further running
        currentThrottleScaled = 0;        
      } else {
        // Case 2: not staring up, so let's do some work
        
        // figure how how much to change the throttle based upon the rate and the amount of time that has elapsed
        throttleDelta = float(tempMillis - lastThrottleUpdateMillis) * THROTTLE_CHANGE_RATE / 1000.;

        // Figure out what to do with the current throttle (which direction do we apply the delta)
        /*
         * NOTE: This is the simplest application of a throttle rate change that is possible.  Nothing fancy, just decide in which direction to apply the 
         *        throttle change and apply it.  No special logic about stopping or anything.
         */
        if (throttleDelta > 10) {
          // Weird case when the car first starts, the millis() reading is way off
          // this causes the delta to be very large and creates bad current target values
          currentThrottleScaled = 0;
        } else if (throttleTargetScaled < currentThrottleScaled) {
          // calling for the throttle to be reduced in value
          currentThrottleScaled -= throttleDelta;        
        } else if (throttleTargetScaled > currentThrottleScaled) {
          // calling for the throttle to be increased in value
          currentThrottleScaled += throttleDelta;
        }
      }


      // now set the direction and the throttle
      if (!throttleReady) {
        // Ignore all input until throttle target reaches 0
        // readings when the car first starts up are not as reliable
        if (throttleTargetScaled == 0) {
          throttleReady = true;
        }

        mcp.setChannelValue(MCP4728_CHANNEL_A, DAC_MIN);
      } else if (floatNearZero(currentThrottleScaled, 2.0)) {
        // stop
        if (!isStopped) {
          isStopped = true;
          timeStopped = millis();
        }
        mcp.setChannelValue(MCP4728_CHANNEL_A, DAC_MIN);
      } else {
        // figure out the throttle DAC setting (ignoring the direction)
        currentDacOut = map(abs(currentThrottleScaled), 0.0, 100.0, DAC_MIN, DAC_MAX);

        if (currentThrottleScaled < 0) {
          //reverse
          if (!isMovingForward) {
            // already moving backard, OK to keep moving
            mcp.setChannelValue(MCP4728_CHANNEL_A, currentDacOut);
            isStopped = false;
          } else if (isStopped && (tempMillis - MIN_STOP_TIME > timeStopped)) {
            // we have been stopped long enough to switch directions
            digitalWrite(REVERSE_OUTPUT_PIN, LOW);
            mcp.setChannelValue(MCP4728_CHANNEL_A, currentDacOut);
            isStopped = false;
            isMovingForward = false;
          } else {
            // we have not been stopped long enough to switch directions
            mcp.setChannelValue(MCP4728_CHANNEL_A, DAC_MIN);
          }
        } else if (currentThrottleScaled > 0) {
          //forward
          if (isMovingForward) {
            // already moving forward, OK to keep moving
            mcp.setChannelValue(MCP4728_CHANNEL_A, currentDacOut);
            isStopped = false;
          } else if (isStopped && (tempMillis - MIN_STOP_TIME > timeStopped)) {
            // we have been stopped long enough to switch directions
            digitalWrite(REVERSE_OUTPUT_PIN, HIGH);
            mcp.setChannelValue(MCP4728_CHANNEL_A, currentDacOut);
            isStopped = false;
            isMovingForward = true;
          } else {
            // we have not been stopped long enough to switch directions
            mcp.setChannelValue(MCP4728_CHANNEL_A, DAC_MIN);
          }
        }
      }

      lastThrottleUpdateMillis = millis();
    }

    boolean floatNearZero(float value, float delta) {
      return (abs(value) - delta) < 0.0;
    }
    
    void getStatus(char * status) {
      sprintf(status, "[Throttle] target:%i current:%f DAC:%i Delta:%i",
        throttleTargetScaled,
        currentThrottleScaled,
        currentDacOut,
        throttleDelta);
    }
};

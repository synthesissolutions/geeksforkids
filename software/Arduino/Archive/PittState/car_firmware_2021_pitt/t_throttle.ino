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

#define DAC_OFF 0
#define DAC_MIN 1250
#define DAC_MAX 2000

// Define this here for now, need to refactor once things are clearer
#define REVERSE_PIN   15

#define BRAKE_PIN     14
#define BRAKE_DELAY_MILLISECONDS  100


class Throttle {

  private:
    // throttle is not ready until the currentThrottleScaled has reached 0
    // this prevents the car from jerking forward as soon as it is turned on
    // it also allows time for the joystick and PWM readings to settle
    boolean throttleReady = false;

    boolean isMovingForward = true;
    boolean isBraking = false;
    boolean isStopped = false;
    long brakingStartTimeMillis = 0;
    
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
      pinMode(BRAKE_PIN, OUTPUT);
            
      // Try to initialize!
      if (!mcp.begin()) {
        Serial.println("Failed to find MCP4728 chip");
        while (1) {
          delay(10);
        }
      }

      pinMode(REVERSE_PIN, OUTPUT);
      // Signal HIGH for forward and LOW for reverse
      digitalWrite(REVERSE_PIN, HIGH);

      mcp.setChannelValue(MCP4728_CHANNEL_A, DAC_OFF);
      mcp.setChannelValue(MCP4728_CHANNEL_B, DAC_OFF);
      mcp.setChannelValue(MCP4728_CHANNEL_C, DAC_OFF);
      mcp.setChannelValue(MCP4728_CHANNEL_D, DAC_OFF);
      
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
   
    void engageBrakes() {
      isStopped = true;
      digitalWrite(BRAKE_PIN, LOW);
    }

    void releaseBrakes() {
      isStopped = false;
      digitalWrite(BRAKE_PIN, HIGH);
    }

    void moveForward(int dacOut) {

      digitalWrite(REVERSE_PIN, HIGH);

      mcp.setChannelValue(MCP4728_CHANNEL_A, dacOut);
      mcp.setChannelValue(MCP4728_CHANNEL_B, dacOut);
      mcp.setChannelValue(MCP4728_CHANNEL_C, dacOut);
      mcp.setChannelValue(MCP4728_CHANNEL_D, dacOut);
    }

    void moveBackward(int dacOut) {

      digitalWrite(REVERSE_PIN, LOW);

      mcp.setChannelValue(MCP4728_CHANNEL_A, dacOut);
      mcp.setChannelValue(MCP4728_CHANNEL_B, dacOut);
      mcp.setChannelValue(MCP4728_CHANNEL_C, dacOut);
      mcp.setChannelValue(MCP4728_CHANNEL_D, dacOut);
    }
    
    void stopBrushlessMotors() {
      mcp.setChannelValue(MCP4728_CHANNEL_A, DAC_OFF);
      mcp.setChannelValue(MCP4728_CHANNEL_B, DAC_OFF);
      mcp.setChannelValue(MCP4728_CHANNEL_C, DAC_OFF);
      mcp.setChannelValue(MCP4728_CHANNEL_D, DAC_OFF);
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
        stopBrushlessMotors();
        engageBrakes();
        return;
      }

      // First time through, set the last throttle update and return so ramp up/down code works properly
      if (lastThrottleUpdateMillis == 0) {
        currentThrottleScaled = 0;
        lastThrottleUpdateMillis = millis();

        return;
      }

      // Check to make sure the throttle target has reached 0 before continuing
      // this is to prevent a start with the throttle already engaged or a case
      // where the control system is failing and always giving a throttle value
      // The throttle must be at 0 before regular driving can begin
      if (!throttleReady) {
        if (throttleTargetScaled == 0) {
          throttleReady = true;
        } else {
          stopBrushlessMotors();
          return;
        }
      }

      // don't engage the brakes immediately give the car a chance to slow down first
      if (isBraking ) {
        if (millis() - brakingStartTimeMillis > BRAKE_DELAY_MILLISECONDS) {
          engageBrakes();
        }
      }
      
      // All of the preliminaries are over and we can now start handling throttle and braking normally
      // The basics are:
        // When the throttle is engaged, we start to release the brakes
        // When is not engaged, we star the braking process
        // We can't immediately switch directions, we will force the car to stop first
        // If braking is not full engaged (limit switch pressed) and we start moving again,
          // we only need to disengage the brakes the same amount of time they were engaged
        // If we are tyring to move in the same direction as before braking starting, we can 
          // immediately start moving while the brake is being released
        // Otherwise, we need the brakes to fully engage before we can start moving in the other direction
      
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

      // now set the direction and the throttle
      if (floatNearZero(currentThrottleScaled, 2.0)) {
        // Stop
        if (!isBraking) {
          isBraking = true;
          brakingStartTimeMillis = millis();
        }
        
        stopBrushlessMotors();
      } else {
        // figure out the throttle DAC setting (ignoring the direction)
        currentDacOut = map(abs(currentThrottleScaled), 0.0, 100.0, DAC_MIN, DAC_MAX);

        // TODO: The moving forward and moving backward code is basically the same
        // except for setting the isMovingForward variable and the reverse pin
        // should combine them into one condition more elegantly
        if (currentThrottleScaled < 0) {
          //reverse
          if (isStopped) {
            // release the brakes
            releaseBrakes();
            isBraking = false;

            // ok to switch directions
            moveBackward(currentDacOut);
            isMovingForward = false;
          } else if (!isMovingForward) {
            // already moving backard, OK to keep moving
            moveBackward(currentDacOut);
            releaseBrakes();
            isBraking = false;
          } else {
            // moving forward and we haven't stopped yet
            // keep waiting until we stop to reverse direction
            if (!isBraking) {
              brakingStartTimeMillis = millis();
              isBraking = true;
            }
            stopBrushlessMotors();
          }
        } else if (currentThrottleScaled > 0) {
          //forward
          if (isStopped) {
            // start releasing the brake
            releaseBrakes();
            isBraking = false;

            // ok to switch directions
            moveForward(currentDacOut);
            isMovingForward = true;
          } else if (isMovingForward) {
            // already moving forward, OK to keep moving
            moveForward(currentDacOut);
            releaseBrakes();
            isBraking = false;
          } else {
            // moving backward and we haven't stopped yet
            // keep waiting until we stop to reverse direction
            if (!isBraking) {
              brakingStartTimeMillis = millis();
              isBraking = true;
            }
            stopBrushlessMotors();
          }
        }
      }
        
      lastThrottleUpdateMillis = millis();
    }

    boolean floatNearZero(float value, float delta) {
      return (abs(value) - delta) < 0.0;
    }
    
    void getStatus(char * status) {
        sprintf(status, "[Throttle] target:%i current:%f DAC:%i isBraking: %s isStopping: %s isMovingForward: %s",
          throttleTargetScaled,
          currentThrottleScaled,
          currentDacOut,
          isBraking ? "true" : "false",
          isStopped ? "true" : "false",
          isMovingForward ? "true" : "false");
    }
};

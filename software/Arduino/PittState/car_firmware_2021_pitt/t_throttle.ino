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
#define DAC_MIN 750
#define DAC_MAX 2000

// Define this here for now, need to refactor once things are clearer
#define REVERSE_OUTPUT_PIN      20
#define BRAKE_LIMIT_SWITCH_PIN  21
#define BRAKE_ENGAGE_PWM        127
#define BRAKE_RELEASE_PWM       254
#define BRAKE_MOTOR_OFF_PWM     0

#define BRAKE_RELEASE_MILLISECONDS  350
#define MAX_BRAKE_TIME_MILLISECONDS 700

class Throttle {

  private:
    // throttle is not ready until the currentThrottleScaled has reached 0
    // this prevents the car from jerking forward as soon as it is turned on
    // it also allows time for the joystick and PWM readings to settle
    boolean throttleReady = false;

    int directionBrakePin;
    int speedPwmBrakePin;

    // When braking is activated move the motor forward until the limit switch is pressed
    // or it took too long to activate the switch. If it takes too long, shutdown the throttle
    // permanently and display error message in logs.
    // When moving after braking has started, the brake must be released. There is no limit switch
    // in this direction so we just release for X milliseconds. If we start braking and then the
    // throttle is told to move, we reverse the braking motion by the same number of milliseconds
    // that we traveled during the initial braking. If we start moving after the limit switch is
    // activated, we reverse the braking motion by the full number of milliseconds.
    boolean isMovingForward = true;
    boolean criticalBrakingFailure = false;
    boolean isBraking = false;
    boolean isBrakeReleasing = false;
    long brakingStartTimeMillis = 0;
    long brakeReleaseStartTimeMillis = 0;

    // Brakes are initialized after the car starts
    // all brakes are moved to the their limit switch
    // If all brakes reach their limit switch in the alotted time,
    // then brakesInitialized will be set to true
    // If during the initialization, one of the brakes does not trigger
    // it's limit switch in the alotted time, a critical braking failure is set.
    boolean brakesInitialized = false;
    
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
    void init(int dirBrakePin, int pwmBrakePin) {
      directionBrakePin = dirBrakePin;
      speedPwmBrakePin = pwmBrakePin;

      pinMode(directionBrakePin, OUTPUT);
      pinMode(speedPwmBrakePin, OUTPUT);
      
      // Try to initialize!
      if (!mcp.begin()) {
        Serial.println("Failed to find MCP4728 chip");
        while (1) {
          delay(10);
        }
      }

      pinMode(REVERSE_OUTPUT_PIN, OUTPUT);
      digitalWrite(REVERSE_OUTPUT_PIN, HIGH);
      pinMode(BRAKE_LIMIT_SWITCH_PIN, INPUT_PULLUP);

      digitalWrite(directionBrakePin, HIGH);
      analogWrite(speedPwmBrakePin, BRAKE_MOTOR_OFF_PWM);

      mcp.setChannelValue(MCP4728_CHANNEL_A, DAC_OFF);
      
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

    boolean isStopped() {
      // The limit switch is Grounded when triggered, so the logic is inverted
      return !digitalRead(BRAKE_LIMIT_SWITCH_PIN);
    }

    void engageBrakes() {
      digitalWrite(directionBrakePin, HIGH);
      analogWrite(speedPwmBrakePin, BRAKE_ENGAGE_PWM);
    }

    void releaseBrakes() {
      digitalWrite(directionBrakePin, LOW);
      analogWrite(speedPwmBrakePin, BRAKE_RELEASE_PWM);
    }

    void stopBrakingMotor() {
      digitalWrite(directionBrakePin, HIGH);
      analogWrite(speedPwmBrakePin, BRAKE_MOTOR_OFF_PWM);
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

      if (criticalBrakingFailure) {
        mcp.setChannelValue(MCP4728_CHANNEL_A, DAC_MIN);
        return;
      }

      // Handle brake initializaiton
      if (!brakesInitialized) {
        if (brakingStartTimeMillis == 0) {
          // start brake initialization
          brakingStartTimeMillis = millis();
          if (isStopped()) {
            // Are the brakes already fully engaged? If so, nothing more to do
            brakesInitialized = true;
          } else {
            // Start the braking motors
            engageBrakes();
          }
        } else {
          // check for successful brake initialization (limit switch pressed), in progress (time limit not expired),
          // or critical braking failure (time limit is expired)
          if (isStopped()) {
            // limit switch pressed
            // stop motors and record successful initialization
            stopBrakingMotor();
            brakesInitialized = true;
          } else if (tempMillis - MAX_BRAKE_TIME_MILLISECONDS < brakingStartTimeMillis) {
            // still braking, nothing to do
          } else {
            // initialization took to long, a critical braking failure has occured
            stopBrakingMotor();
            brakesInitialized = true;
            criticalBrakingFailure = true;
          }
        }

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
          mcp.setChannelValue(MCP4728_CHANNEL_A, DAC_OFF);
          return;
        }
      }

      // Check to see if we need to stop braking either because we have hit the limit switch
      // or because we have failed to trigger the limit switch in time
      if (isBraking) {
        if (isStopped()) {
          stopBrakingMotor();
          isBraking = false;
        } else if (tempMillis - MAX_BRAKE_TIME_MILLISECONDS > brakingStartTimeMillis) {
          stopBrakingMotor();
          mcp.setChannelValue(MCP4728_CHANNEL_A, DAC_OFF); // shouldn't be on, but just in case
          criticalBrakeFailure = true;

          return;
        }
      }
      
      // Check to see if we need to stop releasing the brake
      if (isBrakeReleasing && (tempMillis - BRAKE_RELEASE_MILLISECONDS > brakeReleaseStartTimeMillis)) {
        stopBrakingMotor();
        isBrakeReleasing = false;
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
        if (!isStopped() && !isBraking) {
          // we need to start braking now
          engageBrakes();
          isBraking = true;
          brakingStartTimeMillis = millis();
        }
        
        mcp.setChannelValue(MCP4728_CHANNEL_A, DAC_OFF);
      } else {
        // figure out the throttle DAC setting (ignoring the direction)
        currentDacOut = map(abs(currentThrottleScaled), 0.0, 100.0, DAC_MIN, DAC_MAX);

        if (currentThrottleScaled < 0) {
          //reverse
          if (isStopped()) {
            // start releasing the brake
            releaseBrakes();
            isBrakeReleasing = true;
            isBraking = false;
            brakeReleaseStartTimeMillis = tempMillis;

            // ok to switch directions
            digitalWrite(REVERSE_OUTPUT_PIN, LOW);
            mcp.setChannelValue(MCP4728_CHANNEL_A, currentDacOut);
            isMovingForward = false;
          } else if (!isMovingForward) {
            // already moving backard, OK to keep moving
            mcp.setChannelValue(MCP4728_CHANNEL_A, currentDacOut);

            if (isBraking) {
              // if we were starting to brake, need to release the brake
              isBraking = false;
              releaseBrakes();
              isBrakeReleasing = true;
              // Adjust the brake release start time by half of the time already spent braking
              // this assumes that braking is running half as fast as releasing
              // need to do real math here for other scenarios
              brakeReleaseStartTimeMillis = tempMillis - ((tempMillis - brakingStartTimeMillis) / 2);
            }
          } else {
            // moving forward and we haven't stopped yet
            // keep waiting until we stop to reverse direction
            mcp.setChannelValue(MCP4728_CHANNEL_A, DAC_OFF);
          }
        } else if (currentThrottleScaled > 0) {
          //forward
          if (isStopped()) {
            // start releasing the brake
            releaseBrakes();
            isBrakeReleasing = true;
            isBraking = false;
            brakeReleaseStartTimeMillis = tempMillis;

            // ok to switch directions
            digitalWrite(REVERSE_OUTPUT_PIN, HIGH);
            mcp.setChannelValue(MCP4728_CHANNEL_A, currentDacOut);
            isMovingForward = true;
          } else if (isMovingForward) {
            // already moving forward, OK to keep moving
            mcp.setChannelValue(MCP4728_CHANNEL_A, currentDacOut);

            if (isBraking) {
              // if we were starting to brake, need to release the brake
              isBraking = false;
              releaseBrakes();
              isBrakeReleasing = true;
              // Adjust the brake release start time by half of the time already spent braking
              // this assumes that braking is running half as fast as releasing
              // need to do real math here for other scenarios
              brakeReleaseStartTimeMillis = tempMillis - ((tempMillis - brakingStartTimeMillis) / 2);
            }
          } else {
            // moving backward and we haven't stopped yet
            // keep waiting until we stop to reverse direction
            mcp.setChannelValue(MCP4728_CHANNEL_A, DAC_OFF);
          }
        }
      }
        
      lastThrottleUpdateMillis = millis();
    }

    boolean floatNearZero(float value, float delta) {
      return (abs(value) - delta) < 0.0;
    }
    
    void getStatus(char * status) {
      if (criticalBrakingFailure) {
        sprintf(status, "[Throttle] !! braking limit switch not found in allotted time !!");
      } else if (!brakesInitialized) {
        sprintf(status, "[Throttle] brake initialization underway ms: %ul", 
        millis() - brakingStartTimeMillis);
      } else {
        sprintf(status, "[Throttle] target:%i current:%f DAC:%i Delta:%i",
          throttleTargetScaled,
          currentThrottleScaled,
          currentDacOut,
          throttleDelta);
      }
    }
};

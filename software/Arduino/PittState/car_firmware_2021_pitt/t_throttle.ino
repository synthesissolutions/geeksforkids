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
#define REVERSE_PIN  20
//#define REVERSE2_PIN  21

#define BRAKE1_LIMIT_SWITCH_PIN 14
#define BRAKE2_LIMIT_SWITCH_PIN 15

#define BRAKE_ENGAGE_PWM        75
#define BRAKE_RELEASE_PWM       150
#define BRAKE_MOTOR_OFF_PWM     0

#define BRAKE_RELEASE_MILLISECONDS  300
#define MAX_BRAKE_TIME_MILLISECONDS 900

class Throttle {

  private:
    // throttle is not ready until the currentThrottleScaled has reached 0
    // this prevents the car from jerking forward as soon as it is turned on
    // it also allows time for the joystick and PWM readings to settle
    boolean throttleReady = false;

    int directionBrake1Pin;
    int speedPwmBrake1Pin;
    int directionBrake2Pin;
    int speedPwmBrake2Pin;

    // When braking is activated move the motor forward until the limit switch is pressed
    // or it took too long to activate the switch. If it takes too long, shutdown the throttle
    // permanently and display error message in logs.
    // When moving after braking has started, the brake must be released. There is no limit switch
    // in this direction so we just release for X milliseconds. If we start braking and then the
    // throttle is told to move, we reverse the braking motion by the same number of milliseconds
    // that we traveled during the initial braking. If we start moving after the limit switch is
    // activated, we reverse the braking motion by the full number of milliseconds.
    boolean isMovingForward = true;
    boolean criticalBrakeFailure = false;
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
    void init(int dirBrake1Pin, int pwmBrake1Pin, int dirBrake2Pin, int pwmBrake2Pin) {
      directionBrake1Pin = dirBrake1Pin;
      speedPwmBrake1Pin = pwmBrake1Pin;
      directionBrake2Pin = dirBrake2Pin;
      speedPwmBrake2Pin = pwmBrake2Pin;
      
      pinMode(directionBrake1Pin, OUTPUT);
      pinMode(speedPwmBrake1Pin, OUTPUT);
      pinMode(directionBrake2Pin, OUTPUT);
      pinMode(speedPwmBrake2Pin, OUTPUT);
            
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


      /*
      pinMode(REVERSE1_PIN, INPUT_PULLUP);
      pinMode(REVERSE2_PIN, INPUT_PULLUP);

      digitalWrite(REVERSE1_PIN, HIGH);
      digitalWrite(REVERSE2_PIN, HIGH);
      */
      pinMode(BRAKE1_LIMIT_SWITCH_PIN, INPUT_PULLUP);
      pinMode(BRAKE2_LIMIT_SWITCH_PIN, INPUT_PULLUP);

      digitalWrite(directionBrake1Pin, HIGH);
      digitalWrite(directionBrake2Pin, HIGH);
      analogWrite(speedPwmBrake1Pin, BRAKE_MOTOR_OFF_PWM);
      analogWrite(speedPwmBrake2Pin, BRAKE_MOTOR_OFF_PWM);

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

    boolean isStoppedBrakeActuator1() {
      // The limit switch is Grounded when triggered, so the logic is inverted
      //return !digitalRead(BRAKE_LIMIT_SWITCH1_PIN);
      return true;
    }

    boolean isStoppedBrakeActuator2() {
      // The limit switch is Grounded when triggered, so the logic is inverted
      //return !digitalRead(BRAKE_LIMIT_SWITCH2_PIN);
      return true;
    }
    
    boolean isStopped() {
      // The limit switch is Grounded when triggered, so the logic is inverted
      return isStoppedBrakeActuator1() && isStoppedBrakeActuator2();
    }

    void engageBrakeActuator1() {
      digitalWrite(directionBrake1Pin, HIGH);
      analogWrite(speedPwmBrake1Pin, BRAKE_ENGAGE_PWM);
    }

    void engageBrakeActuator2() {
      digitalWrite(directionBrake2Pin, HIGH);
      analogWrite(speedPwmBrake2Pin, BRAKE_ENGAGE_PWM);
    }
    
    void engageBrakes() {
      if (!isStoppedBrakeActuator1()) {
        engageBrakeActuator1();
      }

      if (!isStoppedBrakeActuator2()) {
        engageBrakeActuator2();
      }
    }

    void releaseBrakes() {
      digitalWrite(directionBrake1Pin, LOW);
      digitalWrite(directionBrake2Pin, LOW);
      analogWrite(speedPwmBrake1Pin, BRAKE_RELEASE_PWM);
      analogWrite(speedPwmBrake2Pin, BRAKE_RELEASE_PWM);
    }

    void stopBrakingMotor1() {
      digitalWrite(directionBrake1Pin, HIGH);
      analogWrite(speedPwmBrake1Pin, BRAKE_MOTOR_OFF_PWM);
    }

    void stopBrakingMotor2() {
      digitalWrite(directionBrake2Pin, HIGH);
      analogWrite(speedPwmBrake2Pin, BRAKE_MOTOR_OFF_PWM);
    }
    
    void stopBrakingMotors() {
      stopBrakingMotor1();
      stopBrakingMotor2();
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
        stopBrakingMotors();
        return;
      }

      if (criticalBrakeFailure) {
        stopBrushlessMotors();
        stopBrakingMotors();
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
            if (!isStoppedBrakeActuator1()) {
              engageBrakeActuator1();
            }
            if (!isStoppedBrakeActuator2()) {
              engageBrakeActuator2();
            }
          }
        } else {
          // check for successful brake initialization (both limit switches pressed),
          // in progress (time limit not expired),
          // or critical braking failure (time limit is expired)
          if (isStopped()) {
            // both limit switches pressed
            // stop motors and record successful initialization
            stopBrakingMotors();
            brakesInitialized = true;
          } else if (tempMillis - MAX_BRAKE_TIME_MILLISECONDS < brakingStartTimeMillis) {
            // at least one brake actuator still moving
            if (isStoppedBrakeActuator1()) {
              stopBrakingMotor1();
            }
            if (isStoppedBrakeActuator2()) {
              stopBrakingMotor2();
            }
          } else {
            // initialization took to long, a critical braking failure has occured
            stopBrakingMotors();
            brakesInitialized = true;
            criticalBrakeFailure = true;
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
          stopBrushlessMotors();
          return;
        }
      }

      // Check to see if we need to stop braking either because we have hit the limit switch
      // or because we have failed to trigger the limit switch in time
      if (isBraking) {
        if (isStopped()) {
          stopBrakingMotors();
          isBraking = false;
        } else if (tempMillis - MAX_BRAKE_TIME_MILLISECONDS > brakingStartTimeMillis) {
          stopBrakingMotors();
          stopBrushlessMotors(); // shouldn't be on, but just in case
          criticalBrakeFailure = true;

          return;
        } else {
          // check to see if one of the braking motors needs to be stopped
          if (isStoppedBrakeActuator1()) {
            stopBrakingMotor1();
          }
          if (isStoppedBrakeActuator2()) {
            stopBrakingMotor2();
          }
        }
      }
      
      // Check to see if we need to stop releasing the brake
      if (isBrakeReleasing && (tempMillis - BRAKE_RELEASE_MILLISECONDS > brakeReleaseStartTimeMillis)) {
        stopBrakingMotors();
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
          isBrakeReleasing = false;
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
          if (isStopped()) {
            // start releasing the brake
            releaseBrakes();
            isBrakeReleasing = true;
            isBraking = false;
            brakeReleaseStartTimeMillis = tempMillis;

            // ok to switch directions
            moveBackward(currentDacOut);
            isMovingForward = false;
          } else if (!isMovingForward) {
            // already moving backard, OK to keep moving
            moveBackward(currentDacOut);

            if (isBraking) {
              // if we were starting to brake, need to release the brake
              isBraking = false;
              releaseBrakes();
              isBrakeReleasing = true;
              // Adjust the brake release start time based on the fact that we were
              // already braking so we don't want to release too far. However,
              // the following is only a gross approximation and falls apaprt when
              // pulsing quickly between braking and releasing
              brakeReleaseStartTimeMillis = tempMillis - (tempMillis - brakingStartTimeMillis);
            }
          } else {
            // moving forward and we haven't stopped yet
            // keep waiting until we stop to reverse direction
            stopBrushlessMotors();
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
            moveForward(currentDacOut);
            isMovingForward = true;
          } else if (isMovingForward) {
            // already moving forward, OK to keep moving
            moveForward(currentDacOut);

            if (isBraking) {
              // if we were starting to brake, need to release the brake
              isBraking = false;
              releaseBrakes();
              isBrakeReleasing = true;
              // Adjust the brake release start time based on the fact that we were
              // already braking so we don't want to release too far. However,
              // the following is only a gross approximation and falls apaprt when
              // pulsing quickly between braking and releasing
              brakeReleaseStartTimeMillis = tempMillis - (tempMillis - brakingStartTimeMillis);
            }
          } else {
            // moving backward and we haven't stopped yet
            // keep waiting until we stop to reverse direction
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
      if (criticalBrakeFailure) {
        sprintf(status, "[Throttle] !! braking limit switch not found in allotted time !!");
      } else if (!brakesInitialized) {
        sprintf(status, "[Throttle] brake initialization underway ms: %ul", 
        millis() - brakingStartTimeMillis);
      } else {
        sprintf(status, "[Throttle] target:%i current:%f DAC:%i isBraking: %s isBrakeReleasing: %s",
          throttleTargetScaled,
          currentThrottleScaled,
          currentDacOut,
          isBraking ? "true" : "false",
          isBrakeReleasing ? "true" : "false");
      }
    }
};

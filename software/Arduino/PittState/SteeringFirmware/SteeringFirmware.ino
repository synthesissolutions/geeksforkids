// Rotate Counter Clockwise until 

#include <AccelStepper.h>

#define FRONT_LEFT

#if defined(FRONT_LEFT)
  #define STEERING_DIRECTION_NORMAL   true
  #define STEPPER_DIRECTION_INVERTED  false
  #define BUFFER_FROM_SWITCH_IN_STEPS 28
#elif defined(FRONT_RIGHT)
  #define STEERING_DIRECTION_NORMAL   true
  #define STEPPER_DIRECTION_INVERTED  true
  #define BUFFER_FROM_SWITCH_IN_STEPS 22
#elif defined(BACK_LEFT)
  #define STEERING_DIRECTION_NORMAL   false
  #define STEPPER_DIRECTION_INVERTED  true
  #define BUFFER_FROM_SWITCH_IN_STEPS 47
#elif defined(BACK_RIGHT)
  #define STEERING_DIRECTION_NORMAL   false
  #define STEPPER_DIRECTION_INVERTED  false
  #define BUFFER_FROM_SWITCH_IN_STEPS 50
#endif

#define PULSE_PIN     4
#define DIR_PIN       3
#define ENABLE_PIN    2

#define MAX_STARTUP_TIME_MILLIS   2500

AccelStepper stepperMotor = AccelStepper(AccelStepper::DRIVER, PULSE_PIN, DIR_PIN);

#define LIMIT_SWITCH_PIN                    A0
#define ANALOG_STEERING_SIGNAL_PIN          A4

#define STEPS_PER_ROTATION        800
#define STEPS_CLOSE_ENOUGH        3  // number of steps away from current target considered close enough
#define MOVEMENT_RANGE_DEGREES    90.0
#define SPEED                     200

boolean switchFound = false;
boolean centerFound = false;

long initializationStartTime;
boolean startupComplete = false;
boolean startupFailed = false;

long stepperMin, stepperCenter, stepperMax;

// The rear wheels steer in opposite directions from the front wheels
// set to true for the front wheels and false for rear wheels
boolean steeringDirectionNormal = STEERING_DIRECTION_NORMAL;
boolean stepperDirectionInverted = STEPPER_DIRECTION_INVERTED;

// how far from the limit switch does the movement range start
// this can be adjusted per wheel to account for limit switch positioning differences
int bufferFromSwitchInSteps = BUFFER_FROM_SWITCH_IN_STEPS;

int rangeSteps = (MOVEMENT_RANGE_DEGREES / 360.0) * STEPS_PER_ROTATION;

long lastUpdateTime = 0;
long currentStepperTarget = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("22.2 Beta Pitt State Steering Single");

  pinMode(ANALOG_STEERING_SIGNAL_PIN, INPUT);
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLDOWN);

  //stepperMotor.setEnablePin(ENABLE_PIN);
  stepperMotor.setMaxSpeed(1000);
  //stepperMotor.enableOutputs();
  //stepperMotor.setPinsInverted();
  //stepperMotor.setMinPulseWidth(3);
  
  if (stepperDirectionInverted) {
    stepperMotor.setSpeed(-SPEED);
  } else {
    stepperMotor.setSpeed(SPEED);
  }

  initializationStartTime = millis();
}

void loop()
{
  // Startup is complete either when all steppers have touched their limit switch
  // and then moved to their calculated center position
  // or when time has elasped and that has not occured for all stepper motors
  if (startupFailed) {
    
  } else if (!startupComplete) {
    // Check to see if the startup time has expired before startup is complete
    if (millis() - initializationStartTime > MAX_STARTUP_TIME_MILLIS) {
      startupFailed = true;
      Serial.println("Start failed. Max Initialization time exceeded.");
      stepperMotor.stop();

      return;
    }
    
    if (!switchFound) {
      if (digitalRead(LIMIT_SWITCH_PIN)) {
        switchFound = true;
        Serial.println("Limit Switch Found");
        long switchPosition = stepperMotor.currentPosition();

        Serial.print("Switch Position: ");
        Serial.println(switchPosition);

        if (stepperDirectionInverted) {
          stepperMin = switchPosition + bufferFromSwitchInSteps;
          stepperCenter = stepperMin + (rangeSteps / 2);
          stepperMax = stepperMin + rangeSteps;
        } else {
          stepperMax = switchPosition - bufferFromSwitchInSteps;
          stepperCenter = stepperMax - (rangeSteps / 2);
          stepperMin = stepperMax - rangeSteps;
        }


        Serial.print("Min, Center, Max: ");
        Serial.print(stepperMin);
        Serial.print(" ");
        Serial.print(stepperCenter);
        Serial.print(" ");
        Serial.println(stepperMax);

        if (stepperDirectionInverted) {
          stepperMotor.setSpeed(SPEED);
        } else {
          stepperMotor.setSpeed(-SPEED);
        }
      } else {
        stepperMotor.runSpeed();
      }
    } else if (!centerFound) {
      if (stepperMotor.currentPosition() == stepperCenter) {
        Serial.println("Found Center");

        centerFound = true;
        stepperMotor.stop();
      } else {
        stepperMotor.runSpeed();
      }
    }

    if (centerFound) {
      startupComplete = true;
      Serial.println("Initialization completed successfully!");
    }
  } else {
    // Startup is finished, handle steering
    // if the limit switch is not pressed
    if (!digitalRead(LIMIT_SWITCH_PIN)) {
      long currentStepperPosition = stepperMotor.currentPosition();
      uint16_t currentScaledTarget = getCurrentScaledTarget();

      if (steeringDirectionNormal) {
        // Direction is inverted (rear wheels)
        currentStepperTarget = map(500-currentScaledTarget, 0, 500, stepperMin, stepperMax);  
      } else {
        currentStepperTarget = map(currentScaledTarget, 0, 500, stepperMin, stepperMax);
      }
      lastUpdateTime = millis();

//            Serial.print(currentScaledTarget);
//            Serial.print("  ");
//            Serial.print(currentStepperTarget);
//            Serial.print("  ");
//            Serial.println(currentStepperPosition);
      
      if (between(currentStepperTarget, currentStepperPosition - STEPS_CLOSE_ENOUGH, currentStepperPosition + STEPS_CLOSE_ENOUGH)) {
        // Close enough, just stay here
        stepperMotor.stop();
      } else if (currentStepperTarget < currentStepperPosition) {
        stepperMotor.setSpeed(-SPEED);
      } else {
        stepperMotor.setSpeed(SPEED);
      }

      if (between(currentStepperTarget, currentStepperPosition - STEPS_CLOSE_ENOUGH, currentStepperPosition + STEPS_CLOSE_ENOUGH)) {
        stepperMotor.stop();
      } else {
        stepperMotor.runSpeed();
      }
    } else {
      Serial.print("ERROR: Limit switch pressed");
      
      stepperMotor.stop();
    }
  }
}

  uint16_t getCurrentScaledTarget() {
  uint16_t currentScaledTarget = analogRead(ANALOG_STEERING_SIGNAL_PIN);
  currentScaledTarget = constrain(currentScaledTarget, 0, 500);

  return currentScaledTarget;
  //return 250;
}

boolean between(long value, long min, long max) {
  return value >= min && value <= max;
}

// Rotate Counter Clockwise until 

#include <AccelStepper.h>

#define STEPPER_MOTOR_COUNT      2
//#define STEPPER_MOTOR_COUNT      4

#define FRONT_LEFT_PULSE_PIN     5
#define FRONT_LEFT_DIR_PIN       4
#define FRONT_LEFT_ENABLE_PIN    3

#define FRONT_RIGHT_PULSE_PIN     A3
#define FRONT_RIGHT_DIR_PIN       12
#define FRONT_RIGHT_ENABLE_PIN    11

#define BACK_LEFT_PULSE_PIN     10
#define BACK_LEFT_DIR_PIN       9
#define BACK_LEFT_ENABLE_PIN    8

#define BACK_RIGHT_PULSE_PIN     13
#define BACK_RIGHT_DIR_PIN       12
#define BACK_RIGHT_ENABLE_PIN    11

#define MAX_STARTUP_TIME_MILLIS   2500

AccelStepper frontLeftStepper = AccelStepper(AccelStepper::DRIVER, FRONT_LEFT_PULSE_PIN, FRONT_LEFT_DIR_PIN);
AccelStepper frontRightStepper = AccelStepper(AccelStepper::DRIVER, FRONT_RIGHT_PULSE_PIN, FRONT_RIGHT_DIR_PIN);
AccelStepper backLeftStepper = AccelStepper(AccelStepper::DRIVER, BACK_LEFT_PULSE_PIN, BACK_LEFT_DIR_PIN);
AccelStepper backRightStepper = AccelStepper(AccelStepper::DRIVER, BACK_RIGHT_PULSE_PIN, BACK_RIGHT_DIR_PIN);

#define FRONT_LEFT_LIMIT_SWITCH_PIN         A0
#define FRONT_RIGHT_LIMIT_SWITCH_PIN        A1
#define BACK_LEFT_LIMIT_SWITCH_PIN          A2
#define BACK_RIGHT_LIMIT_SWITCH_PIN         A3

#define ANALOG_STEERING_SIGNAL_PIN          A4

#define STEPS_PER_ROTATION        400
#define STEPS_CLOSE_ENOUGH        3  // number of steps away from current target considered close enough
#define MOVEMENT_RANGE_DEGREES    90.0
#define SPEED                     100
#define UPDATE_DELAY_MILLIS       50

// IMPORTANT
// For all of the following four position arrays, the order
// of the items in the array are 
// Left Front, Right Front, Left Back and Right Back
boolean switchFound[] = {false, false, false, false};
boolean centerFound[] = {false, false, false, false};

long initializationStartTime;
boolean startupComplete = false;
boolean startupFailed = false;

long stepperMin[4], stepperCenter[4], stepperMax[4];

// Typically, the rear two wheels wil be moved in the opposite direction
// from the front wheels to turn more quickly
boolean steeringDirectionInverted[] = {true, true, false, false };

// The limit switch is always installed towards the middle of the car.
// This results in the inintial movement to find the limit switch to be inverted
// and changes some of the other calculations for Lef, Center and Right target positions
// The natural direction of movement is counter clockwise?? Need to verify with Pitt State
boolean stepperDirectionInverted[] = {false, true, false, true};

int limitSwitchPin[] = {A0, A1, A2, A3};

// how far from the limit switch does the movement range start
// this can be adjusted per wheel to account for limit switch positioning differences
int bufferFromSwitchInSteps[] = {25, 25, 25, 25};

AccelStepper stepperMotor[] = {frontLeftStepper, frontRightStepper, backLeftStepper, backRightStepper};
int enablePin[] = {FRONT_LEFT_ENABLE_PIN, FRONT_RIGHT_ENABLE_PIN, BACK_LEFT_ENABLE_PIN, BACK_RIGHT_ENABLE_PIN};

int rangeSteps = (MOVEMENT_RANGE_DEGREES / 360.0) * STEPS_PER_ROTATION;

long lastUpdateTime = 0;
long currentStepperTarget = 0;
//int8_t currentScaledTarget = 0;
//uint16_t currentScaledTarget = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("22.1 Beta Pitt State Steering");

  pinMode(ANALOG_STEERING_SIGNAL_PIN, INPUT);
  
  for (int i = 0; i < STEPPER_MOTOR_COUNT; i++) {
    pinMode(limitSwitchPin[i], INPUT_PULLUP);
  }

  for (int i = 0; i < STEPPER_MOTOR_COUNT; i++) {
    stepperMotor[i].setEnablePin(enablePin[i]);
    stepperMotor[i].setMaxSpeed(1000);
    stepperMotor[i].enableOutputs();
    stepperMotor[i].setPinsInverted();
    if (stepperDirectionInverted[i]) {
      stepperMotor[i].setSpeed(-SPEED);
    } else {
      stepperMotor[i].setSpeed(SPEED);
    }

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
      for (int i = 0; i < STEPPER_MOTOR_COUNT; i++) {
        stepperMotor[i].stop();
      }
      return;
    }
    
    for (int i = 0; i < STEPPER_MOTOR_COUNT; i++) {
      if (!switchFound[i]) {
        if (!digitalRead(limitSwitchPin[i])) {
          switchFound[i] = true;
          Serial.print("Switch Found for: ");
          Serial.println(i);
          long switchPosition = stepperMotor[i].currentPosition();

          Serial.print("Switch Position: ");
          Serial.println(switchPosition);

          if (stepperDirectionInverted[i]) {
            stepperMin[i] = switchPosition + bufferFromSwitchInSteps[i];
            stepperCenter[i] = stepperMin[i] + (rangeSteps / 2);
            stepperMax[i] = stepperMin[i] + rangeSteps;
          } else {
            stepperMax[i] = switchPosition - bufferFromSwitchInSteps[i];
            stepperCenter[i] = stepperMax[i] - (rangeSteps / 2);
            stepperMin[i] = stepperMax[i] - rangeSteps;
          }


          Serial.print("Min, Center, Max: ");
          Serial.print(stepperMin[i]);
          Serial.print(" ");
          Serial.print(stepperCenter[i]);
          Serial.print(" ");
          Serial.println(stepperMax[i]);

          if (stepperDirectionInverted[i]) {
            stepperMotor[i].setSpeed(SPEED);
          } else {
            stepperMotor[i].setSpeed(-SPEED);
          }
        } else {
          stepperMotor[i].runSpeed();
        }
      } else if (!centerFound[i]) {
        if (stepperMotor[i].currentPosition() == stepperCenter[i]) {
          Serial.print("Found Center for: ");
          Serial.println(i);
          
          centerFound[i] = true;
          stepperMotor[i].stop();
        } else {
          stepperMotor[i].runSpeed();
        }
      }
    }

    if (allCentersFound()) {
      startupComplete = true;
      Serial.println("Initialization completed successfully!");
    }
  } else {
    // Startup is finished, handle steering
    for (int i = 0; i < STEPPER_MOTOR_COUNT; i++) {
      // if the limit switch is not pressed
      if (digitalRead(limitSwitchPin[i])) {
        long currentStepperPosition = stepperMotor[i].currentPosition();
        uint16_t currentScaledTarget = getCurrentScaledTarget();
        //Serial.println(currentScaledTarget);

        if (millis() - UPDATE_DELAY_MILLIS > lastUpdateTime) {
          if (steeringDirectionInverted[i]) {
            // Direction is inverted (rear wheels)
            currentStepperTarget = map(500-currentScaledTarget, 0, 500, stepperMin[i], stepperMax[i]);  
          } else {
            currentStepperTarget = map(currentScaledTarget, 0, 500, stepperMin[i], stepperMax[i]);
          }
          lastUpdateTime = millis();

          if (i == 0) {
            Serial.print(currentScaledTarget);
            Serial.print("  ");
            Serial.print(currentStepperTarget);
            Serial.print("  ");
            Serial.println(currentStepperPosition);
          }
          
          if (between(currentStepperTarget, currentStepperPosition - STEPS_CLOSE_ENOUGH, currentStepperPosition + STEPS_CLOSE_ENOUGH)) {
            // Close enough, just stay here
            stepperMotor[i].stop();
            Serial.print(i);
            Serial.println(" stop");
          } else if (currentStepperTarget < currentStepperPosition) {
            Serial.print(i);
            Serial.println(" left");
            stepperMotor[i].setSpeed(-SPEED);
          } else {
            Serial.print(i);
            Serial.println(" right");
            stepperMotor[i].setSpeed(SPEED);
          }
        }
  
        if (between(currentStepperTarget, currentStepperPosition - STEPS_CLOSE_ENOUGH, currentStepperPosition + STEPS_CLOSE_ENOUGH)) {
          stepperMotor[i].stop();
        } else {
          stepperMotor[i].runSpeed();
        }
      } else {
        Serial.print("ERROR: Limit switch pressed for motor: ");
        Serial.println(i);
        
        stepperMotor[i].stop();
      }
    }
//    delay(10);
  }
}

uint16_t getCurrentScaledTarget() {
  uint16_t currentScaledTarget = analogRead(ANALOG_STEERING_SIGNAL_PIN);
  currentScaledTarget = constrain(currentScaledTarget, 0, 500);

  return currentScaledTarget;
}

boolean between(long value, long min, long max) {
  return value >= min && value <= max;
}

boolean allCentersFound() {
  for (int i = 0; i < STEPPER_MOTOR_COUNT; i++) {
    if (!centerFound[i]) {
      return false;
    }
  }

  Serial.println("all centers found true");
  return true;
}

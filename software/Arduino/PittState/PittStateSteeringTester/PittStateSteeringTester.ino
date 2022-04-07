#include <AccelStepper.h>

#define PULSE_PIN     4
#define DIR_PIN       3
#define ENABLE_PIN    2

#define STEPS_PER_ROTATION        400
#define SPEED                     200
#define MOVEMENT_RANGE_DEGREES    90.0
#define STEPS_CLOSE_ENOUGH        3

#define STEERING_POT_PIN  A7

int rangeSteps = (MOVEMENT_RANGE_DEGREES / 360.0) * STEPS_PER_ROTATION;
int maxPosition = rangeSteps / 2;
int minPostion = -maxPosition;
boolean isStopped = false;

AccelStepper stepperMotor = AccelStepper(AccelStepper::DRIVER, PULSE_PIN, DIR_PIN);

void setup() {
  Serial.begin(115200);
  pinMode(STEERING_POT_PIN, INPUT);

  //stepperMotor.setEnablePin(ENABLE_PIN);
  stepperMotor.setMaxSpeed(1000);
  stepperMotor.setMinPulseWidth(10);
  //stepperMotor.enableOutputs();
  //stepperMotor.setPinsInverted();
  //stepperMotor.setSpeed(SPEED);
}

void loop() {
  int steeringInput = analogRead(STEERING_POT_PIN);
  int steeringTarget = map(steeringInput, 0, 1023, minPostion, maxPosition);

  long currentStepperPosition = stepperMotor.currentPosition();
  Serial.print(currentStepperPosition);
  Serial.print("  ");
  Serial.print(steeringTarget);
  Serial.print("  ");

  if (isStopped && between(currentStepperPosition, steeringTarget - STEPS_CLOSE_ENOUGH, steeringTarget + STEPS_CLOSE_ENOUGH)) {
    Serial.println("close enough");
    stepperMotor.stop();
  } else if (currentStepperPosition == steeringTarget) {
    Serial.println("stop");
    stepperMotor.stop();
    isStopped = true;
  } else if (currentStepperPosition > steeringTarget) {
    Serial.println("go left");
    isStopped = false;
    stepperMotor.setSpeed(-SPEED);
    stepperMotor.runSpeed();
  } else {
    isStopped = false;
    Serial.println("go right");
    stepperMotor.setSpeed(SPEED);
    stepperMotor.runSpeed();
  }
}

boolean between(long value, long min, long max) {
  return value >= min && value <= max;
}

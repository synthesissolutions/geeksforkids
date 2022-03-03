// Rotate Counter Clockwise until 

#include <AccelStepper.h>
#include <Wire.h>

#define PULSE_PIN     4
#define DIR_PIN       3
#define ENABLE_PIN    2

AccelStepper stepper = AccelStepper(AccelStepper::DRIVER, PULSE_PIN, DIR_PIN);

#define LIMIT_SWITCH_PIN          A0
#define STEPS_PER_ROTATION        800
#define STEPS_CLOSE_ENOUGH        3  // number of steps away from current target considered close enough
#define MOVEMENT_RANGE_DEGREES    100.0
#define BUFFER_FROM_SWITCH_STEPS  100
#define SPEED               400
#define UPDATE_DELAY_MILLIS 50

boolean switchFound = false;
boolean centerFound = false;
boolean startupComplete = false;

long startingPosition;
long switchPosition;
long stepperMin, stepperCenter, stepperMax;
int rangeSteps = (MOVEMENT_RANGE_DEGREES / 360.0) * STEPS_PER_ROTATION;
long switchPressedTime;
long lastUpdateTime = 0;
long currentStepperTarget = 0;
int8_t currentScaledTarget = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("22.1 Alpha Pitt State Steering");

  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);

/*
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);

  digitalWrite(3, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(7, HIGH);
*/
  stepper.setEnablePin(ENABLE_PIN);
  stepper.setMaxSpeed(1000);
  stepper.enableOutputs();
  stepper.setPinsInverted();
  stepper.setSpeed(SPEED);
  
  startingPosition = stepper.currentPosition();
}

void loop()
{
  if (!startupComplete) {
    if (!switchFound) {
      if (!digitalRead(LIMIT_SWITCH_PIN)) {
        switchFound = true;
        switchPosition = stepper.currentPosition();
        switchPressedTime = millis();
  
        stepperMin = switchPosition - BUFFER_FROM_SWITCH_STEPS;
        stepperCenter = stepperMin - (rangeSteps / 2);
        stepperMax = stepperMin - rangeSteps;
        
        stepper.setSpeed(-SPEED);
      } else {
        if (digitalRead(LIMIT_SWITCH_PIN)) { // double check that the button is not pressed
          stepper.runSpeed();
        }
      }
    } else if (!centerFound) {
      if (stepper.currentPosition() == stepperCenter) {
        //Serial.println("Found Center");
        centerFound = true;
        startupComplete = true;
        stepper.stop();
      } else {
        if ((millis() - switchPressedTime < 500) || digitalRead(LIMIT_SWITCH_PIN)) { // double check that the button is not pressed
          stepper.runSpeed();
        }
      }
    }
  } else {
    // Startup is finished, handle steering
    // if the limit switch is not pressed
    if (digitalRead(LIMIT_SWITCH_PIN)) {
      long currentStepperPosition = stepper.currentPosition();

      if (millis() - UPDATE_DELAY_MILLIS > lastUpdateTime) {
        currentStepperTarget = map(currentScaledTarget, -100, 100, stepperMin, stepperMax);        
        lastUpdateTime = millis();
        
        //Serial.print("Scaled Target: ");
        //Serial.print(currentScaledTarget);
        //Serial.print("  Stepper Target: ");
        //Serial.print(currentStepperTarget);
        //Serial.print("  Stepper Position: ");
        //Serial.println(currentStepperPosition);

        if (between(currentStepperTarget, currentStepperPosition - STEPS_CLOSE_ENOUGH, currentStepperPosition + STEPS_CLOSE_ENOUGH)) {
          // Close enough, just stay here
          stepper.stop();
        } else if (currentStepperTarget < currentStepperPosition) {
          stepper.setSpeed(-SPEED);
        } else {
          stepper.setSpeed(SPEED);
        }
      }

      if (between(currentStepperTarget, currentStepperPosition - STEPS_CLOSE_ENOUGH, currentStepperPosition + STEPS_CLOSE_ENOUGH)) {
        stepper.stop();
      } else {
        stepper.runSpeed();
      }

    } else {
      Serial.println("ERROR!");
      stepper.stop();
      delay(1000);
    }
  }
}

boolean between(long value, long min, long max) {
  return value >= min && value <= max;
}

void receiveEvent(int howMany) {
  while (1 < Wire.available()) {
    Wire.read(); // this should not happen
  }

  currentScaledTarget = Wire.read();
  //Serial.print("I2C Value: ");
  //Serial.println(currentScaledTarget);
}

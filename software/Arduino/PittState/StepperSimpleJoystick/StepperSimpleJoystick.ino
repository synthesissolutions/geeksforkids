// Rotate Counter Clockwise until 

#include <AccelStepper.h>

AccelStepper stepper = AccelStepper(AccelStepper::DRIVER, 6, 4); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

#define LIMIT_SWITCH_PIN  A0
#define JOYSTICK_X_PIN    A2
#define STEPS_PER_ROTATION  800
#define STEPS_CLOSE_ENOUGH   3  // number of steps away from current target considered close enough
#define MOVEMENT_RANGE_DEGREES  100.0
#define BUFFER_FROM_SWITCH_STEPS  100
#define ACCELERATION  400  // too low need to figure out if this is necessary at all
#define SPEED         400
#define JOYSTICK_READ_DELAY_MILLIS  20

boolean switchFound = false;
boolean centerFound = false;
boolean startupComplete = false;

long startingPosition;
long switchPosition;
long stepperMin, stepperCenter, stepperMax;
int rangeSteps = (MOVEMENT_RANGE_DEGREES / 360.0) * STEPS_PER_ROTATION;
long switchPressedTime;
long lastJoystickXReadTime = 0;
long currentStepperTarget = 0;

void setup()
{
  Serial.begin(115200);
  while (! Serial) delay(10);

  Serial.println("Simple Joystick Control");

  pinMode(JOYSTICK_X_PIN, INPUT);
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);

  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);

  digitalWrite(3, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(7, HIGH);
  
   stepper.setEnablePin(2);
   stepper.setMaxSpeed(1000);
   stepper.enableOutputs();
   stepper.setPinsInverted();
   stepper.setSpeed(SPEED);

   startingPosition = stepper.currentPosition();
   Serial.print("Starting Position: ");
   Serial.println(startingPosition);
}

void loop()
{
  if (!startupComplete) {
    if (!switchFound) {
      if (!digitalRead(LIMIT_SWITCH_PIN)) {
        switchFound = true;
        switchPosition = stepper.currentPosition();
        switchPressedTime = millis();
        
        Serial.print("Switch Position: ");
        Serial.println(switchPosition);
  
        stepperMin = switchPosition - BUFFER_FROM_SWITCH_STEPS;
        stepperCenter = stepperMin - (rangeSteps / 2);
        stepperMax = stepperMin - rangeSteps;
  
        Serial.print("Min: ");
        Serial.println(stepperMin);
        Serial.print("Center: ");
        Serial.println(stepperCenter);
        Serial.print("Max: ");
        Serial.println(stepperMax);
        
        stepper.setSpeed(-SPEED);
      } else {
        if (digitalRead(LIMIT_SWITCH_PIN)) { // double check that the button is not pressed
          stepper.runSpeed();
        }
      }
    } else if (!centerFound) {
      if (stepper.currentPosition() == stepperCenter) {
        Serial.println("Found Center");
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

      if (millis() - JOYSTICK_READ_DELAY_MILLIS > lastJoystickXReadTime) {
        // take new joystick reading
        int joyX = 1024 - constrain(analogRead(JOYSTICK_X_PIN), 0, 1024);
        currentStepperTarget = map(joyX, 0, 1024, stepperMin, stepperMax);        
        lastJoystickXReadTime = millis();
        
        Serial.print(joyX);
        Serial.print("  ");
        Serial.print(currentStepperTarget);
        Serial.print("  ");
        Serial.println(currentStepperPosition);

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

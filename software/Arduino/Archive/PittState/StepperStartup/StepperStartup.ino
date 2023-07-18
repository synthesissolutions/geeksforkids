// Rotate Counter Clockwise until 

#include <AccelStepper.h>

AccelStepper stepper = AccelStepper(AccelStepper::DRIVER, 6, 4); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

#define STEPS_PER_ROTATION  800
#define MOVEMENT_RANGE_DEGREES  100.0
#define BUFFER_FROM_SWITCH_STEPS  100
#define ACCELERATION  400  // too low need to figure out if this is necessary at all
#define SPEED         400

boolean switchFound = false;
boolean centerFound = false;

long startingPosition;
long switchPosition;
long min, center, max;
int rangeSteps = (MOVEMENT_RANGE_DEGREES / 360.0) * STEPS_PER_ROTATION;
long switchPressedTime;

void setup()
{
  Serial.begin(115200);
  while (! Serial) delay(10);

  Serial.println("Start Stop at Switch");
  
  pinMode(A0, INPUT_PULLUP);
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
  if (!switchFound) {
    if (!digitalRead(A0)) {
      switchFound = true;
      switchPosition = stepper.currentPosition();
      switchPressedTime = millis();
      
      Serial.print("Switch Position: ");
      Serial.println(switchPosition);

      min = switchPosition - BUFFER_FROM_SWITCH_STEPS;
      center = min - (rangeSteps / 2);
      max = min - rangeSteps;

      Serial.print("Min: ");
      Serial.println(min);
      Serial.print("Center: ");
      Serial.println(center);
      Serial.print("Max: ");
      Serial.println(max);
      
      stepper.moveTo(center);
      stepper.setAcceleration(ACCELERATION);
    } else {
      if (digitalRead(A0)) { // double check that the button is not pressed
        stepper.runSpeed();
      }
    }
  } else if (!centerFound) {
    if (stepper.distanceToGo() == 0) {
      Serial.println("Found Center");
      centerFound = true;
      stepper.stop();
    } else {
      if ((millis() - switchPressedTime < 500) || digitalRead(A0)) { // double check that the button is not pressed
        stepper.run();
      }
    }
  }
}

// Rotate Counter Clockwise until 

#include <AccelStepper.h>
#include <Adafruit_MCP4728.h>
#include <Wire.h>

AccelStepper stepper = AccelStepper(AccelStepper::DRIVER, 6, 4); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
Adafruit_MCP4728 mcp;

#define LIMIT_SWITCH_PIN  A0
#define JOYSTICK_X_PIN    A2
#define JOYSTICK_Y_PIN    A1
#define REVERSE_OUTPUT_PIN  8
#define STEPS_PER_ROTATION  800
#define MOVEMENT_RANGE_DEGREES  100.0
#define BUFFER_FROM_SWITCH_STEPS  100
#define ACCELERATION  400  // too low need to figure out if this is necessary at all
#define SPEED         400
#define JOYSTICK_READ_DELAY_MILLIS  20
#define MIN_STOP_TIME 1000
#define DAC_MIN 750
#define DAC_MAX 2000
//#define DAC_MAX 4095
#define THROTTLE_STOPPED_MIN  480
#define THROTTLE_STOPPED_MAX  542

boolean switchFound = false;
boolean centerFound = false;
boolean startupComplete = false;

long startingPosition;
long switchPosition;
long min, center, max;
int rangeSteps = (MOVEMENT_RANGE_DEGREES / 360.0) * STEPS_PER_ROTATION;
long switchPressedTime;
long lastJoystickXReadTime = 0;
long timeStopped = 0;
boolean isMovingForward = true;
boolean isStopped = true;

void setup()
{
  Serial.begin(115200);
  while (! Serial) delay(10);

  Serial.println("Simple Joystick Control");

  if (!mcp.begin()) {
    Serial.println("Failed to find MCP4728 chip");
    while (1) {
      delay(10);
    }
  }

  mcp.setChannelValue(MCP4728_CHANNEL_A, DAC_MIN);
  
  pinMode(JOYSTICK_X_PIN, INPUT);
  pinMode(JOYSTICK_Y_PIN, INPUT);
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);
  pinMode(REVERSE_OUTPUT_PIN, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);

  digitalWrite(3, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(7, HIGH);

  digitalWrite(REVERSE_OUTPUT_PIN, HIGH);
  
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
        if (digitalRead(LIMIT_SWITCH_PIN)) { // double check that the button is not pressed
          stepper.runSpeed();
        }
      }
    } else if (!centerFound) {
      if (stepper.distanceToGo() == 0) {
        Serial.println("Found Center");
        centerFound = true;
        startupComplete = true;
        stepper.stop();
      } else {
        if ((millis() - switchPressedTime < 500) || digitalRead(LIMIT_SWITCH_PIN)) { // double check that the button is not pressed
          stepper.run();
        }
      }
    }
    
  } else {
    // Startup is finished, handle steering and throttle
    
    // if the limit switch is not pressed
    if (digitalRead(LIMIT_SWITCH_PIN)) {
      if (millis() - JOYSTICK_READ_DELAY_MILLIS > lastJoystickXReadTime) {
        // take new joystick reading
        int joyX = 1024 - constrain(analogRead(JOYSTICK_X_PIN), 0, 1024);
        int newStepperTarget = map(joyX, 0, 1024, min, max);

        int newMotorVoltage = DAC_MIN;
        int joyY = 1024 - constrain(analogRead(JOYSTICK_Y_PIN), 0, 1024);
        
        if (joyY >= THROTTLE_STOPPED_MIN and joyY <= THROTTLE_STOPPED_MAX) {
          // we are stopping
          if (!isStopped) {
            isStopped = true;
            timeStopped = millis();
          }
        } else if ((isMovingForward && joyY < THROTTLE_STOPPED_MIN) || (!isMovingForward && joyY > THROTTLE_STOPPED_MAX)) {
          // we are switching direction
          if (isStopped && (millis() - MIN_STOP_TIME > timeStopped)) {
            // we have been stopped long enough to switch directions
            isStopped = false;
            
            if (joyY > 512) {
              // we are moving forward
              isMovingForward = true;
              digitalWrite(REVERSE_OUTPUT_PIN, HIGH);
              newMotorVoltage = map(joyY, 512, 1024, DAC_MIN, DAC_MAX);
            } else {
              // we are moving backward
              isMovingForward = false;
              digitalWrite(REVERSE_OUTPUT_PIN, LOW);
              newMotorVoltage = map(1024 - joyY, 512, 1024, DAC_MIN, DAC_MAX);
            } 
          } else {
            // keep waiting or stop the motors if they are still running
            if (!isStopped) {
              isStopped = true;
              timeStopped = millis();
            }
          }
        } else {
          // we are continuing in the same direction, no need to wait until we stop
          isStopped = false;
          
          if (joyY > 512) {
            // we are moving forward
            newMotorVoltage = map(joyY, 512, 1024, DAC_MIN, DAC_MAX);
          } else {
            // we are moving backward
            newMotorVoltage = map(1024 - joyY, 512, 1024, DAC_MIN, DAC_MAX);
          } 
        }
        
        lastJoystickXReadTime = millis();
        
        Serial.print(joyX);
        Serial.print("  ");
        Serial.print(joyY);
        Serial.print("  IsStopped: ");
        if (isStopped) {
          Serial.print("true");
        } else {
          Serial.print("false");
        }
        Serial.print("  ");
        Serial.print(newMotorVoltage);
        Serial.print("  ");
        Serial.println(newStepperTarget);
        
        stepper.moveTo(newStepperTarget);
        stepper.setAcceleration(ACCELERATION);
        mcp.setChannelValue(MCP4728_CHANNEL_A, newMotorVoltage);
      }

      stepper.run();
    } else {
      Serial.println("ERROR!");
      stepper.stop();
      delay(1000);
    }

  }
}

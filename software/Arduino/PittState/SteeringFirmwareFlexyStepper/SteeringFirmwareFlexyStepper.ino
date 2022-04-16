#include <FlexyStepper.h>

#define CENTER_STARTUP_MODE

#define FRONT_LEFT

#if defined(FRONT_LEFT)
  #define STEERING_DIRECTION_NORMAL   true
  #define STEPPER_DIRECTION_INVERTED  false
  #define BUFFER_FROM_SWITCH_IN_STEPS 50
#elif defined(FRONT_RIGHT)
  #define STEERING_DIRECTION_NORMAL   true
  #define STEPPER_DIRECTION_INVERTED  false
  #define BUFFER_FROM_SWITCH_IN_STEPS 50
#elif defined(BACK_LEFT)
  #define STEERING_DIRECTION_NORMAL   false
  #define STEPPER_DIRECTION_INVERTED  false
  #define BUFFER_FROM_SWITCH_IN_STEPS 50
#elif defined(BACK_RIGHT)
  #define STEERING_DIRECTION_NORMAL   false
  #define STEPPER_DIRECTION_INVERTED  false
  #define BUFFER_FROM_SWITCH_IN_STEPS 50
#endif

#define PULSE_PIN     4
#define DIR_PIN       3
#define ENABLE_PIN    2

#define MAX_STARTUP_TIME_MILLIS   2500
#define STEERING_READINGS         10
#define STEERING_READINGS_DELAY_MILLIS  30

FlexyStepper stepperMotor;

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
boolean isStopped = false;

void setup()
{
  Serial.begin(115200);
  Serial.println("22.2 Beta Pitt State Steering Single");

  pinMode(ANALOG_STEERING_SIGNAL_PIN, INPUT);
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLDOWN);

  stepperMotor.connectToPins(PULSE_PIN, DIR_PIN);
  
  stepperMotor.setSpeedInStepsPerSecond(200);
  stepperMotor.setAccelerationInStepsPerSecondPerSecond(1000);

  initializationStartTime = millis();
}

void loop()
{

#if defined(CENTER_STARTUP_MODE)
  if (!startupComplete) {
    //  Fill up the readings array with valid results before starting
    delay(50);
    for (int i = 0; i < STEERING_READINGS; i++) {
      delay(STEERING_READINGS_DELAY_MILLIS + 1);
      uint16_t temp = getCurrentScaledTarget();
    }
    calculateStepperLimitsCenterStart();
    startupComplete = true;
  }
#endif
  
  // Startup is complete either when all steppers have touched their limit switch
  // and then moved to their calculated center position
  // or when time has elasped and that has not occured for all stepper motors
  if (startupFailed) {
    
  } else if (!startupComplete) {
    // Check to see if the startup time has expired before startup is complete
    if (millis() - initializationStartTime > MAX_STARTUP_TIME_MILLIS) {
      startupFailed = true;
      Serial.println("Start failed. Max Initialization time exceeded.");
      stepperMotor.setTargetPositionToStop();

      return;
    }
    
    if (!switchFound) {
      if (limitSwitchPressed()) {
        switchFound = true;
        Serial.println("Limit Switch Found");

        calculateStepperLimits();
        
        stepperMotor.setTargetPositionInSteps(stepperCenter);
      } else {
        stepperMotor.processMovement();
      }
    } else if (!centerFound) {
      if (stepperMotor.motionComplete()) {
        Serial.println("Found Center");

        centerFound = true;
        stepperMotor.setTargetPositionToStop();
      } else {
        stepperMotor.processMovement();
      }
    }

    if (centerFound) {
      startupComplete = true;
      Serial.println("Initialization completed successfully!");
    }
  } else {
    long currentStepperPosition = stepperMotor.getCurrentPositionInSteps();
          
    // Startup is finished, handle steering
    // if the limit switch is not pressed
    if (!limitSwitchPressed()) {

      uint16_t currentScaledTarget = getCurrentScaledTarget();
      long currentStepperTarget;
      
      if (steeringDirectionNormal) {
        // Direction is inverted (rear wheels)
        currentStepperTarget = map(500-currentScaledTarget, 0, 500, stepperMin, stepperMax);  
      } else {
        currentStepperTarget = map(currentScaledTarget, 0, 500, stepperMin, stepperMax);
      }

      /*
      Serial.print(currentScaledTarget);
      Serial.print("  ");
      Serial.print(currentStepperTarget);
      Serial.print("  ");
      Serial.println(currentStepperPosition);
      */
      
      if (isStopped && between(currentStepperTarget, currentStepperPosition - STEPS_CLOSE_ENOUGH, currentStepperPosition + STEPS_CLOSE_ENOUGH)) {
        // Close enough, just stay here
        //Serial.println("close enough");
        stepperMotor.setTargetPositionInSteps(currentStepperPosition);
      } else if (currentStepperTarget == currentStepperPosition) {
        //Serial.println("stop");
        stepperMotor.setTargetPositionInSteps(currentStepperPosition);
        isStopped = true;
      } else {
        isStopped = false;
        stepperMotor.setTargetPositionInSteps(currentStepperTarget);
      }

      stepperMotor.processMovement();
    } else {
      Serial.print("ERROR: Limit switch pressed");
      
      stepperMotor.setTargetPositionInSteps(currentStepperPosition);
    }
  }
}

uint16_t getCurrentScaledTarget() {
  static int readings[STEERING_READINGS];
  static int readingIndex = 0;
  static long lastReadingTimeMillis = 0;
  static uint16_t cachedCurrentScaledTarget = 250;

  if (lastReadingTimeMillis == 0) {
    for (int i = 0; i < STEERING_READINGS; i++) {
      readings[i] = 250;
    }
  }
  
  long currentTimestamp = millis();
  if (currentTimestamp - lastReadingTimeMillis > STEERING_READINGS_DELAY_MILLIS) {
    uint16_t newReading = analogRead(ANALOG_STEERING_SIGNAL_PIN);
    newReading = constrain(newReading, 0, 500);

    // store the new reading
    if (readingIndex >= STEERING_READINGS) {
      readingIndex = 0;
    }
    readings[readingIndex] = newReading;
    readingIndex++;

    // calculate the average of all of the stored readings
    int total = 0;
    for (int i = 0; i < STEERING_READINGS; i++) {
      total += readings[i];
    }
    
    cachedCurrentScaledTarget = total / STEERING_READINGS;      
    lastReadingTimeMillis = currentTimestamp;
  }

  return cachedCurrentScaledTarget;
}

boolean limitSwitchPressed() {
  return false;
  //return digitalRead(LIMIT_SWITCH_PIN);
}

void calculateStepperLimits() {
  long switchPosition = stepperMotor.getCurrentPositionInSteps();

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
}

void calculateStepperLimitsCenterStart() {
  long switchPosition = stepperMotor.getCurrentPositionInSteps();

  Serial.print("Switch Position: ");
  Serial.println(switchPosition);

  if (stepperDirectionInverted) {
    stepperMin = switchPosition - (rangeSteps / 2);
    stepperCenter = switchPosition;
    stepperMax = switchPosition + (rangeSteps / 2);
  } else {
    stepperMin = switchPosition + (rangeSteps / 2);
    stepperCenter = switchPosition;
    stepperMax = switchPosition - (rangeSteps / 2);
  }


  Serial.print("Min, Center, Max: ");
  Serial.print(stepperMin);
  Serial.print(" ");
  Serial.print(stepperCenter);
  Serial.print(" ");
  Serial.println(stepperMax);
}

boolean between(long value, long min, long max) {
  return value >= min && value <= max;
}

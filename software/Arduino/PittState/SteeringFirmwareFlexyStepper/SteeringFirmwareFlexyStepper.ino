#include <FlexyStepper.h>

#define CENTER_STARTUP_MODE

#define BACK_RIGHT

// The rear wheels steer in opposite directions from the front wheels
// set STEERING_DIRECTION_NORMAL to true for the front wheels and false for rear wheels

#if defined(FRONT_LEFT)
  #define STEERING_DIRECTION_NORMAL             true
  #define DIRECTION_TO_LIMIT_SWITCH_CLOCKWISE   true
  #define BUFFER_FROM_SWITCH_IN_STEPS           50
#elif defined(FRONT_RIGHT)
  #define STEERING_DIRECTION_NORMAL             true
  #define DIRECTION_TO_LIMIT_SWITCH_CLOCKWISE   false
  #define BUFFER_FROM_SWITCH_IN_STEPS           50
#elif defined(BACK_LEFT)
  #define STEERING_DIRECTION_NORMAL             false
  #define DIRECTION_TO_LIMIT_SWITCH_CLOCKWISE   false
  #define BUFFER_FROM_SWITCH_IN_STEPS           50
#elif defined(BACK_RIGHT)
  #define STEERING_DIRECTION_NORMAL             false
  #define DIRECTION_TO_LIMIT_SWITCH_CLOCKWISE   true
  #define BUFFER_FROM_SWITCH_IN_STEPS           50
#endif

#define PULSE_PIN     4
#define DIR_PIN       3
#define ENABLE_PIN    2

#define STEERING_READINGS         10
#define STEERING_READINGS_DELAY_MILLIS  30

#define LIMIT_SWITCH_PIN                    A0
#define ANALOG_STEERING_SIGNAL_PIN          A4

#define STEPS_PER_ROTATION        800
#define STEPS_CLOSE_ENOUGH        3  // number of steps away from current target considered close enough
#define MOVEMENT_RANGE_DEGREES    90.0
#define SPEED                     200
#define ACCELERATION              1000  // steps per second per second

FlexyStepper stepperMotor;

long initializationStartTime;
boolean startupComplete = false;
boolean startupFailed = false;

long stepperMin, stepperCenter, stepperMax;

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
  
  stepperMotor.setSpeedInStepsPerSecond(SPEED);
  stepperMotor.setAccelerationInStepsPerSecondPerSecond(ACCELERATION);

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
  // If the limit switch is not found with a limitted number of steps, initialization fails
  if (startupFailed) {
    while (true) {
      // just stay here, no movement of the stepper motor is allowed
      delay(10);
    }
  } else if (!startupComplete) {
    // Move to the limit switch
    // if not found enter error mode
    if (!moveToLimitSwitch(STEPS_PER_ROTATION / 2)) {
      // The limit switch wasn't found
      startupFailed = true;
      Serial.println("Start failed. Limit switch not found.");
      stepperMotor.setTargetPositionToStop();

      return;
    }

    calculateStepperLimits();
    stepperMotor.moveToPositionInSteps(stepperCenter); // Blocking until the move is complete

    startupComplete = true;
    Serial.println("Initialization completed successfully!");
  } else {
    // Startup is finished, handle steering

    long currentStepperPosition = stepperMotor.getCurrentPositionInSteps();

    // if the limit switch is not pressed
    if (!limitSwitchPressed()) {

      uint16_t currentScaledTarget = getCurrentScaledTarget();
      long currentStepperTarget;
      
      if (STEERING_DIRECTION_NORMAL) {
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

// This function blocks until either the limit switch is found
// or the max number of steps have been reached
boolean moveToLimitSwitch(long maxSteps) {
  stepperMotor.setCurrentPositionInSteps(0);

  if (DIRECTION_TO_LIMIT_SWITCH_CLOCKWISE) {
    stepperMotor.setTargetPositionInSteps(maxSteps);
  } else {
    stepperMotor.setTargetPositionInSteps(-maxSteps);
  }

  while (!stepperMotor.motionComplete()) {
    if (limitSwitchPressed()) {
      return true;
    }
    stepperMotor.processMovement();
  }

  return false;
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
  #if defined(CENTER_STARTUP_MODE)
    return false;
  #else
    return digitalRead(LIMIT_SWITCH_PIN);
  #endif
}

void calculateStepperLimits() {
  long switchPosition = stepperMotor.getCurrentPositionInSteps();

  Serial.print("Switch Position: ");
  Serial.println(switchPosition);

  if (DIRECTION_TO_LIMIT_SWITCH_CLOCKWISE) {
    stepperMax = switchPosition - bufferFromSwitchInSteps;
    stepperCenter = stepperMax - (rangeSteps / 2);
    stepperMin = stepperMax - rangeSteps;
  } else {
    stepperMin = switchPosition + bufferFromSwitchInSteps;
    stepperCenter = stepperMin + (rangeSteps / 2);
    stepperMax = stepperMin + rangeSteps;
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

  stepperMin = switchPosition - (rangeSteps / 2);
  stepperCenter = switchPosition;
  stepperMax = switchPosition + (rangeSteps / 2);

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

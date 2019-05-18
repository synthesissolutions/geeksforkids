/**
 * 
 * Sample code to demonstrate reading of the PWM singals from an RC controller to the Teensy 3.6
 * 
 * A few things to note ...
 *    - currently set up to pins 36 (steering) and 37 (throttle).  Easily reconfigured via the pin numbers
 *    - much of this code is based on the original code (from the previous aruduino base) - loads of clean up is necessary
 *    - this is still interrupt driven
 *    - the output (in the serial console from b/c the debugging flag is on) will be the PWM signal length.  Would be better to have a scaling factor to turn this into a cannonical scale (0-1, or 0-100, or ...)
 */

#define PIN_RC_STEERING            36         // INPUT -- steering
#define PIN_RC_THROTTLE            37         // INPUT -- throttle
#define PIN_ESC_THROTTLE           9         // OUTPUT
#define PIN_STEERING_LEFT          6
#define PIN_STEERING_RIGHT         8
#define PIN_STEERING_ENABLE        7
#define PIN_JOYSTICK_STEERING      A9
#define PIN_STEERING_POSITION      A8
#define PIN_JOYSTICK_THROTTLE      A7
#define PIN_THROTTLE_FORWARD       10
#define PIN_THROTTLE_REVERSE       11
#define PIN_THROTTLE_SPEED         9

#define STEERING_MIN               200   // These numbers need to be tuned to maximum wheel turn amount
#define STEERING_MAX               800
#define STEERING_CENTER            500
#define STEERING_STOP_DELTA        10      // How close to target before stopping so we don't oscillate between 2 numbers
#define STEERING_START_DELTA       25      // How close to target before starting so we don't oscillate between 2 numbers
#define STEERING_SPEED             255   // PWM Value from 0 - 255 with 255 = max speed

#define OVERRIDE_TIMEOUT           4000     // in millis
#define OVERRIDE_THRESHOLD         50        // the window around resting which the parental controls must be out of in order to override the car controls
#define VELOCITY_INCR              0.35       // this sets the rate at which changes can be made to the PWM output signal -- higher the setting, faster the change

#define RC_IDLE                    1500
#define RC_MAX                     2000
#define RC_REV                     1000
#define RC_LEFT                    1000
#define RC_RIGHT                   2000
#define RC_LIMIT                   2500
#define RC_BUFFER_LIMIT            16
#define DEBUGGING                  true     // triggers additional logging over the serial line
#define DEBUGGING_JOYSTICK         false

#define ACCELERATION_RATE          0.00133  //amount of power change per milisecond in acceleration
#define DECELERATION_RATE          0.00267  //amount of power change per milisecond in deceleration

volatile int prevTime_steering = 0;
volatile int idxSteering = 0;
int timesSteering[RC_BUFFER_LIMIT];
volatile int prevTime_Throttle = 0;
volatile int idxThrottle = 0;
int timesThrottle[RC_BUFFER_LIMIT];
bool inPulseSteering = false;
bool inPulseThrottle = false;
int rcSteeringPositionPWM = RC_IDLE;
float rcSteeringPositionPercent = 0.5;      // 50% represents center, 0% is full left and 100% is full right
int lastPulseThrottle = RC_IDLE;
int sameIdxCount = 0;
int lastIdx = 0;
bool RCrecvd = false;
unsigned long timeSinceOverride = OVERRIDE_TIMEOUT;
unsigned int passes = 0;
float lastYpwm = RC_IDLE;
int throttleSignal = 185;

int joystickSteering = 512;                 // Reading from X axis of joystick 0 - 1024
float joystickSteeringPercent = 0.5;        // 50% represents center, 0% is full left and 100% is full right
int joystickThrottle = 512;                 // Reading from Y axis of joystick 0 - 1024
float joystickThrottlePercent = 0.5;        // 50% represents center, 0% is full left and 100% is full right
int steeringPosition = 0;                   // Reading from the Linear Actuator
int steeringTarget = 500;
float currentThrottlePercent = 0.5;    
float throttleTargetPercent = 0.5;
unsigned long throttleLastMillis = 0;
bool isSteering = false;

void resetTimeArrays() {
  // initialize the time arrays, in case there's no RC receiver hooked up
  for (int i = 0; i < RC_BUFFER_LIMIT; i++) {
    timesSteering[i] = RC_IDLE;
    timesThrottle[i] = RC_IDLE;
  }

  RCrecvd = false;
}

/**
 * These three functions go together...
 *    handleSteeringInterrupt handles when the steering PWM input changes state
 *        ... it calls...
 *        (1) risingSteering ... handles when the signal is going high
 *        (2) fallingSteering ... handles when the signal is going low
 */
void handleSteeringInterrupt(){
  if(digitalRead(PIN_RC_STEERING) == 1){
    risingSteering();
  } else {
    fallingSteering();
  }
}

void risingSteering()
{
  if (!inPulseSteering) {
    RCrecvd = true;
    prevTime_steering = micros();
    inPulseSteering = true;
  }
}
 
void fallingSteering() {
  if (inPulseSteering) {
    RCrecvd = true;
    int lastTime = micros()-prevTime_steering;
    if ((lastTime > 0) && (lastTime < RC_LIMIT)) {
      idxSteering = ++idxSteering;
      idxSteering = idxSteering % RC_BUFFER_LIMIT;
      timesSteering[idxSteering] = lastTime;
    }
    inPulseSteering = false;
  }
}

/**
 * These three functions go together...
 *    handleThrottleInterrupt handles when the throttle PWM input changes state
 *        ... it calls...
 *        (1) risingThrottle ... handles when the signal is going high
 *        (2) fallingThrottle ... handles when the signal is going low
 */
void handleThrottleInterrupt(){
  if(digitalRead(PIN_RC_THROTTLE) == 1){
    risingThrottle();
  } else {
    fallingThrottle();
  }
}

void risingThrottle()
{
  if (!inPulseThrottle) {
    RCrecvd = true;
    prevTime_Throttle = micros();
    inPulseThrottle = true;
  }
}
 
void fallingThrottle() {
  if (inPulseThrottle) {
    RCrecvd = true;
    int lastTime = micros()-prevTime_Throttle;
    if ((lastTime > 0) && (lastTime < RC_LIMIT)) {
      idxThrottle = ++idxThrottle;
      idxThrottle = idxThrottle % RC_BUFFER_LIMIT;
      timesThrottle[idxThrottle] = lastTime;
    }
    inPulseThrottle = false;
  }
}


/**
 * Setup RC Interrupts, Steering Motor Controller Pins
 */
void setup() {
  pinMode(PIN_RC_STEERING, INPUT_PULLUP); 
  attachInterrupt(digitalPinToInterrupt(PIN_RC_STEERING), &handleSteeringInterrupt, CHANGE);
  
  pinMode(PIN_RC_THROTTLE, INPUT_PULLUP); 
  attachInterrupt(digitalPinToInterrupt(PIN_RC_THROTTLE), &handleThrottleInterrupt, CHANGE);

  pinMode(PIN_STEERING_LEFT, OUTPUT);
  pinMode(PIN_STEERING_RIGHT, OUTPUT);
  pinMode(PIN_STEERING_ENABLE, OUTPUT);
  analogWrite(PIN_STEERING_ENABLE, STEERING_SPEED);
}


/**
 * there's some extra stuff here... but the biggest thing is the debugging output
 * 
 */
void loop() {

  passes = passes + 1;
  
  int iX_J = 0;
  int iY_J = 0;
  int iX_PWM = RC_IDLE;
  int iY_PWM = RC_IDLE;

  byte override = false;

  // monitor the RC input -- if no inputs for a while, force the current steering command to idle.  Otherwise, if a remote is switched off while driving,
  // that command will never stop and cannot be overridden by the child.
  //
  //  NOTE: THIS IS PROBABLY A BIT INCORRECT.  THE INDEX COUNTING METHOD USED HERE IS VERY DEPENDENT UPON CPU SPEED.  SHOULD PROBABLY BE TIME BASED!
  //
  int iCurIdxSteering = idxSteering;
  if (iCurIdxSteering == lastIdx) { 
    sameIdxCount++;
  }
  else {
    sameIdxCount = 0;
    lastIdx = iCurIdxSteering;
  }

  // it's been too long, reset the RC arrays to idle.
  //
  //   NOTE: SEE THE PREVIOUS NOTE ABOUT THE INDEX COUNTING
  //
  if ((sameIdxCount > 2000) && RCrecvd) { 
    resetTimeArrays();  
    sameIdxCount = 0;
  }
  
  // confirm that the input is good (within bounds) and beyond the OVERRIDE_THRESHOLD
  if (abs(timesSteering[iCurIdxSteering] - RC_IDLE) > OVERRIDE_THRESHOLD) {
    if (rcSteeringPositionPWM != timesSteering[iCurIdxSteering]) {
      if (DEBUGGING) {
        Serial.print("idxSteering: ");
        Serial.print(iCurIdxSteering);
        Serial.print(" (");
        Serial.print(timesSteering[iCurIdxSteering]);
        Serial.println(")");
        
        Serial.print("overriding X with ");
        Serial.println(iX_PWM);  
      }
      rcSteeringPositionPWM = timesSteering[iCurIdxSteering];
      calculateRCSteeringPercent();
    }
    
    // the parent has taking over the steering
    override = true;
      timeSinceOverride = millis();
    
    
    iX_PWM = rcSteeringPositionPWM;
    if (DEBUGGING) {
    }
  }
  else rcSteeringPositionPWM = RC_IDLE;

  int iCurIdxThrottle = idxThrottle;
  // confirm that the input is good (within bounds) and beyond the OVERRIDE_THRESHOLD
  if (abs(timesThrottle[iCurIdxThrottle] - RC_IDLE) > OVERRIDE_THRESHOLD) {
    if (lastPulseThrottle != timesThrottle[iCurIdxThrottle]) {
      if (DEBUGGING) {
        Serial.print("idxThrottle: ");
        Serial.print(iCurIdxThrottle);
        Serial.print(" (");
        Serial.print(timesThrottle[iCurIdxThrottle]);
        Serial.print(") ");
      }
      lastPulseThrottle = timesThrottle[iCurIdxThrottle];
    }
    // the parent has taken over the throttle
    override = true;
    timeSinceOverride = millis();
    iY_PWM = lastPulseThrottle;
    if (DEBUGGING) {
      Serial.print("overriding Y with ");
      Serial.println(iY_PWM);  
    }
  }
  else lastPulseThrottle = RC_IDLE;

  // is the override still in effect?
  if ((millis() - timeSinceOverride) < OVERRIDE_TIMEOUT) override = true;

  readInputs();
  calculateJoystickSteeringPercent();
  calculateJoystickThrottlePercent();
  calculateSteeringTarget(override);
  applySteering();
  applyThrottle();
/*
  if (abs(iY_PWM - lastYpwm) < VELOCITY_INCR) lastYpwm = iY_PWM;
  if (iY_PWM > lastYpwm) 
    lastYpwm += VELOCITY_INCR;
  else if (iY_PWM < lastYpwm)
    lastYpwm -= (VELOCITY_INCR);
  if (DEBUGGING) Serial.println(lastYpwm);
*/
/*
  //escThrottle.writeMicroseconds(int(lastYpwm));
  //escThrottle.write(75);
  // Do we need the servo library? Teensy can write PWM signal natively.
  throttleSignal = map(int(lastYpwm), 850, 2100, 130, 250);
      if (DEBUGGING) {
      Serial.print("throttleSignal: ");
      Serial.println(throttleSignal);  
    }
  analogWrite(PIN_ESC_THROTTLE, throttleSignal);
*/
}

void readInputs() {
  joystickSteering = analogRead(PIN_JOYSTICK_STEERING);
  steeringPosition = analogRead(PIN_STEERING_POSITION); 
  joystickThrottle = analogRead(PIN_JOYSTICK_THROTTLE);  

  if (DEBUGGING_JOYSTICK) {
    Serial.print("Joystick X: ");
    Serial.println(joystickSteering);
    Serial.print("Steering Position: ");
    Serial.println(steeringPosition);
  }
}

void calculateSteeringTarget(byte override) {
  int targetPercent;
  if (override) {
    targetPercent = int(rcSteeringPositionPercent * 100);
  } else {
    targetPercent = int(joystickSteeringPercent * 100);
  }
  steeringTarget = constrain(map(targetPercent, 0, 100, STEERING_MIN, STEERING_MAX), STEERING_MIN, STEERING_MAX);
}

void applyThrottle() {
  int speed;
  if(joystickThrottlePercent>0.575 || joystickThrottlePercent<0.425){
    if(abs(joystickThrottlePercent-throttleTargetPercent)>0.05){
      throttleTargetPercent = joystickThrottlePercent;
    }
    if(throttleTargetPercent>currentThrottlePercent){
      speed = (currentThrottlePercent + ((millis()-throttleLastMillis)*ACCELERATION_RATE)*100);
      digitalWrite(PIN_THROTTLE_FORWARD, HIGH);
      digitalWrite(PIN_THROTTLE_REVERSE, LOW);
      analogWrite(PIN_THROTTLE_SPEED, speed);
    } else if (throttleTargetPercent<currentThrottlePercent) {
      speed = (currentThrottlePercent - ((millis()-throttleLastMillis)*ACCELERATION_RATE)*100);
      digitalWrite(PIN_THROTTLE_FORWARD, LOW);
      digitalWrite(PIN_THROTTLE_REVERSE, HIGH);
      analogWrite(PIN_THROTTLE_SPEED, speed);
    } else {
      throttleLastMillis = millis();
    }
  } else {
    speed = 0;
    digitalWrite(PIN_THROTTLE_FORWARD, LOW);
    digitalWrite(PIN_THROTTLE_REVERSE, LOW);
    analogWrite(PIN_THROTTLE_SPEED, speed);
    throttleLastMillis = millis();
  }
  Serial.print("speed ::");
  Serial.println(speed);
}

void applySteering() {
  int targetDelta = abs(steeringPosition - steeringTarget);

  // If we are currently steering only stop when we get really close to our target
  // However, if we have stopped steering, don't start up again until we get a little
  // farther from our target to avoid osciallation
  if ((isSteering && (targetDelta <= STEERING_STOP_DELTA)) 
      || (!isSteering && (targetDelta <= STEERING_START_DELTA))) {
    stopTurning();
  } else if (steeringPosition < steeringTarget) {
    turnLeft();
  } else {
    turnRight();
  }
}

void turnLeft() {
  if (DEBUGGING) {
    Serial.print("Turning Left: ");
    Serial.print(joystickSteeringPercent);
    Serial.print(" ");
    Serial.print(rcSteeringPositionPercent);
    Serial.print(" Target: ");
    Serial.print(steeringTarget);
    Serial.print("  Position: ");
    Serial.println(steeringPosition);
  }

  isSteering = true;
  digitalWrite(PIN_STEERING_LEFT, HIGH);
  digitalWrite(PIN_STEERING_RIGHT, LOW);    
}

void turnRight() {
  if (DEBUGGING) {
    Serial.print("Turning Right: ");
    Serial.print(joystickSteeringPercent);
    Serial.print(" ");
    Serial.print(rcSteeringPositionPercent);
    Serial.print(" Target: ");
    Serial.print(steeringTarget);
    Serial.print("  Position: ");
    Serial.println(steeringPosition);
  }

  isSteering = true;
  digitalWrite(PIN_STEERING_LEFT, LOW);
  digitalWrite(PIN_STEERING_RIGHT, HIGH);    
}

void stopTurning() {
  isSteering = false;
  digitalWrite(PIN_STEERING_LEFT, LOW);
  digitalWrite(PIN_STEERING_RIGHT, LOW);    
}

void calculateRCSteeringPercent() {
  rcSteeringPositionPercent = constrain(float(rcSteeringPositionPWM - RC_LEFT) / float(RC_RIGHT - RC_LEFT), 0.0, 1.0);
  
  if (DEBUGGING) {
    Serial.print("RC Steering Percentage: ");
    Serial.println(rcSteeringPositionPercent);
  }
}

void calculateJoystickSteeringPercent() {
  joystickSteeringPercent = constrain(float(joystickSteering) / 1024.0, 0.0, 1.0);
  
  if (DEBUGGING_JOYSTICK) {
    Serial.print("Joystick Steering Percentage: ");
    Serial.println(joystickSteeringPercent);
  }
}

void calculateJoystickThrottlePercent() {
  joystickThrottlePercent = constrain(float(joystickThrottle) / 1024.0, 0.0, 1.0);
  Serial.print("joystickThrottlePercent ");
  Serial.println(joystickThrottlePercent);
}

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

volatile int iPrevTime_steering = 0;
volatile int iIdxSteering = 0;
int aiTimesSteering[RC_BUFFER_LIMIT];
volatile int iPrevTime_Throttle = 0;
volatile int iIdxThrottle = 0;
int aiTimesThrottle[RC_BUFFER_LIMIT];
bool bInPulseSteering = false;
bool bInPulseThrottle = false;
int rcSteeringPositionPWM = RC_IDLE;
float rcSteeringPositionPercent = 0.5;      // 50% represents center, 0% is full left and 100% is full right
int iLastPulseThrottle = RC_IDLE;
int iSameIdxCount = 0;
int iLastIdx = 0;
bool bRCrecvd = false;
unsigned long ulTimeSinceOverride = OVERRIDE_TIMEOUT;
unsigned int iPasses = 0;
float fLastYpwm = RC_IDLE;
int iThrottleSignal = 185;

int joystickSteering = 512;                 // Reading from X axis of joystick 0 - 1024
float joystickSteeringPercent = 0.5;        // 50% represents center, 0% is full left and 100% is full right
int steeringPosition = 0;                   // Reading from the Linear Actuator
int steeringTarget = 500;
bool isSteering = false;

void resetTimeArrays() {
  // initialize the time arrays, in case there's no RC receiver hooked up
  for (int i = 0; i < RC_BUFFER_LIMIT; i++) {
    aiTimesSteering[i] = RC_IDLE;
    aiTimesThrottle[i] = RC_IDLE;
  }

  bRCrecvd = false;
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
  if (!bInPulseSteering) {
    bRCrecvd = true;
    iPrevTime_steering = micros();
    bInPulseSteering = true;
  }
}
 
void fallingSteering() {
  if (bInPulseSteering) {
    bRCrecvd = true;
    int lastTime = micros()-iPrevTime_steering;
    if ((lastTime > 0) && (lastTime < RC_LIMIT)) {
      iIdxSteering = ++iIdxSteering;
      iIdxSteering = iIdxSteering % RC_BUFFER_LIMIT;
      aiTimesSteering[iIdxSteering] = lastTime;
    }
    bInPulseSteering = false;
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
  if (!bInPulseThrottle) {
    bRCrecvd = true;
    iPrevTime_Throttle = micros();
    bInPulseThrottle = true;
  }
}
 
void fallingThrottle() {
  if (bInPulseThrottle) {
    bRCrecvd = true;
    int lastTime = micros()-iPrevTime_Throttle;
    if ((lastTime > 0) && (lastTime < RC_LIMIT)) {
      iIdxThrottle = ++iIdxThrottle;
      iIdxThrottle = iIdxThrottle % RC_BUFFER_LIMIT;
      aiTimesThrottle[iIdxThrottle] = lastTime;
    }
    bInPulseThrottle = false;
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

  iPasses = iPasses + 1;
  
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
  int iCurIdxSteering = iIdxSteering;
  if (iCurIdxSteering == iLastIdx) { 
    iSameIdxCount++;
  }
  else {
    iSameIdxCount = 0;
    iLastIdx = iCurIdxSteering;
  }

  // it's been too long, reset the RC arrays to idle.
  //
  //   NOTE: SEE THE PREVIOUS NOTE ABOUT THE INDEX COUNTING
  //
  if ((iSameIdxCount > 2000) && bRCrecvd) { 
    resetTimeArrays();  
    iSameIdxCount = 0;
  }
  
  // confirm that the input is good (within bounds) and beyond the OVERRIDE_THRESHOLD
  if (abs(aiTimesSteering[iCurIdxSteering] - RC_IDLE) > OVERRIDE_THRESHOLD) {
    if (rcSteeringPositionPWM != aiTimesSteering[iCurIdxSteering]) {
      if (DEBUGGING) {
        Serial.print("iIdxSteering: ");
        Serial.print(iCurIdxSteering);
        Serial.print(" (");
        Serial.print(aiTimesSteering[iCurIdxSteering]);
        Serial.println(")");
        
        Serial.print("overriding X with ");
        Serial.println(iX_PWM);  
      }
      rcSteeringPositionPWM = aiTimesSteering[iCurIdxSteering];
      calculateRCSteeringPercent();
    }
    
    // the parent has taking over the steering
    override = true;
      ulTimeSinceOverride = millis();
    
    
    iX_PWM = rcSteeringPositionPWM;
    if (DEBUGGING) {
    }
  }
  else rcSteeringPositionPWM = RC_IDLE;

  int iCurIdxThrottle = iIdxThrottle;
  // confirm that the input is good (within bounds) and beyond the OVERRIDE_THRESHOLD
  if (abs(aiTimesThrottle[iCurIdxThrottle] - RC_IDLE) > OVERRIDE_THRESHOLD) {
    if (iLastPulseThrottle != aiTimesThrottle[iCurIdxThrottle]) {
      if (DEBUGGING) {
        Serial.print("iIdxThrottle: ");
        Serial.print(iCurIdxThrottle);
        Serial.print(" (");
        Serial.print(aiTimesThrottle[iCurIdxThrottle]);
        Serial.print(") ");
      }
      iLastPulseThrottle = aiTimesThrottle[iCurIdxThrottle];
    }
    // the parent has taken over the throttle
    override = true;
    ulTimeSinceOverride = millis();
    iY_PWM = iLastPulseThrottle;
    if (DEBUGGING) {
      Serial.print("overriding Y with ");
      Serial.println(iY_PWM);  
    }
  }
  else iLastPulseThrottle = RC_IDLE;

  // is the override still in effect?
  if ((millis() - ulTimeSinceOverride) < OVERRIDE_TIMEOUT) override = true;

  readInputs();
  calculateJoystickSteeringPercent();
  calculateSteeringTarget(override);
  applySteering();
/*
  if (abs(iY_PWM - fLastYpwm) < VELOCITY_INCR) fLastYpwm = iY_PWM;
  if (iY_PWM > fLastYpwm) 
    fLastYpwm += VELOCITY_INCR;
  else if (iY_PWM < fLastYpwm)
    fLastYpwm -= (VELOCITY_INCR);
  if (DEBUGGING) Serial.println(fLastYpwm);
*/
/*
  //escThrottle.writeMicroseconds(int(fLastYpwm));
  //escThrottle.write(75);
  // Do we need the servo library? Teensy can write PWM signal natively.
  iThrottleSignal = map(int(fLastYpwm), 850, 2100, 130, 250);
      if (DEBUGGING) {
      Serial.print("iThrottleSignal: ");
      Serial.println(iThrottleSignal);  
    }
  analogWrite(PIN_ESC_THROTTLE, iThrottleSignal);
*/
}

void readInputs() {
  joystickSteering = analogRead(PIN_JOYSTICK_STEERING);
  steeringPosition = analogRead(PIN_STEERING_POSITION);  

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


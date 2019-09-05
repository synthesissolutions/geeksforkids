#include <Servo.h>
#include <PinChangeInt.h>
#include <Bounce2.h>
 
int     LINACT_RANGE;     // calculated at startup from the MAX and MIN values
#define RC_IDLE                    1500
#define RC_MAX                     2000
#define RC_REV                     1000
#define RC_LEFT                    1000
#define RC_RIGHT                   2000
#define RC_LIMIT                   2500
#define RC_BUFFER_LIMIT            16
#define DEBUGGING                  false     // triggers additional logging over the serial line
#define LIN_ACT_READ_COUNT         6
Servo escSteering;
Servo escThrottle;

Bounce bncLeft;
Bounce bncFwd;
Bounce bncRight;
Bounce bncReverse;

volatile int iPrevTime_steering = 0;
volatile int iIdxSteering = 0;
int aiTimesSteering[RC_BUFFER_LIMIT];
volatile int iPrevTime_Throttle = 0;
volatile int iIdxThrottle = 0;
int aiTimesThrottle[RC_BUFFER_LIMIT];
bool bInPulseSteering = false;
bool bInPulseThrottle = false;
int iLastPulseSteering = RC_IDLE;
int iLastPulseThrottle = RC_IDLE;
float fLastXpwm = RC_IDLE;
float fLastYpwm = RC_IDLE;
int iSameIdxCount = 0;
int iLastIdx = 0;
bool bRCrecvd = false;
int aiLinActReads[LIN_ACT_READ_COUNT];
int iLinActReadIdx = 0;
unsigned long ulTimeSinceOverride = OVERRIDE_TIMEOUT;
unsigned int iPasses = 0;
bool SINGLE_THROTTLE_BUTTON = false;

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


void resetTimeArrays() {
  // initialize the time arrays, in case there's no RC receiver hooked up
  for (int i = 0; i < RC_BUFFER_LIMIT; i++) {
    aiTimesSteering[i] = RC_IDLE;
    aiTimesThrottle[i] = RC_IDLE;
  }
  Serial.println("*");
  bRCrecvd = false;
}

int getAverageLinActPos() {
  iLinActReadIdx++;
  iLinActReadIdx = iLinActReadIdx % LIN_ACT_READ_COUNT;
  aiLinActReads[iLinActReadIdx] = analogRead(PIN_LINACT_STEERING);
  if (LINACT_CALIBRATE) {
    Serial.print("linact pos: ");
    Serial.println(aiLinActReads[iLinActReadIdx]);
  }
  long lReads = 0;
  for (int i = 0; i < LIN_ACT_READ_COUNT; i++) {
    lReads = lReads + aiLinActReads[i];
  }

  return int(lReads / LIN_ACT_READ_COUNT);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // drive system
  Serial.print("attaching to servo pin...");
  escSteering.attach(PIN_ESC_STEERING);
  escThrottle.attach(PIN_ESC_THROTTLE);
  Serial.println("done");
  escSteering.writeMicroseconds(RC_IDLE);
  escThrottle.writeMicroseconds(RC_IDLE);
  delay(1000);
  Serial.println("X and Y servos ready");

  // RC monitoring system
  resetTimeArrays();
  pinMode(PIN_RC_STEERING, INPUT); 
  digitalWrite(PIN_RC_STEERING, HIGH);
  PCintPort::attachInterrupt(PIN_RC_STEERING, &risingSteering, RISING);
  PCintPort::attachInterrupt(PIN_RC_STEERING, &fallingSteering, FALLING);

  pinMode(PIN_RC_THROTTLE, INPUT); 
  digitalWrite(PIN_RC_THROTTLE, HIGH);
  PCintPort::attachInterrupt(PIN_RC_THROTTLE, &risingThrottle, RISING);
  PCintPort::attachInterrupt(PIN_RC_THROTTLE, &fallingThrottle, FALLING);

  SINGLE_THROTTLE_BUTTON = USE_FWD && !USE_LEFT && !USE_RIGHT;

  if (USE_FWD) {
    bncFwd = Bounce();
    pinMode(PIN_FWD, INPUT);
    digitalWrite(PIN_FWD, HIGH);
    bncFwd.attach(PIN_FWD);
    bncFwd.interval(5);
  }

  if (USE_LEFT) {
    bncLeft = Bounce();
    pinMode(PIN_LEFT, INPUT);
    digitalWrite(PIN_LEFT, HIGH);
    bncLeft.attach(PIN_LEFT);
    bncLeft.interval(5);  
  }

  if (USE_RIGHT) {
    bncRight = Bounce();
    pinMode(PIN_RIGHT, INPUT);
    digitalWrite(PIN_RIGHT, HIGH);
    bncRight.attach(PIN_RIGHT);
    bncRight.interval(5);  
  }

  if (USE_REVERSE) {
    bncReverse = Bounce();
    pinMode(PIN_REVERSE, INPUT);
    digitalWrite(PIN_REVERSE, HIGH);
    bncReverse.attach(PIN_REVERSE);
    bncReverse.interval(5);
  }
  
  if (PIN_LINACT_ENABLE) {
    LINACT_RANGE = LINACT_MAX - LINACT_MIN;
    for (int i = 0; i < LIN_ACT_READ_COUNT; i++) {
      aiLinActReads[i] = analogRead(PIN_LINACT_STEERING);
    }
  }
  Serial.println("RC buffer initialized, input pins configured");
}

void loop() {
  iPasses = iPasses + 1;
  
  int iX_J = 0;
  int iY_J = 0;
  int iX_PWM = RC_IDLE;
  int iY_PWM = RC_IDLE;

  byte override = false;

  // if using the governor, check it
  if (USE_GOVERNOR) {
    RC_THROTTLE_GOVERNOR = map(analogRead(PIN_GOVERNOR), 0, 1024, 0, 400);
  }

  // monitor the RC input -- if no inputs for a while, force the current steering command to idle.  Otherwise, if a remote is switched off while driving,
  // that command will never stop and cannot be overridden by the child.
  int iCurIdxSteering = iIdxSteering;
  if (iCurIdxSteering == iLastIdx) { 
    iSameIdxCount++;
  }
  else {
    iSameIdxCount = 0;
    iLastIdx = iCurIdxSteering;
  }

  // it's been too long, reset the RC arrays to idle.
  if ((iSameIdxCount > 2000) && bRCrecvd) { 
    resetTimeArrays();  
    iSameIdxCount = 0;
  }

    // confirm that the input is good (within bounds) and beyond the OVERRIDE_THRESHOLD
  if (abs(aiTimesSteering[iCurIdxSteering] - RC_IDLE) > OVERRIDE_THRESHOLD) {
    if (iLastPulseSteering != aiTimesSteering[iCurIdxSteering]) {
      if (DEBUGGING) {
        Serial.print("iIdxSteering: ");
        Serial.print(iCurIdxSteering);
        Serial.print(" (");
        Serial.print(aiTimesSteering[iCurIdxSteering]);
        Serial.println(")");
      }
      iLastPulseSteering = aiTimesSteering[iCurIdxSteering];
    }
    
    // the parent has taking over the steering
    if (!SINGLE_THROTTLE_BUTTON) {
      override = true;
      ulTimeSinceOverride = millis();
    }
    
    iX_PWM = iLastPulseSteering;
    if (DEBUGGING) {
      Serial.print("overriding X with ");
      Serial.println(iX_PWM);  
    }
  }
  else iLastPulseSteering = RC_IDLE;
  
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
  
  if (!override && USE_JOYSTICK_STEERING) {  // if the parent isn't overriding, get the kid's input
    iX_J = analogRead(PIN_JOYSTICK_STEERING);
    iX_PWM = map(iX_J, 0, 1024, RC_LEFT, RC_RIGHT);
  }

  if (!override && USE_JOYSTICK_THROTTLE) {
    iY_J = analogRead(PIN_JOYSTICK_THROTTLE);
    iY_PWM = map(iY_J, 0, 1024, RC_REV + RC_THROTTLE_GOVERNOR, RC_MAX - RC_THROTTLE_GOVERNOR);
  }

  if (!override && USE_FWD) {
    bncFwd.update();
    if (!bncFwd.read()) {
      iY_PWM = RC_MAX - RC_THROTTLE_GOVERNOR;
    }
  }

  if (!override && USE_LEFT) {
    bncLeft.update();
    if (!bncLeft.read()) {
      iX_PWM = RC_LEFT;
      iY_PWM = RC_MAX - RC_THROTTLE_GOVERNOR;
    }
  }

  if (!override && USE_RIGHT) {
    bncRight.update();
    if (!bncRight.read()) {
      iX_PWM = RC_RIGHT;
      iY_PWM = RC_MAX - RC_THROTTLE_GOVERNOR;
    }
  }
  
// translate the incoming PWM command into a constant direction
  if (PIN_LINACT_ENABLE) {
    int iLinPos = getAverageLinActPos();                                          // where is the linear actuator currently at
    int iTarPos = 0;
    if (LINACT_CALIBRATE) {
      iTarPos = map(iX_PWM, RC_LEFT, RC_RIGHT + 1, 0, 1023);     // target, translated into the linear actuator context
    }
    else {    // !LINACT_CALIBRATE 
      iTarPos = map(iX_PWM, RC_LEFT, RC_RIGHT + 1, LINACT_MIN, LINACT_MAX);     // target, translated into the linear actuator context
      if (abs(iLinPos - LINACT_MIN) < 5 && (iTarPos <= iLinPos)) {
        iX_PWM = RC_IDLE;
      }
      else if (abs(iLinPos - LINACT_MAX) < 5 && (iTarPos >= iLinPos)) {
        iX_PWM = RC_IDLE;
      }
      else {
        if (iLinPos > iTarPos) {
          iX_PWM = map(constrain((iLinPos - iTarPos)*4, 0, LINACT_RANGE), 0, LINACT_RANGE, RC_IDLE, RC_RIGHT);
        }
        else {
          iX_PWM = map(constrain((iTarPos - iLinPos)*4, 0, LINACT_RANGE), 0, LINACT_RANGE, RC_IDLE, RC_LEFT);
        }
      }
    }
  }
  
  if (!override && USE_REVERSE) {
    bncReverse.update();
    if (!bncReverse.read()) {
      iY_PWM = RC_MAX - iY_PWM + RC_REV;
    }
  }
  
  if (abs(iY_PWM - fLastYpwm) < VELOCITY_INCR) fLastYpwm = iY_PWM;
  if (iY_PWM > fLastYpwm) 
    fLastYpwm += VELOCITY_INCR;
  else if (iY_PWM < fLastYpwm)
    fLastYpwm -= (VELOCITY_INCR);
  if (DEBUGGING) Serial.println(fLastYpwm);

  escThrottle.writeMicroseconds(int(fLastYpwm));

  escSteering.writeMicroseconds(iX_PWM);
}




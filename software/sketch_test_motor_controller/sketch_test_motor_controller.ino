#define PIN_THROTTLE_FORWARD      10
#define PIN_THROTTLE_REVERSE      11
#define PIN_THROTTLE_SPEED        9
#define PIN_JOYSTICK_THROTTLE     A9

#define PWM_MIN                   0
#define PWM_MAX                   250 // Don't send full 255 signal for PWM, the motor controllers can't handle it

#define JOYSTICK_CENTER           512
#define THROTTLE_CENTER_MARGIN    0.1 // Percentage from center to ignore

#define DEBUGGING                 true
#define DEBUGGING_JOYSTICK        false

int joystickThrottle = 512;   // Reading from Y axis of joystick 0 - 1024
float joystickThrottlePercent = 0.0;  // Percentage of speed in given direction, -1.0 max reverse, +1.0 max forward

void setup() {
  pinMode(PIN_THROTTLE_FORWARD, OUTPUT);
  pinMode(PIN_THROTTLE_REVERSE, OUTPUT);
  pinMode(PIN_THROTTLE_SPEED, OUTPUT);
  analogWrite(PIN_THROTTLE_SPEED, PWM_MIN);
}

void loop() {
  readInputs();
  calculateJoystickThrottlePercent();
  applyThrottle();
}

void readInputs() {
  joystickThrottle = analogRead(PIN_JOYSTICK_THROTTLE);

  if (DEBUGGING_JOYSTICK) {
    Serial.print("Joystick Y: ");
    Serial.println(joystickThrottle);
  }
}

void applyThrottle() {
  int pwmSpeed = calculateThrottlePWMOutput(abs(joystickThrottlePercent));
  
  if (joystickThrottlePercent > THROTTLE_CENTER_MARGIN) {
    throttleForward(pwmSpeed);
  } else if (joystickThrottlePercent < -THROTTLE_CENTER_MARGIN) {
    throttleReverse(pwmSpeed);
  } else {
    throttleStop();
  }
}

void throttleStop() {
  digitalWrite(PIN_THROTTLE_FORWARD, LOW);
  digitalWrite(PIN_THROTTLE_REVERSE, LOW);
  analogWrite(PIN_THROTTLE_SPEED, 0);
}

void throttleForward(int speed) {
  if (DEBUGGING) {
    Serial.print("Throttle Forward: ");
    Serial.println(speed);
  }
  digitalWrite(PIN_THROTTLE_FORWARD, HIGH);
  digitalWrite(PIN_THROTTLE_REVERSE, LOW);
  analogWrite(PIN_THROTTLE_SPEED, speed);
}

void throttleReverse(int speed) {
  if (DEBUGGING) {
    Serial.print("Throttle Reverse: ");
    Serial.println(speed);
  }
  digitalWrite(PIN_THROTTLE_FORWARD, LOW);
  digitalWrite(PIN_THROTTLE_REVERSE, HIGH);
  analogWrite(PIN_THROTTLE_SPEED, speed);
}

void calculateJoystickThrottlePercent() {
  int deltaFromCenter = joystickThrottle - JOYSTICK_CENTER;
  joystickThrottlePercent = constrain(float(deltaFromCenter) / 512.0, -1.0, 1.0);
  
  if (DEBUGGING_JOYSTICK) {
    Serial.print("Joystick Throttle Percentage: ");
    Serial.print(joystickThrottlePercent);
    Serial.print("   ");
    Serial.println(deltaFromCenter);
  }
}

int calculateThrottlePWMOutput(float percent) {
  int targetPercent = int(percent * 100);
  return constrain(map(targetPercent, 0, 100, PWM_MIN, PWM_MAX), PWM_MIN, PWM_MAX);
}


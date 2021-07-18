const int DRIVE_STRAIGHT_BUTTON_PIN = A1;
const int DRIVE_RIGHT_BUTTON_PIN = A3;
const int DRIVE_LEFT_BUTTON_PIN = A2;
const int REVERSE_BUTTON_PIN = A6;

const int THROTTLE_PWM_PIN = 1;
const int STEERING_PWM_PIN = 0;

const int THROTTLE_OFF = 127;
const int THROTTLE_FORWARD = 254;
const int THROTTLE_REVERSE = 1;

const int STEERING_STRAIGHT = 127;
const int STEERING_LEFT = 1;
const int STEERING_RIGHT = 254;


boolean throttleOn = false;
int throttlePWM = THROTTLE_OFF;
int steeringPWM = STEERING_STRAIGHT;

void setup() {

  Serial.begin(9600);

  pinMode(DRIVE_STRAIGHT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DRIVE_RIGHT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DRIVE_LEFT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(REVERSE_BUTTON_PIN, INPUT_PULLUP);
}

boolean IsReverse() {
  return digitalRead(REVERSE_BUTTON_PIN);
}

void loop() {
  if (!digitalRead(DRIVE_STRAIGHT_BUTTON_PIN)) {
    throttleOn = true;
    steeringPWM = STEERING_STRAIGHT;
  } else if (!digitalRead(DRIVE_LEFT_BUTTON_PIN)) {
    throttleOn = true;
    steeringPWM = STEERING_LEFT;    
  } else if (!digitalRead(DRIVE_RIGHT_BUTTON_PIN)) {
    throttleOn = true;
    steeringPWM = STEERING_RIGHT;
  } else {
    throttleOn = false;
    steeringPWM = STEERING_STRAIGHT;
  }

  if (throttleOn) {
    if (IsReverse()) {
      throttlePWM = THROTTLE_REVERSE;
    } else {
      throttlePWM = THROTTLE_FORWARD; 
    }
  } else {
    throttlePWM = THROTTLE_OFF;
  }

  analogWrite(THROTTLE_PWM_PIN, throttlePWM);
  analogWrite(STEERING_PWM_PIN, steeringPWM);

  Serial.print(throttlePWM);
  Serial.print("  ");
  Serial.println(steeringPWM);

  delay(25);
}

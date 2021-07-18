const int GO_BUTTON_PIN = A1;
const int REVERSE_SWITCH_PIN = A6;
const int HALL_SENSOR_PWM_INPUT_PIN = A2;
   
const int THROTTLE_PWM_PIN = 1;
const int STEERING_PWM_PIN = 0;

const int THROTTLE_OFF = 127;
const int THROTTLE_FORWARD = 254;
const int THROTTLE_REVERSE = 1;


boolean throttleOn = false;
int throttlePWM = THROTTLE_OFF;

const int PWM_MIN = 20;
const int PWM_MAX = 800;

boolean steeringSignalHigh;
unsigned long steeringPulseStart;
unsigned long steeringPWMin;
unsigned long steeringPWMout;
    
void pwmIRQHandler() {
  // which state are we handling
  if(digitalRead(HALL_SENSOR_PWM_INPUT_PIN) == 1){
    // rising signal
    // record when the pulse started
    steeringPulseStart = micros();
  } else {
    // falling signal
    // calculate the pulse width in microseconds
    steeringPWMin = micros()-steeringPulseStart;
    steeringPWMin = constrain(steeringPWMin, PWM_MIN, PWM_MAX);
    if (steeringPWMin < 650) {
       steeringPWMout = map(steeringPWMin, PWM_MIN, PWM_MAX, 10, 240);
    }
  }      
}
    
void setup() {

  Serial.begin(9600);

  pinMode(GO_BUTTON_PIN, INPUT_PULLUP);
  pinMode(REVERSE_SWITCH_PIN, INPUT_PULLUP);
  pinMode(HALL_SENSOR_PWM_INPUT_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(HALL_SENSOR_PWM_INPUT_PIN), &pwmIRQHandler, CHANGE);
}

boolean IsReverse() {
  return !digitalRead(REVERSE_SWITCH_PIN);
}

void loop() {
  if (!digitalRead(GO_BUTTON_PIN)) {
    throttleOn = true;
  } else {
    throttleOn = false;
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
  analogWrite(STEERING_PWM_PIN, steeringPWMout);

  Serial.print(throttlePWM);
  Serial.print("  ");
  Serial.println(steeringPWMout);

  delay(25);
}

#define PIN_STEERING_LEFT     6
#define PIN_STEERING_RIGHT    8
#define PIN_STEERING_ENABLE   7
#define PIN_JOYSTICK_STEERING A9
#define PIN_STEERING_POSITION A8

#define STEERING_MIN          200   // These numbers need to be tuned to maximum wheel turn amount
#define STEERING_MAX          800
#define STEERING_CENTER       500
#define STEERING_STOP_DELTA   5      // How close to target before stopping so we don't oscillate between 2 numbers
#define STEERING_START_DELTA  15      // How close to target before starting so we don't oscillate between 2 numbers
#define STEERING_SPEED        255   // PWM Value from 0 - 255 with 255 = max speed

#define DEBUGGING             false

int joystickSteering = 512;   // Reading from X axis of joystick 0 - 1024
int steeringPosition = 0;     // Reading from the Linear Actuator
int steeringTarget = 500;
bool isSteering = false;

void setup() {
  pinMode(PIN_STEERING_LEFT, OUTPUT);
  pinMode(PIN_STEERING_RIGHT, OUTPUT);
  pinMode(PIN_STEERING_ENABLE, OUTPUT);
  analogWrite(PIN_STEERING_ENABLE, STEERING_SPEED);
}

void loop() {
  readInputs();
  calculateSteeringTarget();
  applySteering();
}

void readInputs() {
  joystickSteering = analogRead(PIN_JOYSTICK_STEERING);
  steeringPosition = analogRead(PIN_STEERING_POSITION);  

  if (DEBUGGING) {
    Serial.print("Joystick X: ");
    Serial.println(joystickSteering);
    Serial.print("Steering Position: ");
    Serial.println(steeringPosition);
  }
}

void calculateSteeringTarget() {
  steeringTarget = joystickSteering; // Need something more sophisticated here  
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
  if (!DEBUGGING) {
    Serial.print("Turning Left: ");
    Serial.print(isSteering);
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
  if (!DEBUGGING) {
    Serial.print("Turning Right: ");
    Serial.print(isSteering);
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


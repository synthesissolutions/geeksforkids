const int PWM_SIGNAL_PIN = 5;
const int NUMBER_OF_SENSORS = 9;
const int HALL_SENSOR_PINS[] = {A1, A2, A3, A4, A5, A6, A7, 6, 7};

// Seems to be an issue with using 0 or numbers near 255
const int MIN_PWM = 40;
const int MAX_PWM = 200;

int sensorValue = 0;
int lowestSensorValue = 1000;
int lowestSensorPosition = 4;

void setup() {

  pinMode(PWM_SIGNAL_PIN, OUTPUT);
  for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
    pinMode(HALL_SENSOR_PINS[i], INPUT);
  }
}

void loop() {
  lowestSensorValue = 1000;
  lowestSensorPosition = 4;
  
  for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
    sensorValue = analogRead(HALL_SENSOR_PINS[i]);
    if (sensorValue < lowestSensorValue) {
      lowestSensorValue = sensorValue;
      lowestSensorPosition = i;
    }
  }

  int steeringPwm = map(lowestSensorPosition, 0, NUMBER_OF_SENSORS - 1, MIN_PWM, MAX_PWM);

  analogWrite(PWM_SIGNAL_PIN, steeringPwm);
  
  delay(25);
}

const int PWM_SIGNAL_PIN = 7;
const int NUMBER_OF_SENSORS = 7;
const int HALL_SENSOR_PINS[] = {A1, A2, A3, A4, A5, A6, A7};

int sensorValue = 0;
int lowestSensorValue = 1000;
int lowestSensorPosition = 3;

void setup() {

  Serial.begin(9600);

  pinMode(PWM_SIGNAL_PIN, OUTPUT);
  for (int i = 0; i < 7; i++) {
    pinMode(HALL_SENSOR_PINS[i], INPUT);
  }
}

void loop() {
  lowestSensorValue = 1000;
  lowestSensorPosition = 3;
  
  for (int i = 0; i < 7; i++) {
    sensorValue = analogRead(HALL_SENSOR_PINS[i]);
    if (sensorValue < lowestSensorValue) {
      lowestSensorValue = sensorValue;
      lowestSensorPosition = i;
    }
    
    Serial.print(sensorValue);
    Serial.print("  ");
  }

  int steeringPwm = map(lowestSensorPosition, 0, 6, 0, 255);

  Serial.print("    Current Position: ");
  Serial.print(lowestSensorPosition);
  Serial.print("  PWM Value: ");
  Serial.print(steeringPwm);
  Serial.println();

  analogWrite(PWM_SIGNAL_PIN, steeringPwm);
  
  delay(25);
}

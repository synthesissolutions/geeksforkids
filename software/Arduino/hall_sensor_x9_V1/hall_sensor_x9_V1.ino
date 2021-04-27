const int PWM_SIGNAL_PIN = 5;  // should be pin 5, normally, but this is to clear that pin for serial TX
const int NUMBER_OF_SENSORS = 9;
const int HALL_SENSOR_PINS[] = {A1, A2, A3, A4, A5, A6, A7, 6, 7};
const int MIDDLE_BAND = 120;
int POINT_BAND = 0;

int sensorValue = 0;
int lowestSensorValue = 1000;
int lowestSensorPosition = 3;
int lastReadings[NUMBER_OF_SENSORS];
int sensorPWMOffset[NUMBER_OF_SENSORS];
bool flipOrientation = false;


const int LOG_NONE = 0;
const int LOG_INFO = 1;
const int LOG_DATA = 2;

int logLevel = LOG_NONE;




void setup() {

  // this relationship seems to work the best
  POINT_BAND = MIDDLE_BAND / 2;
  
  if (logLevel > LOG_NONE) {
    Serial.begin(9600); 
    if (logLevel >= LOG_INFO) {
      Serial.println("");
      Serial.println("**** BEGIN ****");
    }
  }

  if (logLevel == LOG_NONE) {
    pinMode(PWM_SIGNAL_PIN, OUTPUT);
    for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
      pinMode(HALL_SENSOR_PINS[i], INPUT);
    }
  }
  
  //calculate PWM offset for each hall sensor
  //i.e., how far along the PWM range from 0 to 1024 is a given sensor
  if (logLevel >= LOG_INFO) {
    Serial.println("hall sensor offsets:");
  }
   
  int pwmSlice = 1024 / (NUMBER_OF_SENSORS - 1);
  for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
    sensorPWMOffset[i] = i * pwmSlice;
    if (logLevel >= LOG_INFO) {
      peq(String(i), sensorPWMOffset[i]);
    }
  }

  loadSensorArray((logLevel >= LOG_INFO));
  findOrientation();
}



void loop() {
  lowestSensorValue = 1000;
  
  loadSensorArray(logLevel >= LOG_DATA);
  lowestSensorPosition = findFocalPoint();

  int steeringPwm;
  steeringPwm = map(lowestSensorPosition, 0, 6, 0, 255);
  //steeringPwm = findPWM(lastReadings);

  steeringPwm = findPWM(lowestSensorPosition);

  if (logLevel >= LOG_DATA) {
    Serial.print("    Pos: ");
    Serial.print(lowestSensorPosition);
    Serial.print("  PWM: ");
    Serial.println(steeringPwm);
  }

  if (logLevel == LOG_NONE) {
    analogWrite(PWM_SIGNAL_PIN, steeringPwm);
  }
  
  delay(25);
}



// CALCULATIONS

int findPWM(int focusSensor) {
  int pinLeft, pinRight;
  int leftDiff, rightDiff;
  int diff;
  float fractional;
  bool logging = false;
  int target = 0;
  int pwm;
    
//  logging = logLevel >= LOG_INFO;
  
  if (focusSensor == 0) {
    pinLeft = 0;
    pinRight = 1;
  }
  else if (focusSensor == NUMBER_OF_SENSORS) {
    pinLeft = NUMBER_OF_SENSORS - 1;
    pinRight = NUMBER_OF_SENSORS;
  }
  else {   
    leftDiff = abs(lastReadings[focusSensor] - lastReadings[focusSensor - 1]);
    rightDiff = abs(lastReadings[focusSensor + 1] - lastReadings[focusSensor]);
    if (leftDiff < rightDiff) {
      // the left side was closer together, focus on it
      diff = leftDiff;
      pinLeft = focusSensor - 1;
      pinRight = focusSensor;
    }
    else {
      diff = rightDiff;
      pinLeft = focusSensor;
      pinRight = focusSensor + 1;
    }
  }

  if (logging) { 
    Serial.print(pinLeft);
    Serial.print(" | ");
    Serial.println(pinRight);
  }
  
  // we have an area to look and a difference between two specific sensors
  diff = lastReadings[pinRight] - lastReadings[pinLeft];

  if (abs(diff) < MIDDLE_BAND) {
    // between two points
    if (logging) { Serial.print("-"); }
    fractional = 0.5;
  }
  else if (abs(leftDiff - rightDiff) < POINT_BAND) {
    // squarely on one point
    if (logging) { Serial.print("="); }
    if (diff > 0) {
      // just after the point
      fractional = 0;
    }
    else {
      // just before the point
      fractional = 1;
    }
  }
  else if (diff > 0) {
    // on the left slope
    if (logging) { Serial.print("\\"); }
    fractional = 0.25;
  }
  else {
    // on the right slope
    if (logging) { Serial.print("/"); }
    fractional = 0.75;
  }
 
  if (logging) { Serial.print("  "); }

  if (logging) {
    Serial.print("base: ");
    Serial.print(sensorPWMOffset[pinLeft]);
    Serial.print("  fract: ");
    Serial.print(fractional);
    Serial.print(" ~ ");
    Serial.print((sensorPWMOffset[1] * fractional));
    Serial.print("  ");
  }

  target = sensorPWMOffset[pinLeft] + (sensorPWMOffset[1] * fractional);
  if (logging) {
    Serial.print("[ ");
    Serial.print(target);
    Serial.print(" ]");
  }

  pwm = map(target, 0, 1024, 0, 255);
  return pwm;
}


int findFocalPoint() {
  int lowestSensorValue = 1024;
  int lowestSensor;

  for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
    if (lastReadings[i] < lowestSensorValue) {
      lowestSensorValue = lastReadings[i];
      lowestSensor = i;
    }
  }

  return lowestSensor;
}




// INITIAL SETUP

void findOrientation() {
  int sum = 0;
  int average;
  int numAbove = 0;
  int numBelow = 0;

  // find the average of the sensors.  Subsequent comparison between each value and the average
  // will reveal the orientation of the magnet, and if any orientation change is needed.
  if (logLevel >= LOG_INFO) {
    Serial.println("calculating average...");
  }
  
  for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
    peq(String(i), lastReadings[i]);
    sum = sum + lastReadings[i];
  }

  average = sum / NUMBER_OF_SENSORS;
  if (logLevel >= LOG_INFO) {
    peq("average", average);
    Serial.println("\nreadings:");
  }
  
  for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
    peq(String(i), lastReadings[i]);
    if (lastReadings[i] < average) {
      numBelow++;
    }
    else {
      numAbove++;
    }
  }

  peq("below", numBelow);
  peq("above", numAbove);

  if (numBelow > numAbove) {
    flipOrientation = true;
    if (logLevel >= LOG_INFO) {
      Serial.println("flipping orientation");
    }
  }  
}




// UTILITY FUNCTIONS

void loadSensorArray(bool log) {
  for (int i = 0; i < NUMBER_OF_SENSORS; i++) {
    sensorValue = analogRead(HALL_SENSOR_PINS[i]);

    //if the magnet appears to be in backwards, normalize it
    if (flipOrientation) {
      sensorValue = 1024 - sensorValue;
    }
    
    if (sensorValue < lowestSensorValue) {
      lastReadings[i] = sensorValue;
    }

    if (log) {
      Serial.print(sensorValue);
      Serial.print("  ");
    }
  }
}

void peq(String a, int i) {
  Serial.print(a);
  Serial.print(" = ");
  Serial.println(i);
}

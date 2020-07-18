#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

int triggerLedPin = 3;
int testModeLedPin = 2;
int testModeSwitchPin = 5;
int buttonSignalPin = 6;
int potentiometer = A2;

int MAX_DISTANCE = 300; // mm
int MIN_DISTANCE = 50; // mm

int READING_DELY_IN_MILLISECONDS = 50;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(triggerLedPin, OUTPUT);
  pinMode(potentiometer, INPUT);
  pinMode(testModeLedPin, OUTPUT);
  pinMode(testModeSwitchPin, INPUT_PULLUP);
  pinMode(buttonSignalPin, OUTPUT);

  digitalWrite(buttonSignalPin, LOW);

  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}

// the loop routine runs over and over again forever:
void loop() {
  VL53L0X_RangingMeasurementData_t measure;
    
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  int sensorRangeSetting = analogRead(potentiometer);
  int maxTriggerDistance = map(sensorRangeSetting, 0, 1023, MIN_DISTANCE, MAX_DISTANCE);
  Serial.print("Pot: ");
  Serial.print(sensorRangeSetting);
  Serial.print(" Trigger Distance: ");
  Serial.println(maxTriggerDistance);

  bool isTestMode = !digitalRead(testModeSwitchPin);
  if (isTestMode) {
    digitalWrite(testModeLedPin, HIGH);
  } else {
    digitalWrite(testModeLedPin, LOW);
  }

  int rangeInMm = 999;
  
  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
    rangeInMm = measure.RangeMilliMeter;
  } else {
    Serial.println(" out of range ");
    digitalWrite(triggerLedPin, LOW);
  }

  bool inRange = rangeInMm <= maxTriggerDistance;
  bool signalButtonPressed = !isTestMode && inRange;
  
  if (inRange) {
      digitalWrite(triggerLedPin, HIGH);
  } else {
      digitalWrite(triggerLedPin, LOW);
  }

  if (signalButtonPressed) {
    digitalWrite(buttonSignalPin, HIGH);
  } else {
    digitalWrite(buttonSignalPin, LOW);
  }
  
  delay(READING_DELY_IN_MILLISECONDS);
}

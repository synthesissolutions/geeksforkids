#include <Wire.h>
#include <Vishay_VCNL4200.h>
#include "RP2040_PWM.h"

// PWM Defines
#define STEERING_OUT_PIN  18
#define THROTTLE_OUT_PIN  20
#define PWM_FREQUENCY     1000  // 1 kHz

#define THROTTLE_OFF      50
#define THROTTLE_FORWARD  80
#define THROTTLE_REVERSE  20

#define STEERING_STRAIGHT 50
#define STEERING_LEFT     20
#define STEERING_RIGHT    80

// Multiplexer Defines
#define PCAADDR 0x70

#define PCA_LEFT    0
#define PCA_CENTER  1
#define PCA_RIGHT   2

// Other Defines
#define SENSOR_THRESHOLD    1250
#define ACTIVE_SIGNAL_PIN   9
#define REVERSE_SIGNAL_PIN  2
#define DISTANCE_POTENTIOMETER_PIN  A2
#define SOUND1_PIN    10
#define SOUND2_PIN    19

VCNL4200Class sensorLeft(Wire);
VCNL4200Class sensorCenter(Wire);
VCNL4200Class sensorRight(Wire);

RP2040_PWM* steeringPwmConfig;
RP2040_PWM* throttlePwmConfig;


int steeringPwm;
int throttlePwm;
bool throttleOn = false;

void pcaSelect(uint8_t i) {
  if (i > 3) return;
 
  Wire.beginTransmission(PCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

void pulseLed(int count, int durationMilliseconds) {
  for (int i = 0; i < count; i++) {
    digitalWrite(DISTANCE_POTENTIOMETER_PIN, true);
    delay(durationMilliseconds);
    digitalWrite(DISTANCE_POTENTIOMETER_PIN, false);
    delay(durationMilliseconds);
  }
}

void setup()
{
  Serial.begin(115200);

  pinMode(ACTIVE_SIGNAL_PIN, OUTPUT);
  pinMode(REVERSE_SIGNAL_PIN, INPUT_PULLUP);
  pinMode(SOUND1_PIN, OUTPUT);
  pinMode(SOUND2_PIN, OUTPUT);

  digitalWrite(SOUND1_PIN, true);
  digitalWrite(SOUND2_PIN, true);
  
  // Using this PIN to light the Reverse Switch LED
  pinMode(DISTANCE_POTENTIOMETER_PIN, OUTPUT);
  
  steeringPwmConfig = new RP2040_PWM(STEERING_OUT_PIN, PWM_FREQUENCY, STEERING_STRAIGHT);
  throttlePwmConfig = new RP2040_PWM(THROTTLE_OUT_PIN, PWM_FREQUENCY, THROTTLE_OFF);

  steeringPwmConfig->setPWM(STEERING_OUT_PIN, PWM_FREQUENCY, STEERING_STRAIGHT);
  throttlePwmConfig->setPWM(THROTTLE_OUT_PIN, PWM_FREQUENCY, THROTTLE_OFF);
  
  Wire.begin();

  pcaSelect(PCA_LEFT);
  if (!sensorLeft.begin())
  {
    Serial.println("Failed to initialize vcnl4200 for left button");
    pulseLed(500, 50);
    while(1);
  }

  pcaSelect(PCA_CENTER);
  if (!sensorCenter.begin())
  {
    Serial.println("Failed to initialize vcnl4200 for center button");
    pulseLed(500, 100);
    while(1);
  }

  pcaSelect(PCA_RIGHT);
  if (!sensorRight.begin())
  {
    Serial.println("Failed to initialize vcnl4200 for right button");
    pulseLed(500, 200);
    while(1);
  }

  digitalWrite(ACTIVE_SIGNAL_PIN, true);

  pulseLed(4, 100);
  
  Serial.println("PRX\tLux");
}

void loop() 
{
  uint16_t prxLeft = 0;
  uint16_t prxCenter = 0;
  uint16_t prxRight = 0;

  pcaSelect(PCA_LEFT);
  if (sensorLeft.read_PRX(&prxLeft))
  {
    Serial.print("Left\t");
    Serial.print(prxLeft);
    Serial.print('\t');
    Serial.println(sensorLeft.get_lux());
  }

  pcaSelect(PCA_CENTER);
  if (sensorLeft.read_PRX(&prxCenter))
  {
    Serial.print("Center\t");
    Serial.print(prxCenter);
    Serial.print('\t');
    Serial.println(sensorCenter.get_lux());
  }

  pcaSelect(PCA_RIGHT);
  if (sensorRight.read_PRX(&prxRight))
  {
    Serial.print("Right\t");
    Serial.print(prxRight);
    Serial.print('\t');
    Serial.println(sensorRight.get_lux());
  }

  if (prxCenter > SENSOR_THRESHOLD)
  {
    throttleOn = true;
    steeringPwm = STEERING_STRAIGHT;
  }
  else if (prxLeft > SENSOR_THRESHOLD)
  {
    throttleOn = true;
    steeringPwm = STEERING_LEFT;
  }
  else if (prxRight > SENSOR_THRESHOLD)
  {
    throttleOn = true;
    steeringPwm = STEERING_RIGHT;
  }
  else
  {
    throttleOn = false;
    steeringPwm = STEERING_STRAIGHT;
  }

  bool isReverse = digitalRead(REVERSE_SIGNAL_PIN);
  
  if (throttleOn)
  {
    if (isReverse) {
      throttlePwm = THROTTLE_FORWARD;
    } else {
      throttlePwm = THROTTLE_REVERSE;
    }
  }
  else
  {
    throttlePwm = THROTTLE_OFF;
  }

  if (isReverse) {
    digitalWrite(DISTANCE_POTENTIOMETER_PIN, false);
  } else {
    digitalWrite(DISTANCE_POTENTIOMETER_PIN, true);
  }

  steeringPwmConfig->setPWM(STEERING_OUT_PIN, PWM_FREQUENCY, steeringPwm);
  throttlePwmConfig->setPWM(THROTTLE_OUT_PIN, PWM_FREQUENCY, throttlePwm);
  
  delay(25);
}

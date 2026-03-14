#include <WiiChuck.h>

#include "RP2040_PWM.h"


#define THROTTLE_OFF      50
#define THROTTLE_FORWARD  80
#define THROTTLE_REVERSE  20

#define STEERING_STRAIGHT 50
#define STEERING_LEFT     20
#define STEERING_RIGHT    80

#define PWM_FREQUENCY     1000  // 1 kHz

#define STEERING_OUT_PIN  18
#define THROTTLE_OUT_PIN  20
#define ACTIVE_SIGNAL_PIN   9
#define SOUND1_PIN    10
#define SOUND2_PIN    19

RP2040_PWM* steeringPwmConfig;
RP2040_PWM* throttlePwmConfig;

int steeringPwm;
int throttlePwm;
bool throttleOn = false;

Accessory nunchuck1;

void setup() {
	Serial.begin(115200);

  pinMode(ACTIVE_SIGNAL_PIN, OUTPUT);
  pinMode(SOUND1_PIN, OUTPUT);
  pinMode(SOUND2_PIN, OUTPUT);

  digitalWrite(SOUND1_PIN, true);
  digitalWrite(SOUND2_PIN, true);
  
  steeringPwmConfig = new RP2040_PWM(STEERING_OUT_PIN, PWM_FREQUENCY, STEERING_STRAIGHT);
  throttlePwmConfig = new RP2040_PWM(THROTTLE_OUT_PIN, PWM_FREQUENCY, THROTTLE_OFF);

  steeringPwmConfig->setPWM(STEERING_OUT_PIN, PWM_FREQUENCY, STEERING_STRAIGHT);
  throttlePwmConfig->setPWM(THROTTLE_OUT_PIN, PWM_FREQUENCY, THROTTLE_OFF);
  
	nunchuck1.begin();
	if (nunchuck1.type == UnknownChuck) {
		/** If the device isn't auto-detected, set the type explicatly
		 * 	NUNCHUCK,
		 WIICLASSIC,
		 GuitarHeroController,
		 GuitarHeroWorldTourDrums,
		 DrumController,
		 DrawsomeTablet,
		 Turntable
		 */
		nunchuck1.type = NUNCHUCK;
	}

 digitalWrite(ACTIVE_SIGNAL_PIN, true);
}

void loop() {
	Serial.println("-------------------------------------------");
	nunchuck1.readData();    // Read inputs and update maps
	nunchuck1.printInputs(); // Print all inputs
  
  uint8_t x = nunchuck1.values[0];
  uint8_t y = nunchuck1.values[1];
  uint8_t sound1 = nunchuck1.values[10];
  uint8_t sound2 = nunchuck1.values[11];

  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.print(y);
  Serial.print(" Sound1: ");
  Serial.print(sound1);
  Serial.print(" Sound2: ");
  Serial.println(sound2);

  steeringPwm = map(x, 0, 255, STEERING_LEFT, STEERING_RIGHT);
  throttlePwm = map(y, 0, 255, THROTTLE_REVERSE, THROTTLE_FORWARD);
  
  steeringPwmConfig->setPWM(STEERING_OUT_PIN, PWM_FREQUENCY, steeringPwm);
  throttlePwmConfig->setPWM(THROTTLE_OUT_PIN, PWM_FREQUENCY, throttlePwm);

  if (sound1 == 255) {
    digitalWrite(SOUND1_PIN, false);
  } else {
    digitalWrite(SOUND1_PIN, true);
  }

  if (sound2 == 255) {
    digitalWrite(SOUND2_PIN, false);
  } else {
    digitalWrite(SOUND2_PIN, true);
  }

  delay(25);
}

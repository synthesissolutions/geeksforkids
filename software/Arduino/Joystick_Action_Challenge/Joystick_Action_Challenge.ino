
#include "joystick.h"

#define PIN_ACTION_OUT    PIN_PB5
#define PIN_JOYSTICK_X    PIN_PA6
#define PIN_JOYSTICK_Y    PIN_PB4
#define PIN_JOYSTICK_BTN  PIN_PA5

void setTrigger(void);

Joystick joystick(PIN_JOYSTICK_X, PIN_JOYSTICK_Y, PIN_JOYSTICK_BTN);

void setup() {
  // put your setup code here, to run once:
  joystick.begin();
  pinMode(PIN_ACTION_OUT, OUTPUT);
  digitalWrite(PIN_ACTION_OUT, LOW);
}

void loop() {
  joystick.read();

  if (joystick.x > 950 || joystick.x < 50) {
    setTrigger();
  } else if (joystick.y > 950 || joystick.y < 50) {
    setTrigger();
  }
  delay(50);
}

void setTrigger() {
  // set trigger output HIGH for 1 ms (blocking)
  // trigger output is inverted to send falling edge to action challenge
  digitalWrite(PIN_ACTION_OUT, HIGH);
  delay(1);
  digitalWrite(PIN_ACTION_OUT, LOW);
}

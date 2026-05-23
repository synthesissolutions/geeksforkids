
#define PIN_ACTION_OUT  4
#define PIN_JOYSTICK_X  A6
#define PIN_JOYSTICK_Y  A5

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_ACTION_OUT, OUTPUT);
  digitalWrite(PIN_ACTION_OUT, LOW);
  pinMode(PIN_JOYSTICK_X, INPUT);
  pinMode(PIN_JOYSTICK_Y, INPUT);
}

void loop() {
  int xPosition = analogRead(PIN_JOYSTICK_X);
  int yPosition = analogRead(PIN_JOYSTICK_Y);

  if (xPosition > 950 || xPosition < 50) {
    digitalWrite(PIN_ACTION_OUT, HIGH);
  } else if (yPosition > 950 || yPosition < 50) {
    //digitalWrite(PIN_ACTION_OUT, HIGH);
  } else {
    digitalWrite(PIN_ACTION_OUT, LOW);
  }
}

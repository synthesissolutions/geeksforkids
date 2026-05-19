
#define PIN_ACTION_OUT  4 

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_ACTION_OUT, OUTPUT);
  digitalWrite(PIN_ACTION_OUT, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  digitalWrite(PIN_ACTION_OUT, HIGH);
  delay(1000);
  digitalWrite(PIN_ACTION_OUT, LOW);
}

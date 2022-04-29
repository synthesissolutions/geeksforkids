#define PIN_PUL_PLUS  7
#define PIN_PUL_MINUS 6
#define PIN_DIR_PLUS  5
#define PIN_DIR_MINUS 4
#define PIN_ENA_PLUS  3
#define PIN_ENA_MINUS 2

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_PUL_PLUS, OUTPUT);
  pinMode(PIN_PUL_MINUS, OUTPUT);
  pinMode(PIN_DIR_PLUS, OUTPUT);
  pinMode(PIN_DIR_MINUS, OUTPUT);
  pinMode(PIN_ENA_PLUS, OUTPUT);
  pinMode(PIN_ENA_MINUS, OUTPUT);

  digitalWrite(PIN_PUL_MINUS, LOW);
  digitalWrite(PIN_DIR_MINUS, LOW);

  digitalWrite(PIN_PUL_PLUS, HIGH);
  digitalWrite(PIN_DIR_PLUS, HIGH);
  digitalWrite(PIN_ENA_PLUS, HIGH);
  digitalWrite(PIN_ENA_MINUS, HIGH);
}

void loop() {
  for(int x=0; x<1600; x++){
    digitalWrite(PIN_PUL_MINUS, HIGH);
    delayMicroseconds(100);
    digitalWrite(PIN_PUL_MINUS, LOW);
    delayMicroseconds(100);
  }

}

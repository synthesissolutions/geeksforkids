
int buttonSignalPin = 8;

void setup() {
    Serial.begin(115200);

    pinMode(buttonSignalPin, INPUT);
}

void loop() {
  if (digitalRead(buttonSignalPin)) {
    Serial.println("Pressed !!");
  } else {
    Serial.println("Not Pressed.");
  }

}

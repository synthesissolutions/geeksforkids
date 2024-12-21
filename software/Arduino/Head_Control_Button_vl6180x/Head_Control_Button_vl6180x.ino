#include <Wire.h>
#include "Adafruit_VL6180X.h"
#include <Adafruit_NeoPixel.h>

#define PIN         0
#define NUMPIXELS   1
#define BUTTON_PIN  9

Adafruit_VL6180X vl = Adafruit_VL6180X();
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, OUTPUT);
  
  pixels.begin();
  pixels.clear(); // Set all pixel colors to 'off'

  Serial.println("Adafruit VL6180x test!");
  if (! vl.begin()) {
    Serial.println("Failed to find sensor");
    while (1);
  }
  Serial.println("Sensor found!");
}

void loop() {
  float lux = vl.readLux(VL6180X_ALS_GAIN_5);

  uint8_t range = vl.readRange();
  uint8_t status = vl.readRangeStatus();

  if (status == VL6180X_ERROR_NONE) {
    Serial.print("Range: ");
    Serial.println(range);

    if (range >= 100) {
      digitalWrite(BUTTON_PIN, HIGH);
      pixels.setPixelColor(0, pixels.Color(150, 0, 0));
    } else {
      digitalWrite(BUTTON_PIN, LOW);
      pixels.setPixelColor(0, pixels.Color(0, 150, 0));
    }
  } else {
    digitalWrite(BUTTON_PIN, HIGH);
    pixels.setPixelColor(0, pixels.Color(150, 0, 0));
  }

  pixels.show();
  delay(50);
}

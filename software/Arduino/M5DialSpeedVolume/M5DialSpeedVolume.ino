#include "M5Dial.h"
#include <Wire.h>
#include <Preferences.h>

Preferences preferences;

long oldPosition = -999;
uint16_t speed = 50; 
uint16_t volume = 75;
bool showSpeed = true;

// Only allow the car version string to be set once by I2C
bool carVersionSet = false;
char carVersion[30];

const uint16_t currentVersion = 1;

#define M5DIAL_VERSION        "d24.10.1"
#define PREFERENCES_VERSION   "version"
#define PREFERENCES_NAMESPACE "settings"
#define PREFERENCES_SPEED     "speed"
#define PREFERENCES_VOLUME    "volume"

void requestEvent() {
  Wire.write((uint8_t) speed);
  Wire.write((uint8_t) volume);
}

void receiveEvent(int count) {
  if (carVersionSet) return;
  
  for (int i = 0; i < count; i++) {
    if (i < 30) {
      carVersion[i] = Wire.read();
    }
  }

  carVersionSet = true;
  displayChanged();
}

void setup() {
    auto cfg = M5.config();
    M5Dial.begin(cfg, true, false);
    M5Dial.Display.setTextFont(&fonts::Orbitron_Light_32);

    M5Dial.update();
    oldPosition = M5Dial.Encoder.read();

    preferences.begin(PREFERENCES_NAMESPACE, false);

    uint16_t version = preferences.getShort(PREFERENCES_VERSION, -1);
    if (version == currentVersion) {
      speed = preferences.getShort(PREFERENCES_SPEED, speed);
      volume = preferences.getShort(PREFERENCES_VOLUME, volume);

      speed = constrain(speed, 1, 100);
      volume = constrain(volume, 0, 100);
    } else {
      preferences.clear();
      preferences.putShort(PREFERENCES_VERSION, currentVersion);
      preferences.putShort(PREFERENCES_SPEED, speed);
      preferences.putShort(PREFERENCES_VOLUME, volume);
    }

    displayChanged();

    Wire.begin(0x55); // join i2c bus with address 0x55
    Wire.onRequest(requestEvent);
    Wire.onReceive(receiveEvent);
}

void drawSpeed() {
    M5Dial.Display.setTextColor(GREEN);
    M5Dial.Display.setTextDatum(middle_center);

    M5Dial.Display.setTextSize(1);
    M5Dial.Display.drawString("Speed", 
                              M5Dial.Display.width() /2, 
                              M5Dial.Display.height() / 6);

    M5Dial.Display.setTextSize(3);
    M5Dial.Display.drawString(String(speed),
                              M5Dial.Display.width() / 2,
                              M5Dial.Display.height() / 2);

}

void drawVolume() {
    M5Dial.Display.setTextColor(ORANGE);
    M5Dial.Display.setTextDatum(middle_center);
    
    M5Dial.Display.setTextSize(1);
    M5Dial.Display.drawString("Volume", 
                              M5Dial.Display.width() /2, 
                              M5Dial.Display.height() / 6);

    M5Dial.Display.setTextSize(3);
    M5Dial.Display.drawString(String(volume),
                              M5Dial.Display.width() / 2,
                              M5Dial.Display.height() / 2);
}

void drawM5DialVersion() {
    M5Dial.Display.setTextColor(DARKCYAN);
    M5Dial.Display.setTextDatum(middle_center);
    M5Dial.Display.setTextSize(1);
    M5Dial.Display.drawString(M5DIAL_VERSION, 
                              M5Dial.Display.width() /2, 
                              M5Dial.Display.height()  - (M5Dial.Display.height() / 5));  
}

void drawCarVersion() {
    if (!carVersionSet) {
      return;
    }
    M5Dial.Display.setTextColor(VIOLET);
    M5Dial.Display.setTextDatum(middle_center);
    M5Dial.Display.setTextSize(1);
    M5Dial.Display.drawString(carVersion,
                              M5Dial.Display.width() /2,
                              M5Dial.Display.height()  - (M5Dial.Display.height() / 5));
}

void displayChanged() {
    M5Dial.Speaker.tone(8000, 20);
    M5Dial.Display.clear();
    if (showSpeed) {
      drawSpeed();      
      drawCarVersion();
    } else {
      drawVolume();      
      drawM5DialVersion();
    }
}

void loop() {
    M5Dial.update();
    long newPosition = M5Dial.Encoder.read();
    if (newPosition != oldPosition) {
      long delta = newPosition - oldPosition;
      oldPosition = newPosition;
      if (showSpeed) {
        speed += delta;
        speed = constrain(speed, 1, 100);
        preferences.putShort(PREFERENCES_SPEED, speed);
      } else {
        volume += delta;
        volume = constrain(volume, 1, 100);
        preferences.putShort(PREFERENCES_VOLUME, volume);
      }

      displayChanged();
    }

    if (M5Dial.BtnA.wasPressed()) {
      showSpeed = !showSpeed;
      displayChanged();
    }
    if (M5Dial.BtnA.pressedFor(5000)) {
        //M5Dial.Encoder.write(100);
    }
}

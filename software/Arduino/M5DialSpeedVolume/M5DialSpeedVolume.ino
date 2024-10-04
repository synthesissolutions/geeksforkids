/**
 * @file encoder.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief M5Dial Encoder Test
 * @version 0.2
 * @date 2023-10-18
 *
 *
 * @Hardwares: M5Dial
 * @Platform Version: Arduino M5Stack Board Manager v2.0.7
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 */

#include "M5Dial.h"
#include <Wire.h>

long oldPosition = -999;
long speed = 50; 
long volume = 75;
bool showSpeed = true;

// Only allow the car version string to be set once by I2C
bool carVersionSet = false;
char carVersion[30];

#define M5DIAL_VERSION "d24.09.0"
#define CAR_VERSION "c24.09.1"

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
}

void setup() {
    auto cfg = M5.config();
    M5Dial.begin(cfg, true, false);
    M5Dial.Display.setTextFont(&fonts::Orbitron_Light_32);

    M5Dial.update();
    oldPosition = M5Dial.Encoder.read();

    //carVersion += CAR_VERSION;
    
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
      } else {
        volume += delta;
        volume = constrain(volume, 1, 100);
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

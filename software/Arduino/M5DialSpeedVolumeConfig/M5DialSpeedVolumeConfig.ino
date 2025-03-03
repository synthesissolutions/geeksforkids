#include "M5Dial.h"
#include <Wire.h>
#include <Preferences.h>

#define REGISTER_VERSION              0
#define REGISTER_ACTUATOR_MIN         1
#define REGISTER_ACTUATOR_CENTER      2
#define REGISTER_ACTUATOR_MAX         3
#define REGISTER_USE_RC               4
#define REGISTER_RC_STEERING_MIN      5
#define REGISTER_RC_STEERING_CENTER   6
#define REGISTER_RC_STEERING_MAX      7
#define REGISTER_RC_THROTTLE_MIN      8
#define REGISTER_RC_THROTTLE_CENTER   9
#define REGISTER_RC_THROTTLE_MAX      10
#define REGISTER_USE_PWM_JOYSTICK_X   11
#define REGISTER_USE_PWM_JOYSTICK_Y   12
#define REGISTER_INVERT_JOYSTICK_X    13
#define REGISTER_INVERT_JOYSTICK_Y    14
#define REGISTER_JOYSTICK_STEERING_MIN    15
#define REGISTER_JOYSTICK_STEERING_CENTER 16
#define REGISTER_JOYSTICK_STEERING_MAX    17
#define REGISTER_JOYSTICK_THROTTLE_MIN    18
#define REGISTER_JOYSTICK_THROTTLE_CENTER 19
#define REGISTER_JOYSTICK_THROTTLE_MAX    20
#define REGISTER_EXTEND_THROTTLE          21
#define REGISTER_EXTEND_THROTTLE_TIME_MS  22
#define REGISTER_CHILD_THROTTLE_ONLY      23
#define REGISTER_CAR_CODE_VERSION         98
#define REGISTER_SPEED_VOLUME             99

const int CURRENT_SETTINGS_VERSION = 5;

#define INTEGER_CONFIGURATION 1
#define BOOLEAN_CONFIGURATION 2

struct MenuOptions {
  String name;
  uint8_t options[10];
};

MenuOptions menuOptions[] = {
  {"Linear Actuator", {REGISTER_ACTUATOR_MIN, REGISTER_ACTUATOR_CENTER, REGISTER_ACTUATOR_MAX}},
  {"Remote Control", {REGISTER_USE_RC, REGISTER_RC_STEERING_MIN, REGISTER_RC_STEERING_CENTER, REGISTER_RC_STEERING_MAX, REGISTER_RC_THROTTLE_MIN, REGISTER_RC_THROTTLE_CENTER, REGISTER_RC_THROTTLE_MAX}},
  {"Analog/PWM", {REGISTER_USE_PWM_JOYSTICK_X, REGISTER_USE_PWM_JOYSTICK_Y}},
  {"Direction", {REGISTER_INVERT_JOYSTICK_X, REGISTER_INVERT_JOYSTICK_Y}},
  {"Steering", {REGISTER_JOYSTICK_STEERING_MIN, REGISTER_JOYSTICK_STEERING_CENTER, REGISTER_JOYSTICK_STEERING_MAX}},
  {"Throttle", {REGISTER_JOYSTICK_THROTTLE_MIN, REGISTER_JOYSTICK_THROTTLE_CENTER, REGISTER_JOYSTICK_THROTTLE_MAX, REGISTER_EXTEND_THROTTLE, REGISTER_EXTEND_THROTTLE_TIME_MS, REGISTER_CHILD_THROTTLE_ONLY}}
};

int menuItemCount = sizeof(menuOptions);

struct ConfigurationEntry {
  String name;
  int dataType;
  int intMin;
  int intMax;
  boolean booleanValue;
  int16_t intValue;
};

ConfigurationEntry configurationEntries[] = {
  {"Version", 1, 100, INTEGER_CONFIGURATION, false, CURRENT_SETTINGS_VERSION},
  {"Min", -100, 100, INTEGER_CONFIGURATION, false, -50},  // in scaled units from -100 to 100
  {"Center", -100, 100, INTEGER_CONFIGURATION, false, 0},  // in scaled units from -100 to 100
  {"Max", -100, 100, INTEGER_CONFIGURATION, false, 50},   // in scaled units from -100 to 100
  {"Use RC", 0, 0, BOOLEAN_CONFIGURATION, true, 0},
  {"Steering Min", 800, 2200, INTEGER_CONFIGURATION, false, 1000},  // All RC values are in PWM duty cycle microseconds
  {"Steering Center", 800, 2200, INTEGER_CONFIGURATION, false, 1500},
  {"Steering Max", 800, 2200, INTEGER_CONFIGURATION, false, 2000},
  {"Throttle Min", 800, 2200, INTEGER_CONFIGURATION, false, 1000},
  {"Throttle Center", 800, 2200, INTEGER_CONFIGURATION, false, 1500},
  {"Throttle Max", 800, 2200, INTEGER_CONFIGURATION, false, 2000},
  {"Steering PWM", 0, 0, BOOLEAN_CONFIGURATION, true, 0},
  {"Throttle PWM", 0, 0, BOOLEAN_CONFIGURATION, true, 0},
  {"Invert Steering", 0, 0, BOOLEAN_CONFIGURATION, true, 0},
  {"Invert Throttle", 0, 0, BOOLEAN_CONFIGURATION, true, 0},
  {"Steering Min", 0, 1023, INTEGER_CONFIGURATION, false, 200}, // Joystick values are in PWM duty cycle microseconds or analog readings 0 - 1023
  {"Steering Center", 0, 1023, INTEGER_CONFIGURATION, false, 500},
  {"Steering Max", 0, 1023, INTEGER_CONFIGURATION, false, 800},
  {"Throttle Min", 0, 1023, INTEGER_CONFIGURATION, false, 200},
  {"Throttle Center", 0, 1023, INTEGER_CONFIGURATION, false, 500},
  {"Throttle Max", 0, 1023, INTEGER_CONFIGURATION, false, 800},
  {"Extend Throttle", 0, 0, BOOLEAN_CONFIGURATION, false, 0},
  {"Extend Throttle Milliseconds", 0, 5000, INTEGER_CONFIGURATION, false, 500},
  {"Child Throttle Only", 0, 0, BOOLEAN_CONFIGURATION, false, 0}
};

Preferences preferences;

long oldPosition = -999;
uint8_t speed = 50; 
uint8_t volume = 75;
bool showSpeed = true;
uint8_t currentRegister = REGISTER_SPEED_VOLUME;
bool isInConfigurationMode = false;

// Configuration UI variables
uint8_t currentMenuOption;

// Only allow the car version string to be set once by I2C
bool carVersionSet = false;
char carVersion[30];

const uint16_t currentVersion = 1;

#define M5DIAL_VERSION        "d25.03.1"
#define PREFERENCES_VERSION   "version"
#define PREFERENCES_NAMESPACE "settings"
#define PREFERENCES_SPEED     "speed"
#define PREFERENCES_VOLUME    "volume"

// Based on the current register, return three or four bytes
// Byte one is a boolean true = config mode, false = speed/volume mode
// Byte two is the register being returned
// speed and volume are single byte values but both are returned together
// all boolean registers are single byte values
// all other integer values are two bytes
void requestEvent() {
  if (currentRegister == REGISTER_SPEED_VOLUME) {
    Wire.write((uint8_t) 0); // speed/volume mode
    Wire.write(currentRegister);
    
    Wire.write((uint8_t) speed);
    Wire.write((uint8_t) volume);
  } else if (currentRegister <= REGISTER_CHILD_THROTTLE_ONLY) {
    Wire.write((uint8_t) 1); // config mode
    Wire.write(currentRegister);

    if (configurationEntries[currentRegister].dataType == BOOLEAN_CONFIGURATION) {
      Wire.write(configurationEntries[currentRegister].booleanValue);
    } else if (configurationEntries[currentRegister].dataType == INTEGER_CONFIGURATION) {
      uint8_t* p = (uint8_t*) &configurationEntries[currentRegister].intValue;
      Wire.write(p[0]);
      Wire.write(p[1]);
    }
  }
}

// Byte 1 read/write flag
// Byte 2 register (which value to read/write to)
// Bytes 3&4 data if byte 1 is write flag contain either a one byte boolean or two byte signed integer
// Unless the register is for the car version, in which case it's the version text
void receiveEvent(int count) {
  // If we have fewer than 3 bytes then something is wrong
  if (count < 3) return;

  uint8_t isWriteFlag = Wire.read();
  uint8_t newRegister = Wire.read();
  uint8_t previousRegister = currentRegister;
  
  currentRegister = newRegister;
  
  if (!isWriteFlag) {
    // If we are reading data, we just need to save the register and wait for the request event
    return;
  }
  
  if (currentRegister == REGISTER_CAR_CODE_VERSION) {
    for (int i = 0; i < count-2; i++) {
      if (i < 30) {
        carVersion[i] = Wire.read();
      }    
    }

    carVersionSet = true;

    // The Car Code version is a readonly register
    // so switch back to the default speed/volume register
    currentRegister = REGISTER_SPEED_VOLUME;
  } else if (currentRegister == REGISTER_SPEED_VOLUME) {
    if (isInConfigurationMode) {
      // Do not allow switching from configuration mode back to Speed/Volume
      currentRegister = previousRegister;
    } else if (isWriteFlag && count == 4) {
      speed = Wire.read();
      volume = Wire.read();
    }
  } else if (currentRegister == REGISTER_VERSION) {
    // We do not allow the Version value to be overwritten by the car
    // This is simply to set the proper register for the car to retrieve the
    // version of the configuration that the M5Dial is using

    // For now we will let the car decide what to do with a version mismatch
  } else if (currentRegister <= REGISTER_CHILD_THROTTLE_ONLY) {
    // In theory, the car should never set the register in read only mode
    // that should be controlled by the M5Dial
    
    if (isWriteFlag) {
      if (configurationEntries[currentRegister].dataType == BOOLEAN_CONFIGURATION) {
        configurationEntries[currentRegister].booleanValue = Wire.read();
      } else if (configurationEntries[currentRegister].dataType == INTEGER_CONFIGURATION) {
        uint8_t* p = (uint8_t*) &configurationEntries[currentRegister].intValue;
        p[0] = Wire.read();
        p[1] = Wire.read();
      }
    }

    if (isInConfigurationMode && currentRegister != previousRegister) {
      // While in configuration mode, the M5Dial is in control of which configuration setting is being operated on
      currentRegister = previousRegister;
    }
  }

  displayChanged();
}

void setup() {
    Serial.begin(115200);
    
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
    //Wire.onRequest(requestEvent);
    //Wire.onReceive(receiveEvent);
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
    if (M5Dial.BtnA.pressedFor(3000)) {
        configurationLoop();
    }
}

void drawMainMenu(int currentMenuOption) {
  M5Dial.Display.clear();
  
  M5Dial.Display.setTextColor(BLUE);
  M5Dial.Display.setTextDatum(middle_center);
  M5Dial.Display.setTextSize(0.75);
  M5Dial.Display.drawString("Main Menu1", M5Dial.Display.width() /2, M5Dial.Display.height() / 2);  
  M5Dial.Display.drawString("Main Menu2", M5Dial.Display.width() /2, M5Dial.Display.height() / 2 + 24);  
}

void configurationLoop() {
  // Display the main menu
  // We will never exit this loop and return to speed/volume control
  
  currentMenuOption = 0;
  M5Dial.Encoder.write(currentMenuOption);

  drawMainMenu(currentMenuOption);
  
  while (true) {
    M5Dial.update();
    long newPosition = M5Dial.Encoder.read();
  }
}

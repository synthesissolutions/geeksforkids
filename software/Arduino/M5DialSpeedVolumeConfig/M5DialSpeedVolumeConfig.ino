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

#define BACK_MENU_ITEM                    -1

const int CURRENT_SETTINGS_VERSION = 5;

#define INTEGER_CONFIGURATION 1
#define BOOLEAN_CONFIGURATION 2

struct MenuOption {
  String name;
  uint8_t optionCount;
  uint8_t options[10];
};

MenuOption menuOptions[] = {
  {"Lin Actuator", 4, {BACK_MENU_ITEM, REGISTER_ACTUATOR_MIN, REGISTER_ACTUATOR_CENTER, REGISTER_ACTUATOR_MAX}},
  {"Remote Ctrl", 8, {BACK_MENU_ITEM, REGISTER_USE_RC, REGISTER_RC_STEERING_MIN, REGISTER_RC_STEERING_CENTER, REGISTER_RC_STEERING_MAX, REGISTER_RC_THROTTLE_MIN, REGISTER_RC_THROTTLE_CENTER, REGISTER_RC_THROTTLE_MAX}},
  {"Analog/PWM", 3, {BACK_MENU_ITEM, REGISTER_USE_PWM_JOYSTICK_X, REGISTER_USE_PWM_JOYSTICK_Y}},
  {"Direction", 3, {BACK_MENU_ITEM, REGISTER_INVERT_JOYSTICK_X, REGISTER_INVERT_JOYSTICK_Y}},
  {"Steering", 4, {BACK_MENU_ITEM, REGISTER_JOYSTICK_STEERING_MIN, REGISTER_JOYSTICK_STEERING_CENTER, REGISTER_JOYSTICK_STEERING_MAX}},
  {"Throttle", 7, {BACK_MENU_ITEM, REGISTER_JOYSTICK_THROTTLE_MIN, REGISTER_JOYSTICK_THROTTLE_CENTER, REGISTER_JOYSTICK_THROTTLE_MAX, REGISTER_EXTEND_THROTTLE, REGISTER_EXTEND_THROTTLE_TIME_MS, REGISTER_CHILD_THROTTLE_ONLY}}
};

int menuItemCount = sizeof(menuOptions) / sizeof(menuOptions[0]);

struct ConfigurationEntry {
  String name;
  boolean setByCar;
  int intMin;
  int intMax;
  int dataType;
  boolean booleanValue;
  int16_t intValue;
};

ConfigurationEntry configurationEntries[] = {
  {"Version", false, 1, 100, INTEGER_CONFIGURATION, false, CURRENT_SETTINGS_VERSION},
  {"Min", false, -100, 100, INTEGER_CONFIGURATION, false, -50},  // in scaled units from -100 to 100
  {"Center", false, -100, 100, INTEGER_CONFIGURATION, false, 0},  // in scaled units from -100 to 100
  {"Max", false, -100, 100, INTEGER_CONFIGURATION, false, 50},   // in scaled units from -100 to 100
  {"Use RC", false, 0, 0, BOOLEAN_CONFIGURATION, true, 0},
  {"Steering Min", false, 800, 2200, INTEGER_CONFIGURATION, false, 1000},  // All RC values are in PWM duty cycle microseconds
  {"Steering Center", false, 800, 2200, INTEGER_CONFIGURATION, false, 1500},
  {"Steering Max", false, 800, 2200, INTEGER_CONFIGURATION, false, 2000},
  {"Throttle Min", false, 800, 2200, INTEGER_CONFIGURATION, false, 1000},
  {"Throttle Center", false, 800, 2200, INTEGER_CONFIGURATION, false, 1500},
  {"Throttle Max", false, 800, 2200, INTEGER_CONFIGURATION, false, 2000},
  {"Steering PWM", false, 0, 0, BOOLEAN_CONFIGURATION, true, 0},
  {"Throttle PWM", false, 0, 0, BOOLEAN_CONFIGURATION, true, 0},
  {"Invert Steering", false, 0, 0, BOOLEAN_CONFIGURATION, true, 0},
  {"Invert Throttle", false, 0, 0, BOOLEAN_CONFIGURATION, true, 0},
  {"Steering Min", false, 0, 1023, INTEGER_CONFIGURATION, false, 200}, // Joystick values are in PWM duty cycle microseconds or analog readings 0 - 1023
  {"Steering Center", false, 0, 1023, INTEGER_CONFIGURATION, false, 500},
  {"Steering Max", false, 0, 1023, INTEGER_CONFIGURATION, false, 800},
  {"Throttle Min", false, 0, 1023, INTEGER_CONFIGURATION, false, 200},
  {"Throttle Center", false, 0, 1023, INTEGER_CONFIGURATION, false, 500},
  {"Throttle Max", false, 0, 1023, INTEGER_CONFIGURATION, false, 800},
  {"Extend Throttle", false, 0, 0, BOOLEAN_CONFIGURATION, false, 0},
  {"Ext Throttle Ms", false, 0, 5000, INTEGER_CONFIGURATION, false, 500},
  {"Child Throt Only", false, 0, 0, BOOLEAN_CONFIGURATION, false, 0}
};

Preferences preferences;

long oldPosition = -999;
uint8_t speed = 50; 
uint8_t volume = 75;
bool showSpeed = true;
uint8_t currentRegister = REGISTER_SPEED_VOLUME;
bool isInConfigurationMode = false;

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
      configurationEntries[currentRegister].setByCar = true;
      
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
      isInConfigurationMode = true;
      configurationLoop();
    }
}

void drawMainMenu(int currentMenuOption) {
  M5Dial.Display.clear();

  int centerX = M5Dial.Display.width() / 2;
  int centerY = M5Dial.Display.height() / 2;
  int lineOffset = 24;

  // Place Selected Menu Item
  M5Dial.Display.setTextColor(BLUE);
  M5Dial.Display.setTextDatum(middle_center);
  M5Dial.Display.setTextSize(0.75);

  M5Dial.Display.drawString(menuOptions[currentMenuOption].name, centerX, centerY);

  M5Dial.Display.setTextSize(0.6);
  M5Dial.Display.setTextColor(WHITE);

  // Place items above selected item
  if (currentMenuOption != 0) {
    for (int i = currentMenuOption - 1; i >= 0; i--) {
      M5Dial.Display.drawString(menuOptions[i].name, centerX, centerY - (currentMenuOption - i) * lineOffset);
    }    
  }

  // Place items below selected item
  if (currentMenuOption < (menuItemCount - 1)) {
    for (int i = currentMenuOption + 1; i < menuItemCount; i++) {
      M5Dial.Display.drawString(menuOptions[i].name, centerX, centerY + (i - currentMenuOption) * lineOffset);
    }
  }
}

void configurationLoop() {
  // Display the main menu
  // We will never exit this loop and return to speed/volume control
  
  int currentMenuOption = 0;
  M5Dial.Encoder.write(currentMenuOption);

  drawMainMenu(currentMenuOption);
  
  while (true) {
    M5Dial.update();
    long newPosition = M5Dial.Encoder.read();

    if (newPosition < 0) {
      newPosition = 0;
    } else if (newPosition >= menuItemCount) {
      newPosition = menuItemCount - 1;
    }

    if (newPosition != currentMenuOption) {
      currentMenuOption = newPosition;
      drawMainMenu(currentMenuOption);
    }

    if (M5Dial.BtnA.wasPressed()) {
      secondaryMenuLoop(menuOptions[currentMenuOption]);
      M5Dial.Encoder.write(currentMenuOption);
      drawMainMenu(currentMenuOption);
    }
  }
}

void getInteger(ConfigurationEntry *entry) {
  drawInteger(entry);

  int currentPosition = entry->intValue;
  M5Dial.Encoder.write(currentPosition);
  
  while (true) {
    M5Dial.update();
    int newPosition = M5Dial.Encoder.read();
    
    if (newPosition != currentPosition) {
      // If the value has not be set by the car caddy,
      // show *waiting* and wait until it is set.
      if (entry->setByCar) {
        if (newPosition < entry->intMin) {
          currentPosition = entry->intMin;
          M5Dial.Encoder.write(currentPosition);
        } else if (newPosition > entry->intMax) {
          currentPosition = entry->intMax;
          M5Dial.Encoder.write(currentPosition);
        } else {
          currentPosition = newPosition;
        }      

        entry->intValue = currentPosition;
        drawInteger(entry);
      }
    }
    
    if (M5Dial.BtnA.wasPressed()) {
      return;
    }
  }  
}

void drawBoolean(ConfigurationEntry *entry) {
  int centerX = M5Dial.Display.width() / 2;
  int centerY = (M5Dial.Display.height() / 2) + 20;
  
  M5Dial.Display.clear();

  M5Dial.Display.fillRect(0, 24, M5Dial.Display.width(), 46, BLUE);
  M5Dial.Display.setTextColor(WHITE);
  M5Dial.Display.setTextDatum(middle_center);
  M5Dial.Display.setTextSize(0.75);
  M5Dial.Display.drawString(entry->name, centerX, 48);

  M5Dial.Display.setTextColor(WHITE);
  if (!entry->setByCar) {
    M5Dial.Display.setTextSize(1.25);
    M5Dial.Display.drawString("*waiting*", centerX, centerY);
  } else {
    M5Dial.Display.setTextSize(2);
    if (entry->booleanValue) {
      M5Dial.Display.drawString("True", centerX, centerY);
    } else {
      M5Dial.Display.drawString("False", centerX, centerY);
    }
  }
}

void drawInteger(ConfigurationEntry *entry) {
  int centerX = M5Dial.Display.width() / 2;
  int centerY = (M5Dial.Display.height() / 2) + 20;
  
  M5Dial.Display.clear();

  M5Dial.Display.fillRect(0, 24, M5Dial.Display.width(), 46, BLUE);
  M5Dial.Display.setTextColor(WHITE);
  M5Dial.Display.setTextDatum(middle_center);
  M5Dial.Display.setTextSize(0.75);
  M5Dial.Display.drawString(entry->name, centerX, 48);

  M5Dial.Display.setTextColor(WHITE);
  if (!entry->setByCar) {
    M5Dial.Display.setTextSize(1.25);
    M5Dial.Display.drawString("*waiting*", centerX, centerY);
  } else {
    M5Dial.Display.setTextSize(2);
    M5Dial.Display.drawString(String(entry->intValue), centerX, centerY);
  }
}

void getBoolean(ConfigurationEntry *entry) {
  int centerX = M5Dial.Display.width() / 2;
  int centerY = M5Dial.Display.height() / 2;

  drawBoolean(entry);

  int currentPosition = M5Dial.Encoder.read();
  
  while (true) {
    M5Dial.update();
    int newPosition = M5Dial.Encoder.read();

    // If the value has not be set by the car caddy,
    // show *waiting* and wait until it is set.
    if (entry->setByCar) {
      bool oldValue = entry->booleanValue;
      
      if (newPosition < currentPosition) {
        entry->booleanValue = true;
      } else if (newPosition > currentPosition) {
        entry->booleanValue = false;
      }
      
      currentPosition = newPosition;
      if (oldValue != entry->booleanValue) {
        drawBoolean(entry);
      }
    }

    if (M5Dial.BtnA.wasPressed()) {
      return;
    }
  }
}

void secondaryMenuLoop(MenuOption menuOption) {
  int currentMenuItem = 0;
  M5Dial.Encoder.write(currentMenuItem);

  drawSecondaryMenu(menuOption, currentMenuItem);
  
  while (true) {
    M5Dial.update();
    long newPosition = M5Dial.Encoder.read();

    if (newPosition < 0) {
      newPosition = 0;
    } else if (newPosition >= menuOption.optionCount) {
      newPosition = menuOption.optionCount - 1;
    }

    if (newPosition != currentMenuItem) {
      currentMenuItem = newPosition;
      drawSecondaryMenu(menuOption, currentMenuItem);
    }

    if (M5Dial.BtnA.wasPressed()) {
      if (currentMenuItem == 0) {
        return;
      }
      
      ConfigurationEntry *entry = &configurationEntries[menuOption.options[currentMenuItem]];
      currentRegister = menuOption.options[currentMenuItem];
      if (entry->dataType == BOOLEAN_CONFIGURATION) {
        getBoolean(entry);
      } else {
        getInteger(entry);
      }

      M5Dial.Encoder.write(currentMenuItem);
      drawSecondaryMenu(menuOption, currentMenuItem);
    }
  }
}

void drawSecondaryMenu(MenuOption menuOption, int selectedMenuOption) {
  M5Dial.Display.clear();

  int centerX = M5Dial.Display.width() / 2;
  int centerY = M5Dial.Display.height() / 2;
  int lineOffset = 24;

  // Place Selected Menu Item
  M5Dial.Display.setTextColor(ORANGE);
  M5Dial.Display.setTextDatum(middle_center);
  M5Dial.Display.setTextSize(0.75);

  ConfigurationEntry entry;

  //if (menuOption.options[selectedMenuOption] == BACK_MENU_ITEM) {
  if (selectedMenuOption == 0) {
    M5Dial.Display.drawString("<< Back", centerX, centerY);
  } else {
    entry = configurationEntries[menuOption.options[selectedMenuOption]];
    M5Dial.Display.drawString(entry.name, centerX, centerY);
  }

  M5Dial.Display.setTextSize(0.6);
  M5Dial.Display.setTextColor(WHITE);

  // Place items above selected item
  if (selectedMenuOption != 0) {
    for (int i = selectedMenuOption - 1; i >= 0; i--) {
      int yPosition = centerY - (selectedMenuOption - i) * lineOffset;
      if (yPosition < 60) {
        break;
      }

      if (i == 0) {
        M5Dial.Display.drawString("<< Back", centerX, yPosition);
      } else {
        entry = configurationEntries[menuOption.options[i]];
        M5Dial.Display.drawString(entry.name, centerX, yPosition);        
      }
    }    
  }

  // Place items below selected item
  if (selectedMenuOption < (menuOption.optionCount - 1)) {
    for (int i = selectedMenuOption + 1; i < menuOption.optionCount; i++) {
      if (menuOption.options[selectedMenuOption] == BACK_MENU_ITEM) {
        M5Dial.Display.drawString("<< Back", centerX, centerY + (i - selectedMenuOption) * lineOffset);
      } else {
        entry = configurationEntries[menuOption.options[i]];
        M5Dial.Display.drawString(entry.name, centerX, centerY + (i - selectedMenuOption) * lineOffset);
      }
    }
  }

   // Draw Menu Option Title
  M5Dial.Display.fillRect(0, 24, M5Dial.Display.width(), 46, BLUE);
  M5Dial.Display.setTextColor(WHITE);
  M5Dial.Display.setTextDatum(middle_center);
  M5Dial.Display.setTextSize(0.75);
  M5Dial.Display.drawString(menuOption.name, centerX, 48);
}

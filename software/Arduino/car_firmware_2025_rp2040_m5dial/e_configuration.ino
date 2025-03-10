/**
 * Configuration Class
 * 
 * This class serves to interpret the eeprom settings to define the configuration for this car
 */
#include <Wire.h>

#define REGISTER_CAR_CODE_VERSION         98
#define REGISTER_SPEED_VOLUME             99

class Configuration {
  private:
    Eeprom *eeprom;
    int maxSpeedPin;
    uint8_t speed = 5;
    uint8_t volume = 10;
    bool versionSent = false;
    bool m5DialDetected = false;
    int16_t m5DialVersion = -1;
    bool m5DialConfigurationModeActive = false;
    
  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    Configuration() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init(Eeprom *e) {
      eeprom = e;

      Wire.setSDA(PIN_M5DIAL_I2C_SDA);
      Wire.setSCL(PIN_M5DIAL_I2C_SCL);
      Wire.begin();
      
      Wire1.setSDA(PIN_ATTINY_I2C_SDA);
      Wire1.setSCL(PIN_ATTINY_I2C_SCL);
      Wire1.begin();
    }

    void detectM5Dial() {
      Wire.beginTransmission(M5DIAL_I2C_ADDRESS);

      Wire.write(0); // Set to read mode
      Wire.write(EEPROM_VERSION); // The Register
      
      Wire.endTransmission();

      delay(5);
      
      if(Wire.requestFrom(M5DIAL_I2C_ADDRESS, 4))
      {
        uint8_t* p = (uint8_t*) &m5DialVersion;

        bool configMode = Wire.read();
        uint8_t reg = Wire.read();

        if (reg == EEPROM_VERSION) {
          p[0] = Wire.read();
          p[1] = Wire.read();
          m5DialDetected = true;        
        }
      }
    }
    
    // Called periodically to update any values read in real-time
    void update() {
      if (m5DialDetected) {
        readSpeedVolume();
        writeVolume(); // Send the selected volume to the ATTiny handling audio output
  
        if (!versionSent) {
          versionSent = true;
          writeVersion();
        }        
      } else {
        detectM5Dial();
      }
    }

    bool getIsM5DialConfigurationMode() {
      // TODO Double check the configuration mode to make sure it's not spurious data
      return m5DialConfigurationModeActive;
    }
    
    /*
     * getters ... translate dip switch settings into car configuration
     */
    int getConfigurationVersion() { return eeprom->getIntegerSetting(EEPROM_VERSION); }

    // Joystick
    boolean getInvertJoystickX() { return eeprom->getBooleanSetting(EEPROM_INVERT_JOYSTICK_X); }
    boolean getInvertJoystickY() { return eeprom->getBooleanSetting(EEPROM_INVERT_JOYSTICK_Y); }
    boolean usePwmJoystickX() { return eeprom->getBooleanSetting(EEPROM_USE_PWM_JOYSTICK_X); }
    boolean usePwmJoystickY() { return eeprom->getBooleanSetting(EEPROM_USE_PWM_JOYSTICK_Y); }
    int getJoystickSteeringMin() { return eeprom->getIntegerSetting(EEPROM_JOYSTICK_STEERING_MIN); }
    int getJoystickSteeringCenter() { return eeprom->getIntegerSetting(EEPROM_JOYSTICK_STEERING_CENTER); }
    int getJoystickSteeringMax() { return eeprom->getIntegerSetting(EEPROM_JOYSTICK_STEERING_MAX); }
    int getJoystickThrottleMin() { return eeprom->getIntegerSetting(EEPROM_JOYSTICK_THROTTLE_MIN); }
    int getJoystickThrottleCenter() { return eeprom->getIntegerSetting(EEPROM_JOYSTICK_THROTTLE_CENTER); }
    int getJoystickThrottleMax() { return eeprom->getIntegerSetting(EEPROM_JOYSTICK_THROTTLE_MAX); }

    // Parental Control
    boolean useRc() { return eeprom->getBooleanSetting(EEPROM_USE_RC); }
    int getRcSteeringMin() { return eeprom->getIntegerSetting(EEPROM_RC_STEERING_MIN); }
    int getRcSteeringCenter() { return eeprom->getIntegerSetting(EEPROM_RC_STEERING_CENTER); }
    int getRcSteeringMax() { return eeprom->getIntegerSetting(EEPROM_RC_STEERING_MAX); }
    int getRcThrottleMin() { return eeprom->getIntegerSetting(EEPROM_RC_THROTTLE_MIN); }
    int getRcThrottleCenter() { return eeprom->getIntegerSetting(EEPROM_RC_THROTTLE_CENTER); }
    int getRcThrottleMax() { return eeprom->getIntegerSetting(EEPROM_RC_THROTTLE_MAX); }

    void readSpeedVolume() {
      if(Wire.requestFrom(M5DIAL_I2C_ADDRESS, 4))
      {
        m5DialConfigurationModeActive = Wire.read();
        uint8_t reg = Wire.read();

        if (reg == REGISTER_SPEED_VOLUME) {
          speed = Wire.read();
          volume = Wire.read();
        }

        if (m5DialConfigurationModeActive) {
          m5DialVersion++;
        }
      }
      else
      {
        // If we can't read the potentiometer, set to medium slow speed as a default
        speed = 35;
        volume = 35;
      }
    }

    void writeVersion() {
      Wire.beginTransmission(M5DIAL_I2C_ADDRESS);
      Wire.write(1);
      Wire.write(REGISTER_CAR_CODE_VERSION);
      Wire.write(RELEASE_VERSION);
      Wire.endTransmission();
    }

    void writeVolume() {
      Wire1.beginTransmission(ATTINY_SPEED_CONTROL_I2C_ADDRESS);
      Wire1.write(volume);
      Wire1.endTransmission();
    }

    float getSpeedMultiplier() {
      return constrain(map(speed, 1, 100, SPEED_CONFIGURATION_MIN_SPEED, SPEED_CONFIGURATION_MAX_SPEED), SPEED_CONFIGURATION_MIN_SPEED, SPEED_CONFIGURATION_MAX_SPEED) / 100.0;
    }

    // Linear Actuator
    int getSteeringCenter() { return eeprom->getIntegerSetting(EEPROM_ACTUATOR_CENTER); }
    int getSteeringMin() { return eeprom->getIntegerSetting(EEPROM_ACTUATOR_MIN); }
    int getSteeringMax() { return eeprom->getIntegerSetting(EEPROM_ACTUATOR_MAX); }

    // Extend Throttle
    boolean getExtendThrottle() { return eeprom->getBooleanSetting(EEPROM_EXTEND_THROTTLE); }
    int getExtendThrottleTimeMilliseconds() { return eeprom->getIntegerSetting(EEPROM_EXTEND_THROTTLE_TIME_MS); }

    // Extend Throttle
    boolean getChildThrottleOnly() { return eeprom->getBooleanSetting(EEPROM_CHILD_THROTTLE_ONLY); }

    void m5DialConfigureCar() {
      while (1) {
        // Send all configuration data to the M5Dial
        // Skip the Version configuration setting
        for (int i = 1; i < NUMBER_OF_CONFIGURATION_ENTRIES; i++) {
          Wire.beginTransmission(M5DIAL_I2C_ADDRESS);
    
          Wire.write(1); // Set to 
            uint8_t* p = (uint8_t*) configurationEntries[i].intValue;
            p[0] = Wire.read();
            p[1] = Wire.read();
          }
          
          Wire.endTransmission();
  
          delay(5);
        }

        delay(50);
      }
    }
    
    void configureCar() {
      int selection;
      int indexToEdit;write mode
          Wire.write(i); // The Register
  
          if (configurationEntries[i].dataType == BOOLEAN_CONFIGURATION) {
            Wire.write(configurationEntries[i].booleanValue);
          } else {
      int newIntValue;
      boolean newBooleanValue;
      
      // This method will never return control to the main program
      // The microcontroller must be reset for the car to resume normal operation
      while (1) {
        printMainMenu();
        selection = readMainMenu();
        indexToEdit = selection - 'a' + 1;

        Serial.print(eeprom->getSettingName(indexToEdit));
        Serial.print("Current Setting: ");

        if (eeprom->getSettingType(indexToEdit) == INTEGER_CONFIGURATION) {
          Serial.print(eeprom->getIntegerSetting(indexToEdit));
          Serial.print(" Enter new value: ");

          newIntValue = readIntValue();

          eeprom->setIntegerSetting(indexToEdit, newIntValue);
          Serial.println("");
          Serial.print("Saving New Value: ");
          Serial.println(newIntValue);
          eeprom->saveConfiguration();
        } else if (eeprom->getSettingType(indexToEdit) == BOOLEAN_CONFIGURATION) {
          if (eeprom->getBooleanSetting(indexToEdit)) {
            Serial.print("True");
          } else {
            Serial.print("False");
          }
          Serial.print(" Enter new value t/f: ");

          newBooleanValue = readBooleanValue();
          
          eeprom->setBooleanSetting(indexToEdit, newBooleanValue);
          Serial.println("");
          Serial.print("Saving New Value: ");
          Serial.println(newBooleanValue);
          eeprom->saveConfiguration();
        }
      }
    }

    int readIntValue() {
      int entry;
      while(1) {
        if (Serial.available() > 0) {
          entry = Serial.parseInt();
          break;
        }
      }

      // Discard newline and any other additional characters
      while (Serial.available() > 0) {
        Serial.read();
      }

      return entry;
    }

    boolean readBooleanValue() {
      int entry;
      while(1) {
        if (Serial.available() > 0) {
          entry = Serial.read();
          if (entry != 't' && entry != 'f') {
            Serial.print("Invalid Entry: ");
            Serial.println(entry);
          } else {
            break;
          }
        }
      }

      // Discard newline and any other additional characters
      while (Serial.available() > 0) {
        Serial.read();
      }

      return entry == 't';
    }

    void printMainMenu() {
      char option;

      if (eeprom->isDefaultConfiguration()) {
        Serial.println("Default settings used");
      } else {
        Serial.println("Loaded from EEPROM");
      }
      
      Serial.print("Configuration Version: ");
      Serial.println(eeprom->getSavedConfigurationVersion());
      
      for (int i = 1; i < NUMBER_OF_CONFIGURATION_ENTRIES; i++) {
        option = 'a' + i - 1;
        Serial.print(option);
        Serial.print(") ");
        Serial.print(eeprom->getSettingName(i));
        Serial.print(": ");

        if (eeprom->getSettingType(i) == INTEGER_CONFIGURATION) {
          Serial.println(eeprom->getIntegerSetting(i));
        } else if (eeprom->getSettingType(i) == BOOLEAN_CONFIGURATION) {
          if (eeprom->getBooleanSetting(i)) {
            Serial.println("True");
          } else {
            Serial.println("False");
          }
        }
      }

      Serial.println("");
      Serial.println("Enter the letter of the item you wish to edit in lowercase.");
    }

    int readMainMenu() {
      int entry;
      while(1) {
        if (Serial.available() > 0) {
          entry = Serial.read();
          if (entry < 'a' || entry > 'w') {
            Serial.print("Invalid Entry: ");
            Serial.println(entry);
          } else {
            break;
          }
        }
      }

      // Discard newline and any other additional characters
      while (Serial.available() > 0) {
        Serial.read();
      }

      return entry;
    }

    void getStatus(char * status) {
      sprintf(status, "[Configuration] M5Deteced: %s Dial Config: %s %i Version: %i  Invert Joy X:%s Y:%s Joy Steering:%i %i %i  Speed:%i Volume: %i RC:%s %s Min/C/Max:%i %i %i", 
        m5DialDetected ? "true" : "false",
        m5DialConfigurationModeActive ? "true" : "false",
        m5DialVersion,
        getConfigurationVersion(),
        getInvertJoystickX() ? "true" : "false",
        getInvertJoystickY() ? "true" : "false",
        getJoystickSteeringMin(),
        getJoystickSteeringCenter(),
        getJoystickSteeringMax(),
        speed,
        volume,
        useRc() ? "true" : "false",
        getChildThrottleOnly() ? "true" : "false",
        getSteeringMin(),
        getSteeringCenter(),
        getSteeringMax());
    }
};

/**
 * Configuration Class
 * 
 * This class serves to interpret the eeprom settings to define the configuration for this car
 */
#include <Wire.h>

class Configuration {
  private:
    Eeprom *eeprom;
    int maxSpeedPin;
    uint8_t speed = 5;
    uint8_t volume = 10;
    
  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    Configuration() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init(Eeprom *e) {
      eeprom = e;

      Wire1.setSDA(PIN_I2C_SDA);
      Wire1.setSCL(PIN_I2C_SCL);
      Wire1.begin();
    }

    // Called periodically to update any values read in real-time
    void update() {
      readSpeedVolume();
      writeVolume(); // Send the selected volume to the ATTiny handling audio output
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
      if(Wire1.requestFrom(M5DIAL_I2C_ADDRESS, 2))
      {
        speed = Wire1.read();
        volume = Wire1.read();
      }
      else
      {
        // If we can't read the potentiometer, set to medium slow speed as a default
        speed = 35;
        volume = 35;
      }
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
    
    void configureCar() {
      int selection;
      int indexToEdit;
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
          if (entry < 'a' || entry > 'v') {
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
      sprintf(status, "[Configuration] Version: %i  Invert Joy X:%s Y:%s Joy Steering:%i %i %i  Speed:%i Volume: %i RC:%s Min/C/Max:%i %i %i", 
        getConfigurationVersion(),
        getInvertJoystickX() ? "true" : "false",
        getInvertJoystickY() ? "true" : "false",
        getJoystickSteeringMin(),
        getJoystickSteeringCenter(),
        getJoystickSteeringMax(),
        speed,
        volume,
        useRc() ? "true" : "false",
        getSteeringMin(),
        getSteeringCenter(),
        getSteeringMax());
    }
};

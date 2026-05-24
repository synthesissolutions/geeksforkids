/**
 * Configuration Class
 * 
 * This class serves to interpret the eeprom settings to define the configuration for this car
 */
#include <Wire.h>
#include <SparkFunTMP102.h>

#define REGISTER_CAR_CODE_VERSION         98
#define REGISTER_SPEED_VOLUME             99
#define REGISTER_PCB_TEMPERATURE          100
#define REGISTER_BATTERY_VOLTAGE          101

TMP102 tempSensor;
boolean tempSensorAvailable = false;

struct M5DialCurrentConfiguration {
  boolean success;
  uint8_t configMode;
  uint8_t reg;
  uint8_t firstByte;
  uint8_t secondByte;
  boolean validRegister;
};

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
    uint8_t m5DialConfigModeActiveCount = 0;
    
  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    Configuration() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init(Eeprom *e) {
      eeprom = e;

      Wire1.setSDA(PIN_M5DIAL_I2C_SDA);
      Wire1.setSCL(PIN_M5DIAL_I2C_SCL);
      Wire1.begin();

      Wire.setSDA(PIN_I2C_SDA);
      Wire.setSCL(PIN_I2C_SCL);
      Wire.begin();

      if (tempSensor.begin(TEMP_SENSOR_I2C_ADDRESS, Wire)) {
        tempSensorAvailable = true;
        // set the number of consecutive faults before triggering alarm.
        // 0-3: 0:1 fault, 1:2 faults, 2:4 faults, 3:6 faults.
        tempSensor.setFault(0);  // Trigger alarm immediately
        
        // set the polarity of the Alarm. (0:Active LOW, 1:Active HIGH).
        tempSensor.setAlertPolarity(1); // Active HIGH
        
        // set the sensor in Comparator Mode (0) or Interrupt Mode (1).
        tempSensor.setAlertMode(0); // Comparator Mode.
        
        // set the Conversion Rate (how quickly the sensor gets a new reading)
        //0-3: 0:0.25Hz, 1:1Hz, 2:4Hz, 3:8Hz
        tempSensor.setConversionRate(2);
        
        //set Extended Mode.
        //0:12-bit Temperature(-55C to +128C) 1:13-bit Temperature(-55C to +150C)
        tempSensor.setExtendedMode(0);
      
        //set T_HIGH, the upper limit to trigger the alert on
        //sensor0.setHighTempF(85.0);  // set T_HIGH in F
        tempSensor.setHighTempC(75); // set T_HIGH in C
        
        //set T_LOW, the lower limit to shut turn off the alert
        //sensor0.setLowTempF(84.0);  // set T_LOW in F
        tempSensor.setLowTempC(74); // set T_LOW in C
      }
      
      pinMode(PIN_BATTERY_VOLTAGER_DIVIDER, INPUT);
      pinMode(PIN_REVISION_DIVIDER, INPUT);
    }

    void detectM5Dial() {
      Wire1.beginTransmission(M5DIAL_I2C_ADDRESS);

      Wire1.write(0); // Set to read mode
      Wire1.write(EEPROM_VERSION); // The Register
      
      Wire1.endTransmission();

      delay(5);
      
      if(Wire1.requestFrom(M5DIAL_I2C_ADDRESS, 4))
      {
        uint8_t* p = (uint8_t*) &m5DialVersion;

        bool configMode = Wire1.read();
        uint8_t reg = Wire1.read();

        if (reg == EEPROM_VERSION) {
          p[0] = Wire1.read();
          p[1] = Wire1.read();
          m5DialDetected = true;        
        }
      }
    }
    
    // Called periodically to update any values read in real-time
    void update() {
      if (m5DialDetected) {
        readSpeedVolume();
  
        if (!versionSent) {
          versionSent = true;
          writeVersion();
        }
        writePcbTemperature();
        writeBatteryVoltage();
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

    boolean getReverseRcChannels() { return eeprom->getBooleanSetting(EEPROM_REVERSE_RC_CHANNELS); }

    float getBatteryVoltage() {
      if (!tempSensorAvailable) {
        return 0;
      }
      
      int rawDivider = analogRead(PIN_BATTERY_VOLTAGER_DIVIDER);

      return (float)rawDivider / DIVIDER_ONE_VOLT;
    }

    int getPcbRevision() {
      int rawDivider = analogRead(PIN_REVISION_DIVIDER);

      // TODO figure this out for real
      if (rawDivider < 20) {
        return 1;
      }

      return 2;
    }

    float getPcbTemperature() {
      return tempSensor.readTempC();
    }

    void readSpeedVolume() {
      uint8_t tempConfigurationMode;
      
      if(Wire1.requestFrom(M5DIAL_I2C_ADDRESS, 4))
      {
        tempConfigurationMode = Wire1.read(); // Check to make sure the value is exactly one so noisy data has a lower chance of triggering configuration mode
        if (tempConfigurationMode == 1) {
          m5DialConfigModeActiveCount++;
          // We need 5 consecutive configuration mode values of 1 to enter configuration mode
          // this should eliminate issues with bad data
          if (m5DialConfigModeActiveCount > 4) {
            m5DialConfigurationModeActive = true;
          }
        } else {
          m5DialConfigModeActiveCount = 0;
        }
                
        uint8_t reg = Wire1.read();

        if (reg == REGISTER_SPEED_VOLUME) {
          speed = Wire1.read();
          volume = Wire1.read();
        }
      }
      else
      {
        // If we can't read the potentiometer, set to medium slow speed as a default
        speed = 35;
        volume = 35;
      }
    }


    void writePcbTemperature() {
      // Send temperature as integer in Celsius for simplicity
      // multiple by 100 on this end
      int16_t pcbTemp = (int16_t)(getPcbTemperature() * 100);
      Wire1.beginTransmission(M5DIAL_I2C_ADDRESS);
      Wire1.write(1);
      Wire1.write(REGISTER_PCB_TEMPERATURE);
      uint8_t* p = (uint8_t*) &pcbTemp;
      Wire1.write(p[0]);
      Wire1.write(p[1]);
      Wire1.endTransmission();
    }
    
    void writeBatteryVoltage() {
      // Send battery voltage as integer for simplicity
      // multiple by 100 on this end
      int16_t batteryVoltage = (int16_t)(getBatteryVoltage() * 100);
      Wire1.beginTransmission(M5DIAL_I2C_ADDRESS);
      Wire1.write(1);
      Wire1.write(REGISTER_BATTERY_VOLTAGE);
      uint8_t* p = (uint8_t*) &batteryVoltage;
      Wire1.write(p[0]);
      Wire1.write(p[1]);
      Wire1.endTransmission();
    }

    void writeVersion() {
      Wire1.beginTransmission(M5DIAL_I2C_ADDRESS);
      Wire1.write(1);
      Wire1.write(REGISTER_CAR_CODE_VERSION);
      Wire1.write(RELEASE_VERSION);
      Wire1.endTransmission();
    }

    int getVolume() {
      return (int)volume;
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

    void sendConfigurationsToM5Dial() {
      // Send all configuration data to the M5Dial
      // Skip the Version configuration setting
      for (int i = 1; i < NUMBER_OF_CONFIGURATION_ENTRIES; i++) {
        Wire1.beginTransmission(M5DIAL_I2C_ADDRESS);
 
        Wire1.write(1); // Set to write mode
        Wire1.write(i); // The Register

        if (configurationEntries[i].dataType == BOOLEAN_CONFIGURATION) {
          Wire1.write(configurationEntries[i].booleanValue);
        } else {
          uint8_t* p = (uint8_t*) &configurationEntries[i].intValue;
          Wire1.write(p[0]);
          Wire1.write(p[1]);
        }
 
        Wire1.endTransmission();

        delay(10);
      }

      // Send 
    }

    M5DialCurrentConfiguration readCurrentM5DialConfiguration() {
      M5DialCurrentConfiguration config;

      if(Wire.requestFrom(M5DIAL_I2C_ADDRESS, 4)) {
        config.success = true;
        config.configMode = Wire.read();
        config.reg = Wire.read();
        config.firstByte = Wire.read();
        config.secondByte = Wire.read();
        config.validRegister = config.reg > EEPROM_VERSION && config.reg < NUMBER_OF_CONFIGURATION_ENTRIES;
      } else {
        config.success = false;
      }

      return config;
    }

    void saveM5DialConfiguration(M5DialCurrentConfiguration config) {
      if (configurationEntries[config.reg].dataType == BOOLEAN_CONFIGURATION) {
        if (configurationEntries[config.reg].booleanValue != config.firstByte) {
          Serial.print("write boolean reg: ");
          Serial.print(config.reg);
          Serial.print(" new value: ");
          Serial.println(config.firstByte);
          
          configurationEntries[config.reg].booleanValue = config.firstByte;
          eeprom->saveBooleanValue(config.reg, configurationEntries[config.reg].booleanValue);
        }
      } else {
        int16_t newValue = 0;
        uint8_t* p = (uint8_t*) &newValue;
        p[0] = config.firstByte;
        p[1] = config.secondByte;

        if (configurationEntries[config.reg].intValue != newValue) {
          Serial.print("write integer reg: ");
          Serial.print(config.reg);
          Serial.print(" new value: ");
          Serial.println(newValue);
          configurationEntries[config.reg].intValue = newValue;
          eeprom->saveIntegerValue(config.reg, configurationEntries[config.reg].intValue);
        }
      }

    }

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

      Serial.print("Car Code Version: ");
      Serial.println(RELEASE_VERSION);
      
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
          if (entry < 'a' || entry > 'x') {
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
      sprintf(status, "[Configuration] PCB Rev: %i Battery: %.2f PCB Temp: %.2f c Speed:%i Volume: %i  M5Det: %s Dial Cfg: %s %i Version: %i\n\t\tInvert Joy X:%s Y:%s Joy Steering:%i %i %i RC:%s %s Min/C/Max:%i %i %i", 
        getPcbRevision(),
        getBatteryVoltage(),
        getPcbTemperature(),
        speed,
        volume,
        m5DialDetected ? "true" : "false",
        m5DialConfigurationModeActive ? "true" : "false",
        m5DialVersion,
        getConfigurationVersion(),
        getInvertJoystickX() ? "true" : "false",
        getInvertJoystickY() ? "true" : "false",
        getJoystickSteeringMin(),
        getJoystickSteeringCenter(),
        getJoystickSteeringMax(),
        useRc() ? "true" : "false",
        getChildThrottleOnly() ? "true" : "false",
        getSteeringMin(),
        getSteeringCenter(),
        getSteeringMax());
    }
};

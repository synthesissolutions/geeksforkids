#include <EEPROM.h>

#define NUMBER_OF_CONFIGURATION_ENTRIES 25

#define EEPROM_VERSION              0
#define EEPROM_ACTUATOR_MIN         1
#define EEPROM_ACTUATOR_CENTER      2
#define EEPROM_ACTUATOR_MAX         3
#define EEPROM_USE_RC               4
#define EEPROM_RC_STEERING_MIN      5
#define EEPROM_RC_STEERING_CENTER   6
#define EEPROM_RC_STEERING_MAX      7
#define EEPROM_RC_THROTTLE_MIN      8
#define EEPROM_RC_THROTTLE_CENTER   9
#define EEPROM_RC_THROTTLE_MAX      10
#define EEPROM_USE_PWM_JOYSTICK_X   11
#define EEPROM_USE_PWM_JOYSTICK_Y   12
#define EEPROM_INVERT_JOYSTICK_X    13
#define EEPROM_INVERT_JOYSTICK_Y    14
#define EEPROM_JOYSTICK_STEERING_MIN    15
#define EEPROM_JOYSTICK_STEERING_CENTER 16
#define EEPROM_JOYSTICK_STEERING_MAX    17
#define EEPROM_JOYSTICK_THROTTLE_MIN    18
#define EEPROM_JOYSTICK_THROTTLE_CENTER 19
#define EEPROM_JOYSTICK_THROTTLE_MAX    20
#define EEPROM_EXTEND_THROTTLE          21
#define EEPROM_EXTEND_THROTTLE_TIME_MS  22
#define EEPROM_CHILD_THROTTLE_ONLY      23
#define EEPROM_REVERSE_RC_CHANNELS      24

#define INTEGER_CONFIGURATION 1
#define BOOLEAN_CONFIGURATION 2

#define RC_DEFAULT_MIN        1125
#define RC_DEFAULT_MAX        1875
#define ACTUATOR_DEFAULT_MIN  -30
#define ACTUATOR_DEFAULT_MAX  30

/**
 * Eeprom Class
 * 
 * This class stores and retrievs settings from Eeprom to define the configuration for this car
 */

const int CURRENT_SETTINGS_VERSION = 6;

struct ConfigurationEntry {
  String name;
  unsigned int eeAddress;
  int dataType;
  boolean booleanValue;
  int intValue;
};

ConfigurationEntry configurationEntries[] = {
  {"Version", 0, INTEGER_CONFIGURATION, false, CURRENT_SETTINGS_VERSION},
  {"Actuator Min", 8, INTEGER_CONFIGURATION, false, ACTUATOR_DEFAULT_MIN},  // in scaled units from -100 to 100
  {"Actuator Center", 12, INTEGER_CONFIGURATION, false, 0},  // in scaled units from -100 to 100
  {"Actuator Max", 16, INTEGER_CONFIGURATION, false, ACTUATOR_DEFAULT_MAX},   // in scaled units from -100 to 100
  {"Use RC", 20, BOOLEAN_CONFIGURATION, true, 0},
  {"RC Steering Min", 24, INTEGER_CONFIGURATION, false, RC_DEFAULT_MIN},  // All RC values are in PWM duty cycle microseconds
  {"RC Steering Center", 28, INTEGER_CONFIGURATION, false, 1500},
  {"RC Steering Max", 32, INTEGER_CONFIGURATION, false, RC_DEFAULT_MAX},
  {"RC Throttle Min", 36, INTEGER_CONFIGURATION, false, RC_DEFAULT_MIN},
  {"RC Throttle Center", 40, INTEGER_CONFIGURATION, false, 1500},
  {"RC Throttle Max", 44, INTEGER_CONFIGURATION, false, RC_DEFAULT_MAX},
  {"Use PWM Joystick X", 48, BOOLEAN_CONFIGURATION, true, 0},
  {"Use PWM Joystick Y", 52, BOOLEAN_CONFIGURATION, true, 0},
  {"Invert Joystick X", 56, BOOLEAN_CONFIGURATION, true, 0},
  {"Invert Joystick Y", 60, BOOLEAN_CONFIGURATION, true, 0},
  {"Joystick Steering Min", 64, INTEGER_CONFIGURATION, false, 200}, // Joystick values are in PWM duty cycle microseconds or analog readings 0 - 1023
  {"Joystick Steering Center", 68, INTEGER_CONFIGURATION, false, 500},
  {"Joystick Steering Max", 72, INTEGER_CONFIGURATION, false, 800},
  {"Joystick Throttle Min", 76, INTEGER_CONFIGURATION, false, 200},
  {"Joystick Throttle Center", 80, INTEGER_CONFIGURATION, false, 500},
  {"Joystick Throttle Max", 84, INTEGER_CONFIGURATION, false, 800},
  {"Extend Throttle", 88, BOOLEAN_CONFIGURATION, false, 0},
  {"Extend Throttle Milliseconds", 92, INTEGER_CONFIGURATION, false, 500},
  {"Child Throttle Only", 96, BOOLEAN_CONFIGURATION, false, 0},
  {"Reverse RC Channels", 100, BOOLEAN_CONFIGURATION, false, 0}
};
    
class Eeprom {
  private:
    boolean isConfigurationDefault = false;

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    Eeprom() {  
    }

    void init() {
      EEPROM.begin(512);
      
      int savedVersion = getSavedConfigurationVersion();
      
      if (savedVersion == CURRENT_SETTINGS_VERSION) {
        loadConfigurationSettings();
      } else if (savedVersion == 4 && CURRENT_SETTINGS_VERSION == 5) {
        loadConfigurationSettings();
        
        setBooleanSetting(EEPROM_CHILD_THROTTLE_ONLY, false);
        setIntegerSetting(EEPROM_VERSION, CURRENT_SETTINGS_VERSION);

        saveConfiguration();
      } else if ((savedVersion == 4 || savedVersion == 5) && CURRENT_SETTINGS_VERSION == 6) {
        loadConfigurationSettings();

        if (savedVersion == 4) {
          setBooleanSetting(EEPROM_CHILD_THROTTLE_ONLY, false);
        }
        setIntegerSetting(EEPROM_VERSION, CURRENT_SETTINGS_VERSION);
        setIntegerSetting(EEPROM_RC_STEERING_MIN, RC_DEFAULT_MIN);
        setIntegerSetting(EEPROM_RC_STEERING_MAX, RC_DEFAULT_MAX);
        setIntegerSetting(EEPROM_RC_THROTTLE_MIN, RC_DEFAULT_MIN);
        setIntegerSetting(EEPROM_RC_THROTTLE_MAX, RC_DEFAULT_MAX);
        setIntegerSetting(EEPROM_ACTUATOR_MIN, ACTUATOR_DEFAULT_MIN);
        setIntegerSetting(EEPROM_ACTUATOR_MAX, ACTUATOR_DEFAULT_MAX);
        setBooleanSetting(EEPROM_REVERSE_RC_CHANNELS, false);

        saveConfiguration();
      } else {
        saveConfiguration(); // This will save the default values
        isConfigurationDefault = true;      
      }
    }

    /*
     * getters ... read settings from Eeprom cache
     */
    int getIntegerSetting(int index) {
      return configurationEntries[index].intValue;
    }

    int getBooleanSetting(int index) {
      return configurationEntries[index].booleanValue;
    }

    String getSettingName(int index) {
      return configurationEntries[index].name;
    }

    int getSettingType(int index) {
      return configurationEntries[index].dataType;
    }

    int isDefaultConfiguration() {
      return isConfigurationDefault;
    }
    
    /*
     * setters ... write settings to Eeprom cache
     */
    void setIntegerSetting(int index, int value) {
      configurationEntries[index].intValue = value;
    }

    void setBooleanSetting(int index, boolean value) {
      configurationEntries[index].booleanValue = value;
    }

    int getSavedConfigurationVersion() {
      ConfigurationEntry entry = configurationEntries[EEPROM_VERSION];
      int intValue;
      EEPROM.get(entry.eeAddress, intValue);      

      return intValue;
    }

    /*
     * Load the configuration settings from Eeprom into cache
     */
    void loadConfigurationSettings() {
      int intValue;
      boolean booleanValue;
      
      for (int i = 0; i < NUMBER_OF_CONFIGURATION_ENTRIES; i++) {
        if (configurationEntries[i].dataType == INTEGER_CONFIGURATION) {
          EEPROM.get(configurationEntries[i].eeAddress, intValue);
          configurationEntries[i].intValue = intValue;
        } else if (configurationEntries[i].dataType == BOOLEAN_CONFIGURATION) {
          EEPROM.get(configurationEntries[i].eeAddress, booleanValue);
          configurationEntries[i].booleanValue = booleanValue;
        }
      }
    }

    /*
     * Save the configuration settings from cache into Eeprom
     */
    void saveConfiguration() {
      for (int i = 0; i < NUMBER_OF_CONFIGURATION_ENTRIES; i++) {
        if (configurationEntries[i].dataType == INTEGER_CONFIGURATION) {
          EEPROM.put(configurationEntries[i].eeAddress, configurationEntries[i].intValue);
        } else if (configurationEntries[i].dataType == BOOLEAN_CONFIGURATION) {
          if (configurationEntries[i].booleanValue) {
            EEPROM.put(configurationEntries[i].eeAddress, 1);
          } else {
            EEPROM.put(configurationEntries[i].eeAddress, 0);
          }
        }
      }

      if (EEPROM.commit()) {
        Serial.println("EEPROM successfully committed");
      } else {
        Serial.println("ERROR! EEPROM commit failed");
      }
    }

    void saveIntegerValue(int index, int value) {
      if (configurationEntries[index].dataType == INTEGER_CONFIGURATION) {
        EEPROM.put(configurationEntries[index].eeAddress, configurationEntries[index].intValue);
      }

      if (EEPROM.commit()) {
        Serial.println("EEPROM successfully committed");
      } else {
        Serial.println("ERROR! EEPROM commit failed");
      }
    }

    void saveBooleanValue(int index, boolean value) {
      if (configurationEntries[index].dataType == BOOLEAN_CONFIGURATION) {
        if (configurationEntries[index].booleanValue) {
          EEPROM.put(configurationEntries[index].eeAddress, 1);
        } else {
          EEPROM.put(configurationEntries[index].eeAddress, 0);
        }
      }

      if (EEPROM.commit()) {
        Serial.println("EEPROM successfully committed");
      } else {
        Serial.println("ERROR! EEPROM commit failed");
      }
    }

     void getStatus(char * status) {
      sprintf(status, "[EEprom] Version: %i Steering: %i %i %i Configuration: %s", getIntegerSetting(EEPROM_VERSION), 
        getIntegerSetting(EEPROM_JOYSTICK_STEERING_MIN), getIntegerSetting(EEPROM_JOYSTICK_STEERING_CENTER), 
        getIntegerSetting(EEPROM_JOYSTICK_STEERING_MAX), isConfigurationDefault ? "Default" : "Eeprom");
    }
};

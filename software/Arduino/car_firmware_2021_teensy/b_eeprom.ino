#include <ArduinoJson.h>
#include <EEPROM.h>

#define NUMBER_OF_CONFIGURATION_ENTRIES 21

const String EEPROM_VERSION = "version";
const String EEPROM_ACTUATOR_MIN = "actuatorMin";
const String EEPROM_ACTUATOR_CENTER = "actuatorCenter";
const String EEPROM_ACTUATOR_MAX = "actuatorMax";
const String EEPROM_USE_RC = "useRc";
const String EEPROM_RC_STEERING_MIN = "rcSteeringMin";
const String EEPROM_RC_STEERING_CENTER = "rcSteeringCenter";
const String EEPROM_RC_STEERING_MAX = "rcSteeringMax";
const String EEPROM_RC_THROTTLE_MIN = "rcThrottleMin";
const String EEPROM_RC_THROTTLE_CENTER = "rcThrottleCenter";
const String EEPROM_RC_THROTTLE_MAX = "rcThrottleMax";
const String EEPROM_USE_PWM_JOYSTICK_X = "usePwmJoystickX";
const String EEPROM_USE_PWM_JOYSTICK_Y = "usePwmJoystickY";
const String EEPROM_INVERT_JOYSTICK_X = "invertJoystickX";
const String EEPROM_INVERT_JOYSTICK_Y = "invertJoystickY";
const String EEPROM_JOYSTICK_STEERING_MIN = "joystickSteeringMin";
const String EEPROM_JOYSTICK_STEERING_CENTER = "joystickSteeringCenter";
const String EEPROM_JOYSTICK_STEERING_MAX = "joystickSteeringMax";
const String EEPROM_JOYSTICK_THROTTLE_MIN = "joystickThrottleMin";
const String EEPROM_JOYSTICK_THROTTLE_CENTER = "joystickThrottleCenter";
const String EEPROM_JOYSTICK_THROTTLE_MAX = "joystickThrottleMax";

/**
 * Eeprom Class
 * 
 * This class serves to interpret the dip switch setting to define the configuration for this car
 */

const int CURRENT_SETTINGS_VERSION = 3;

struct ConfigurationEntry {
  String name;
  unsigned int eeAddress;
  String dataType;
  boolean booleanValue;
  int intValue;
  String stringValue;
};


ConfigurationEntry configurationEntries[] = {
  {EEPROM_VERSION, 0, "Integer", false, CURRENT_SETTINGS_VERSION, ""},
  {EEPROM_ACTUATOR_MIN, 8, "Integer", false, -50, ""},  // in scaled units from -100 to 100
  {EEPROM_ACTUATOR_CENTER, 12, "Integer", false, 0, ""},  // in scaled units from -100 to 100
  {EEPROM_ACTUATOR_MAX, 16, "Integer", false, 50, ""},   // in scaled units from -100 to 100
  {EEPROM_USE_RC, 20, "Boolean", true, 0, ""},
  {EEPROM_RC_STEERING_MIN, 24, "Integer", false, 1000, ""},  // All RC values are in PWM duty cycle milliseconds
  {EEPROM_RC_STEERING_CENTER, 28, "Integer", false, 1500, ""},
  {EEPROM_RC_STEERING_MAX, 32, "Integer", false, 2000, ""},
  {EEPROM_RC_STEERING_MIN, 36, "Integer", false, 1000, ""},
  {EEPROM_RC_STEERING_CENTER, 40, "Integer", false, 1500, ""},
  {EEPROM_RC_STEERING_MAX, 44, "Integer", false, 2000, ""},
  {EEPROM_USE_PWM_JOYSTICK_X, 48, "Boolean", false, 0, ""},
  {EEPROM_USE_PWM_JOYSTICK_Y, 52, "Boolean", false, 0, ""},
  {EEPROM_INVERT_JOYSTICK_X, 56, "Boolean", true, 0, ""},
  {EEPROM_INVERT_JOYSTICK_Y, 60, "Boolean", true, 0, ""},
  {EEPROM_JOYSTICK_STEERING_MIN, 64, "Integer", false, 1000, ""}, // Joystick values are in PWM duty cycle milliseconds or analog readings 0 - 1023
  {EEPROM_JOYSTICK_STEERING_CENTER, 68, "Integer", false, 1500, ""},
  {EEPROM_JOYSTICK_STEERING_MAX, 72, "Integer", false, 2000, ""},
  {EEPROM_JOYSTICK_THROTTLE_MIN, 76, "Integer", false, 1000, ""},
  {EEPROM_JOYSTICK_THROTTLE_CENTER, 80, "Integer", false, 1500, ""},
  {EEPROM_JOYSTICK_THROTTLE_MAX, 84, "Integer", false, 2000, ""}
};
    
class Eeprom {
  private:
    const unsigned int EE_ADDRESS = 0;
    String loadingLogMessage = "Loaded from Eeprom";
    
    StaticJsonDocument<1024> currentSettingsJson;  

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    Configuration() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init() {
      loadConfigurationSettingsAsJson();

      if (getIntegerSetting("version") != CURRENT_SETTINGS_VERSION) {
        resetConfiguration();
        saveConfiguration();
        loadingLogMessage = "Loaded from defaults";
      }
    }

    /*
     * getters ... read settings from EEprom
     */
    int getIntegerSetting(String configurationEntryName) {
      // TODO check the configuration enry and make sure it is an integer value?
      return currentSettingsJson[configurationEntryName];
    }

    int getBooleanSetting(String configurationEntryName) {
      return currentSettingsJson[configurationEntryName];
    }
    
    void setIntegerSetting(String configurationEntryName, int value) {
      currentSettingsJson[configurationEntryName] = value;
    }

    void setBooleanSetting(String configurationEntryName, boolean value) {
      currentSettingsJson[configurationEntryName] = value;
    }

    JsonDocument getCurrentSettingsAsJson() {
      return currentSettingsJson;
    }

    JsonDocument loadConfigurationSettingsAsJson() {
      int intValue;
      boolean booleanValue;
      
      for (int i = 0; i < NUMBER_OF_CONFIGURATION_ENTRIES; i++) {
        ConfigurationEntry entry = configurationEntries[i];
        if (entry.dataType == "Integer") {
          EEPROM.get(entry.eeAddress, intValue);
          currentSettingsJson[entry.name] = intValue;
        } else if (entry.dataType == "Boolean") {
          EEPROM.get(entry.eeAddress, booleanValue);
          currentSettingsJson[entry.name] = booleanValue;
        } else {
          // ignore for now
        }
      }
    }

    String saveConfiguration() {
      for (int i = 0; i < NUMBER_OF_CONFIGURATION_ENTRIES; i++) {
        ConfigurationEntry entry = configurationEntries[i];
        if (entry.dataType == "Integer") {
          int value = currentSettingsJson[entry.name];
          EEPROM.put(entry.eeAddress, value);
        } else if (entry.dataType == "Boolean") {
          boolean booleanValue = currentSettingsJson[entry.name];
          Serial.println(booleanValue);
          if (currentSettingsJson[entry.name]) {
            EEPROM.put(entry.eeAddress, 1);
          } else {
            EEPROM.put(entry.eeAddress, 0);
          }
        } else {
          // ignore for now
        }
      }
      
      return "{\"Success\": true}";
    }
    
    String resetConfiguration() {
      for (int i = 0; i < NUMBER_OF_CONFIGURATION_ENTRIES; i++) {
        ConfigurationEntry entry = configurationEntries[i];
        if (entry.dataType == "Integer") {
          EEPROM.put(entry.eeAddress, entry.intValue);
          currentSettingsJson[entry.name] = entry.intValue;
        } else if (entry.dataType == "Boolean") {
          EEPROM.put(entry.eeAddress, entry.booleanValue);
          currentSettingsJson[entry.name] = entry.booleanValue;
        } else {
          // ignore for now
        }
      }
      
      return "{\"Success\": true}";
    }

     void getStatus(char * status) {
      sprintf(status, "[EEprom] Version: %i Configuration %s", getIntegerSetting("version"), loadingLogMessage);
    }
};

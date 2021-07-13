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

const int CURRENT_SETTINGS_VERSION = 2;

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
  {EEPROM_USE_RC, 20, "Boolean", false, 0, ""},
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
  {EEPROM_JOYSTICK_STEERING_MIN, 64, "Integer", false, 0, ""}, // Joystick values are in PWM duty cycle milliseconds or analog readings 0 - 1023
  {EEPROM_JOYSTICK_STEERING_CENTER, 68, "Integer", false, 500, ""},
  {EEPROM_JOYSTICK_STEERING_MAX, 72, "Integer", false, 950, ""},
  {EEPROM_JOYSTICK_THROTTLE_MIN, 76, "Integer", false, 0, ""},
  {EEPROM_JOYSTICK_THROTTLE_CENTER, 80, "Integer", false, 500, ""},
  {EEPROM_JOYSTICK_THROTTLE_MAX, 84, "Integer", false, 950, ""}
};
    
class Eeprom {
  private:
    String loadingLogMessage = "Loaded from Eeprom";
    
    int getConfigurationIndexByName(String configurationName) {
      for (int i = 0; i < NUMBER_OF_CONFIGURATION_ENTRIES; i++) {
        ConfigurationEntry entry = configurationEntries[i];
        if (configurationName == entry.name) {
          return i;
        }
      }

      return -1;
    }

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    Eeprom() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init() {
      if (getSavedConfigurationVersion() == CURRENT_SETTINGS_VERSION) {
        loadConfigurationSettings();
      } else {
        saveConfiguration(); // This will save the default values
        loadingLogMessage = "Loaded from defaults";        
      }
    }

    /*
     * getters ... read settings from EEprom
     */
    int getIntegerSetting(String configurationEntryName) {
      int index = getConfigurationIndexByName(configurationEntryName);
      return configurationEntries[index].intValue;
    }

    int getBooleanSetting(String configurationEntryName) {
      int index = getConfigurationIndexByName(configurationEntryName);
      return configurationEntries[index].booleanValue;
    }
    
    void setIntegerSetting(String configurationEntryName, int value) {
      int index = getConfigurationIndexByName(configurationEntryName);
      ConfigurationEntry entry = configurationEntries[index];
      entry.intValue = value;
    }

    void setBooleanSetting(String configurationEntryName, boolean value) {
      int index = getConfigurationIndexByName(configurationEntryName);
      ConfigurationEntry entry = configurationEntries[index];
      entry.booleanValue = value;
    }

    int getSavedConfigurationVersion() {
      // The first configuration entry is always the version
      ConfigurationEntry entry = configurationEntries[0];
      int intValue;
      EEPROM.get(entry.eeAddress, intValue);      

      return intValue;
    }
    
    void loadConfigurationSettings() {
      int intValue;
      boolean booleanValue;
      
      for (int i = 0; i < NUMBER_OF_CONFIGURATION_ENTRIES; i++) {
        ConfigurationEntry entry = configurationEntries[i];
        if (entry.dataType == "Integer") {
          EEPROM.get(entry.eeAddress, intValue);
          entry.intValue = intValue;
        } else if (entry.dataType == "Boolean") {
          EEPROM.get(entry.eeAddress, booleanValue);
          entry.booleanValue = booleanValue;
          // ignore for now        } else {

        }
      }
    }

    void saveConfiguration() {
      for (int i = 0; i < NUMBER_OF_CONFIGURATION_ENTRIES; i++) {
        ConfigurationEntry entry = configurationEntries[i];
        if (entry.dataType == "Integer") {
          EEPROM.put(entry.eeAddress, entry.intValue);
        } else if (entry.dataType == "Boolean") {
          if (entry.booleanValue) {
            EEPROM.put(entry.eeAddress, 1);
          } else {
            EEPROM.put(entry.eeAddress, 0);
          }
        } else {
          // ignore for now
        }
      }
    }

     void getStatus(char * status) {
      sprintf(status, "[EEprom] Version: %i Configuration %s", getIntegerSetting("version"), loadingLogMessage);
    }
};

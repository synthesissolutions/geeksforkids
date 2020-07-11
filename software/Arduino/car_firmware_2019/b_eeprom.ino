#include <ArduinoJson.h>
#include <EEPROM.h>

#define NUMBER_OF_CONFIGURATION_ENTRIES 14

const String EEPROM_VERSION = "version";
const String EEPROM_MAX_SPEED = "maxSpeed";
const String EEPROM_ACTUATOR_CENTER = "actuatorCenter";
const String EEPROM_ACTUATOR_MIN = "actuatorMin";
const String EEPROM_ACTUATOR_MAX = "actuatorMax";
const String EEPROM_USE_JOYSTICK = "useJoystick";
const String EEPROM_INVERT_JOYSTICK_X = "invertJoystickX";
const String EEPROM_INVERT_JOYSTICK_Y = "invertJoystickY";
const String EEPROM_USE_RC = "useRc";
const String EEPROM_USE_DRIVE_BY_WIRE = "usePotGo";
const String EEPROM_DRIVE_BY_WIRE_CENTER = "steeringPotCenter";
const String EEPROM_DRIVE_BY_WIRE_MIN = "steeringPotMin";
const String EEPROM_DRIVE_BY_WIRE_MAX = "steeringPotMax";
const String EEPROM_USE_PUSH_BUTTON_DRIVE = "usePushButtonDrive";

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

// TODO why does this have to be defined outside of the class?
ConfigurationEntry configurationEntries[] = {
  {EEPROM_VERSION, 0, "Integer", false, CURRENT_SETTINGS_VERSION, ""},
  {EEPROM_MAX_SPEED, 4, "Integer", false, 65, ""},
  {EEPROM_ACTUATOR_CENTER, 8, "Integer", false, 0, ""},  // in scaled units from -100 to 100
  {EEPROM_ACTUATOR_MIN, 12, "Integer", false, -50, ""},  // in scaled units from -100 to 100
  {EEPROM_ACTUATOR_MAX, 16, "Integer", false, 50, ""},   // in scaled units from -100 to 100
  {EEPROM_USE_JOYSTICK, 20, "Boolean", true, 0, ""},
  {EEPROM_INVERT_JOYSTICK_X, 24, "Boolean", true, 0, ""},
  {EEPROM_INVERT_JOYSTICK_Y, 28, "Boolean", false, 0, ""},
  {EEPROM_USE_RC, 32, "Boolean", false, 0, ""},
  {EEPROM_USE_DRIVE_BY_WIRE, 36, "Boolean", false, 0, ""},
  {EEPROM_DRIVE_BY_WIRE_CENTER, 40, "Integer", false, 512, ""},
  {EEPROM_DRIVE_BY_WIRE_MIN, 44, "Integer", false, 300, ""},
  {EEPROM_DRIVE_BY_WIRE_MAX, 48, "Integer", false, 700, ""},
  {EEPROM_USE_PUSH_BUTTON_DRIVE, 52, "Boolean", false, 0, ""}
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
    
    String getStatus() {
      String ret = String("[EEprom] ");
      ret.concat(String("Version:"));ret.concat(getIntegerSetting("version"));
      ret.concat(String(" Configuration "));ret.concat(loadingLogMessage);
      
      return ret;
    }
};

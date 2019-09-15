#include <ArduinoJson.h>
#include <EEPROM.h>

#define NUMBER_OF_CONFIGURATION_ENTRIES 13

/**
 * Eeprom Class
 * 
 * This class serves to interpret the dip switch setting to define the configuration for this car
 */

const int CURRENT_SETTINGS_VERSION = 1;

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
  {"version", 0, "Integer", false, CURRENT_SETTINGS_VERSION, ""},
  {"maxSpeed", 4, "Integer", false, 50, ""},
  {"actuatorCenter", 8, "Integer", false, 512, ""},
  {"actuatorMin", 12, "Integer", false, 200, ""},
  {"actuatorMax", 16, "Integer", false, 800, ""},
  {"useJoystick", 20, "Boolean", true, 0, ""},
  {"invertJoystickX", 24, "Boolean", false, 0, ""},
  {"invertJoystickY", 28, "Boolean", false, 0, ""},
  {"useRc", 32, "Boolean", false, 1, ""},
  {"usePotGo", 36, "Boolean", false, 0, ""},
  {"steeringPotCenter", 40, "Integer", false, 512, ""},
  {"steeringPotMin", 44, "Integer", false, 300, ""},
  {"steeringPotMax", 48, "Integer", false, 700, ""}
};
    
class Eeprom {
  private:
    const unsigned int EE_ADDRESS = 0;
    String loadingLogMessage = "loaded from Eeprom";
    
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
        loadingLogMessage = "loaded from defaults";
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
      ret.concat(String(" Loading Message:"));ret.concat(loadingLogMessage);
      
      return ret;
    }
};

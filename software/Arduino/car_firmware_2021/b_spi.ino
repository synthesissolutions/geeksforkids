#include <ArduinoJson.h>
#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>

using namespace Adafruit_LittleFS_Namespace;

/**
 * SPI Class
 * 
 * This class loads and saves configuration values from the nRF52840 onboard SPI Flash file system
 */

#define FILENAME    "/geeks.dat"

const int CURRENT_SETTINGS_VERSION = 3;

struct ConfigurationSettings {
  unsigned int version;
  int actuatorCenter;
  int actuatorMin;
  int actuatorMax;
  boolean useJoystick;
  boolean invertJoystickX;
  boolean invertJoystickY;
  boolean useRc;
};

/*
ConfigurationEntry configurationEntries[] = {
  {EEPROM_VERSION, 0, "Integer", false, CURRENT_SETTINGS_VERSION, ""},
  {EEPROM_MAX_SPEED, 4, "Integer", false, 65, ""},
  {EEPROM_ACTUATOR_CENTER, 8, "Integer", false, 0, ""},  // in scaled units from -100 to 100
  {EEPROM_ACTUATOR_MIN, 12, "Integer", false, -50, ""},  // in scaled units from -100 to 100
  {EEPROM_ACTUATOR_MAX, 16, "Integer", false, 50, ""},   // in scaled units from -100 to 100
  {EEPROM_USE_JOYSTICK, 20, "Boolean", true, 0, ""},
  {EEPROM_INVERT_JOYSTICK_X, 24, "Boolean", true, 0, ""},
  {EEPROM_INVERT_JOYSTICK_Y, 28, "Boolean", true, 0, ""},
  {EEPROM_USE_RC, 32, "Boolean", true, 0, ""},
  {EEPROM_USE_DRIVE_BY_WIRE, 36, "Boolean", false, 0, ""},
  {EEPROM_DRIVE_BY_WIRE_CENTER, 40, "Integer", false, 512, ""},
  {EEPROM_DRIVE_BY_WIRE_MIN, 44, "Integer", false, 300, ""},
  {EEPROM_DRIVE_BY_WIRE_MAX, 48, "Integer", false, 700, ""},
  {EEPROM_USE_PUSH_BUTTON_DRIVE, 52, "Boolean", false, 0, ""}
};
*/

class Spi {
  private:
    const unsigned int EE_ADDRESS = 0;
    String loadingLogMessage = "Loaded from SPI Flash memory";
    
    StaticJsonDocument<1024> currentSettingsJson;  

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    Spi() {  
    }

    ConfigurationSettings currentSettings;

    /*
     * init - load configuration values
     */
    void init() {
      if (loadFromSpiFlash() ||currentSettings.version != CURRENT_SETTINGS_VERSION) {
        setDefaultValues();
        if (saveToSpiFlash()) {
          loadingLogMessage = "Loaded from defaults";
        } else {
          loadingLogMessage = "Loaded from defaults - Saved Failed!";
        }
      }
    }

    void setDefaultValues() {
        currentSettings.version = CURRENT_SETTINGS_VERSION;
        currentSettings.actuatorCenter = 0;
        currentSettings.actuatorMin = -50;
        currentSettings.actuatorMax = 50;
        currentSettings.useJoystick = true;
        currentSettings.invertJoystickX = true;
        currentSettings.invertJoystickY = false;
        currentSettings.useRc = false;
    }

    bool loadFromSpiFlash() {
      return false;
    }

    bool saveToSpiFlash() {
      return false;
    }

/*
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
    */

     void getStatus(char * status) {
      sprintf(status, "[SPI Flash] Version: %i Configuration %s", currentSettings.version, loadingLogMessage);
    }
};

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

File file(InternalFS);

const int CURRENT_SETTINGS_VERSION = 5;

struct ConfigurationSettings {

  int actuatorMin;
  int actuatorCenter;
  int actuatorMax;
  boolean useRc;
  int rcSteeringMin;
  int rcSteeringCenter;
  int rcSteeringMax;
  int rcThrottleMin;
  int rcThrottleCenter;
  int rcThrottleMax;
  boolean invertJoystickX;
  boolean invertJoystickY;
  int joystickSteeringMin;
  int joystickSteeringCenter;
  int joystickSteeringMax;
  int joystickThrottleMin;
  int joystickThrottleCenter;
  int joystickThrottleMax;
};

class Spi {
  private:
    char *loadingLogMessage = "Loaded from SPI Flash memory";
    
    StaticJsonDocument<1024> currentSettingsJson;  

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    Spi() {  
    }

    ConfigurationSettings currentSettings;
    unsigned int version;
    
    /*
     * init - load configuration values
     */
    void init() {
       InternalFS.begin();

      if (!loadFromSpiFlash() || version != CURRENT_SETTINGS_VERSION) {
        setDefaultValues();
        if (saveToSpiFlash()) {
          loadingLogMessage = "Loaded from defaults";
        } else {
          loadingLogMessage = "Loaded from defaults - Saved Failed!";
        }
      } else {
        loadingLogMessage = "Loaded from settings file";
      }
    }

    void setDefaultValues() {
        version = CURRENT_SETTINGS_VERSION;
        
        currentSettings.actuatorMin = -50;
        currentSettings.actuatorCenter = 0;
        currentSettings.actuatorMax = 50;
        currentSettings.useRc = true;
        currentSettings.rcSteeringMin = 25;
        currentSettings.rcSteeringCenter = 512;
        currentSettings.rcSteeringMax = 1000;
        currentSettings.rcThrottleMin = 25;
        currentSettings.rcThrottleCenter = 512;
        currentSettings.rcThrottleMax = 1000;
        currentSettings.invertJoystickX = true;
        currentSettings.invertJoystickY = false;
        currentSettings.joystickSteeringMin = 25;
        currentSettings.joystickSteeringCenter = 512;
        currentSettings.joystickSteeringMax = 1000;
        currentSettings.joystickThrottleMin = 25;
        currentSettings.joystickThrottleCenter = 512;
        currentSettings.joystickThrottleMax = 1000;
    }

    bool loadFromSpiFlash() {
      // Initialize Internal File System
      version = 0;
      uint32_t readlen;

      if (file.open(FILENAME, FILE_O_READ)) {
        readlen = file.read((uint8_t *)&version, sizeof(unsigned int));

        if (version == CURRENT_SETTINGS_VERSION) {
          readlen = file.read((uint8_t *)&currentSettings, sizeof(struct ConfigurationSettings));
        }
      }

      file.close();
      
      return version == CURRENT_SETTINGS_VERSION;
    }

    bool saveToSpiFlash() {
      if( file.open(FILENAME, FILE_O_WRITE) )
      {
        Serial.println("OK");
        file.write((uint8_t *)&version, sizeof(unsigned int));
        file.write((uint8_t *)&currentSettings, sizeof(struct ConfigurationSettings));
        
        file.close();

        return true;
      }
  
      return false;
    }

     void getStatus(char * status) {
      sprintf(status, "[SPI Flash] Version: %i Configuration %s", version, loadingLogMessage);
    }
};

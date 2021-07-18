#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>

using namespace Adafruit_LittleFS_Namespace;

/**
 * SPI Class
 * 
 * This class loads and saves configuration values from the nRF52840 onboard SPI Flash file system
 */

#define FILENAME    "/geeksconfig.dat"

File file(InternalFS);

const int CURRENT_SETTINGS_VERSION = 1;

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

        currentSettings.actuatorMin = STEERING_MIN;
        currentSettings.actuatorCenter = STEERING_CENTER;
        currentSettings.actuatorMax = STEERING_MAX;
        currentSettings.useRc = false;
        currentSettings.rcSteeringMin = STEERING_RC_MIN;
        currentSettings.rcSteeringCenter = STEERING_RC_CENTER;
        currentSettings.rcSteeringMax = STEERING_RC_MAX;
        currentSettings.rcThrottleMin = THROTTLE_RC_MIN;
        currentSettings.rcThrottleCenter = THROTTLE_RC_CENTER;
        currentSettings.rcThrottleMax = THROTTLE_RC_MAX;
        currentSettings.invertJoystickX = false;
        currentSettings.invertJoystickY = false;
        currentSettings.joystickSteeringMin = JOYSTICK_X_AXIS_MIN;
        currentSettings.joystickSteeringCenter = JOYSTICK_X_AXIS_CENTER;
        currentSettings.joystickSteeringMax = JOYSTICK_X_AXIS_MAX;
        currentSettings.joystickThrottleMin = JOYSTICK_Y_AXIS_MIN;
        currentSettings.joystickThrottleCenter = JOYSTICK_Y_AXIS_CENTER;
        currentSettings.joystickThrottleMax = JOYSTICK_Y_AXIS_MAX;
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
      InternalFS.remove(FILENAME);

      Serial.println("Attempting to save changes to SPI Flash");
      if( file.open(FILENAME, FILE_O_WRITE) )
      {
        file.write((uint8_t *)&version, sizeof(unsigned int));
        file.write((uint8_t *)&currentSettings, sizeof(struct ConfigurationSettings));

        file.flush();
        file.close();

        Serial.println("Save OK");
        return true;
      }

      Serial.println("Save Failed");
      return false;
    }

     void getStatus(char * status) {
      sprintf(status, "[SPI Flash] Version: %i Configuration %s", version, loadingLogMessage);
    }
};

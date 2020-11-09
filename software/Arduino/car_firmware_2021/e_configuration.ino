/**
 * Configuration Class
 * 
 * This class serves to interpret the spi settings to define the configuration for this car
 */

class Configuration {
  private:
    Spi *spi;
    int maxSpeedPin;
    
  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    Configuration() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init(Spi *s, int sp) {
      spi = s;

      maxSpeedPin = sp;
      pinMode(maxSpeedPin, INPUT);

    }

    /*
     * getters ... translate dip switch settings into car configuration
     */
    int getConfigurationVersion() { return spi->version; }
    
    boolean getInvertJoystickX() { return spi->currentSettings.invertJoystickX; }
    boolean getInvertJoystickY() { return spi->currentSettings.invertJoystickY; }

    boolean useJoystick() { return spi->currentSettings.useJoystick; }
    boolean useRc() { return spi->currentSettings.useRc; }

    int readMaxSpeedPot() {
      return analogRead(maxSpeedPin);  
    }
    
    float getSpeedMultiplier() {
      return constrain(map(readMaxSpeedPot(), 0, 1023, SPEED_CONFIGURATION_MIN_SPEED, SPEED_CONFIGURATION_MAX_SPEED), SPEED_CONFIGURATION_MIN_SPEED, SPEED_CONFIGURATION_MAX_SPEED) / 100.0;
    }
    
    int getSteeringCenter() {
      int spiValue = spi->currentSettings.actuatorCenter;
      return spiValue;
    }
    
    int getSteeringMin() {
      int spiValue = spi->currentSettings.actuatorMin;
      return spiValue;
    }
    
    int getSteeringMax() {
      int spiValue = spi->currentSettings.actuatorMax;
      return spiValue;
    }

    void getStatus(char * status) {
      sprintf(status, "[Configuration] Version: %i  Invert Joystick X:%s Invert Joystick Y:%s Speed Multiplier:%f Speed Pot:%i Joystick:%s RC:%s Min/C/Max:%i %i %i", 
        getConfigurationVersion(),
        getInvertJoystickX() ? "true" : "false",
        getInvertJoystickY() ? "true" : "false",
        getSpeedMultiplier(),
        readMaxSpeedPot(),
        useJoystick() ? "true" : "false",
        useRc() ? "true" : "false",
        getSteeringMin(),
        getSteeringCenter(),
        getSteeringMax());
    }
};

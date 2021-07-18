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

    // Joystick
    boolean getInvertJoystickX() { return spi->currentSettings.invertJoystickX; }
    boolean getInvertJoystickY() { return spi->currentSettings.invertJoystickY; }
    int getJoystickSteeringMin() { return spi->currentSettings.joystickSteeringMin; }
    int getJoystickSteeringCenter() { return spi->currentSettings.joystickSteeringCenter; }
    int getJoystickSteeringMax() { return spi->currentSettings.joystickSteeringMax; }
    int getJoystickThrottleMin() { return spi->currentSettings.joystickThrottleMin; }
    int getJoystickThrottleCenter() { return spi->currentSettings.joystickThrottleCenter; }
    int getJoystickThrottleMax() { return spi->currentSettings.joystickThrottleMax; }

    // Parental Control
    boolean useRc() { return spi->currentSettings.useRc; }
    int getRcSteeringMin() { return spi->currentSettings.rcSteeringMin; }
    int getRcSteeringCenter() { return spi->currentSettings.rcSteeringCenter; }
    int getRcSteeringMax() { return spi->currentSettings.rcSteeringMax; }
    int getRcThrottleMin() { return spi->currentSettings.rcThrottleMin; }
    int getRcThrottleCenter() { return spi->currentSettings.rcThrottleCenter; }
    int getRcThrottleMax() { return spi->currentSettings.rcThrottleMax; }

    int readMaxSpeedPot() {
      return analogRead(maxSpeedPin);  
    }
    
    float getSpeedMultiplier() {
      return constrain(map(readMaxSpeedPot(), 0, 1023, SPEED_CONFIGURATION_MIN_SPEED, SPEED_CONFIGURATION_MAX_SPEED), SPEED_CONFIGURATION_MIN_SPEED, SPEED_CONFIGURATION_MAX_SPEED) / 100.0;
    }

    // Linear Actuator
    int getSteeringCenter() { return spi->currentSettings.actuatorCenter; }
    int getSteeringMin() { return spi->currentSettings.actuatorMin; }
    int getSteeringMax() { return spi->currentSettings.actuatorMax; }

    void getStatus(char * status) {
      sprintf(status, "[Configuration] Version: %i  Invert Joy X:%s Y:%s Joy Steering:%i %i %i  Speed Pot:%i RC:%s Min/C/Max:%i %i %i", 
        getConfigurationVersion(),
        getInvertJoystickX() ? "true" : "false",
        getInvertJoystickY() ? "true" : "false",
        getJoystickSteeringMin(),
        getJoystickSteeringCenter(),
        getJoystickSteeringMax(),
        readMaxSpeedPot(),
        useRc() ? "true" : "false",
        getSteeringMin(),
        getSteeringCenter(),
        getSteeringMax());
    }
};

/**
 * Configuration Class
 * 
 * This class serves to interpret the eeprom settings to define the configuration for this car
 */

class Configuration {
  private:
    Eeprom *eeprom;
    int maxSpeedPin;
    
  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    Configuration() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init(Eeprom *e, int s) {
      eeprom = e;

      maxSpeedPin = s;
      pinMode(maxSpeedPin, INPUT);

    }

    /*
     * getters ... translate dip switch settings into car configuration
     */
    int getConfigurationVersion() { return eeprom->getIntegerSetting(EEPROM_VERSION); }
    
    boolean getInvertJoystickX() { return eeprom->getBooleanSetting(EEPROM_INVERT_JOYSTICK_X); }
    boolean getInvertJoystickY() { return eeprom->getBooleanSetting(EEPROM_INVERT_JOYSTICK_Y); }

    boolean useJoystick() { return eeprom->getBooleanSetting(EEPROM_USE_JOYSTICK); }
    boolean useRc() { return eeprom->getBooleanSetting(EEPROM_USE_RC); }
    boolean useDriveByWireAndGoButton() { return eeprom->getBooleanSetting(EEPROM_USE_DRIVE_BY_WIRE); }
    boolean usePushButtonDrive() { return eeprom->getBooleanSetting(EEPROM_USE_PUSH_BUTTON_DRIVE); }

    int readMaxSpeedPot() {
      return analogRead(maxSpeedPin);  
    }
    
    float getSpeedMultiplier() {
      return constrain(map(readMaxSpeedPot(), 0, 1023, SPEED_CONFIGURATION_MIN_SPEED, SPEED_CONFIGURATION_MAX_SPEED), SPEED_CONFIGURATION_MIN_SPEED, SPEED_CONFIGURATION_MAX_SPEED) / 100.0;
    }
    
    int getSpeedMultiplierInt2() {
      int eepromValue = eeprom->getIntegerSetting(EEPROM_MAX_SPEED);
      return eepromValue;
    }
    
    int getSteeringCenter() {
      int eepromValue = eeprom->getIntegerSetting(EEPROM_ACTUATOR_CENTER);
      return eepromValue;
    }
    
    int getSteeringMin() {
      int eepromValue = eeprom->getIntegerSetting(EEPROM_ACTUATOR_MIN);
      return eepromValue;
    }
    
    int getSteeringMax() {
      int eepromValue = eeprom->getIntegerSetting(EEPROM_ACTUATOR_MAX);
      return eepromValue;
    }

    void getStatus(char * status) {
      sprintf(status, "[Configuration] Version: %i  Invert Joystick X:%s Invert Joystick Y:%s Speed Multiplier:%f Speed Pot:%i Joystick:%s PushButton:%s RC:%s DriveByWire:%s Min/C/Max:%i %i %i", 
        getConfigurationVersion(),
        getInvertJoystickX() ? "true" : "false",
        getInvertJoystickY() ? "true" : "false",
        getSpeedMultiplier(),
        readMaxSpeedPot(),
        useJoystick() ? "true" : "false",
        usePushButtonDrive() ? "true" : "false",
        useRc() ? "true" : "false",
        useDriveByWireAndGoButton() ? "true" : "false",
        getSteeringMin(),
        getSteeringCenter(),
        getSteeringMax());
    }
};

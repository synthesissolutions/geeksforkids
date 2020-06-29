/**
 * Configuration Class
 * 
 * This class serves to interpret the eeprom settings to define the configuration for this car
 */

class Configuration {
  private:
    Eeprom *eeprom;
    
  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    Configuration() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init(Eeprom *e) {
      eeprom = e;
    }

    /*
     * getters ... translate dip switch settings into car configuration
     */
    // TODO Use constants instead of the hard coded setting name strings
    int getConfigurationVersion() { return eeprom->getIntegerSetting(EEPROM_VERSION); }
    
    boolean getInvertJoystickX() { return eeprom->getBooleanSetting(EEPROM_INVERT_JOYSTICK_X); }
    boolean getInvertJoystickY() { return eeprom->getBooleanSetting(EEPROM_INVERT_JOYSTICK_Y); }

    boolean useJoystick() { return eeprom->getBooleanSetting(EEPROM_USE_JOYSTICK); }
    boolean useRc() { return eeprom->getBooleanSetting(EEPROM_USE_RC); }
    boolean useSteeringPotentiometerAndGoButton() { return eeprom->getBooleanSetting(EEPROM_USE_DRIVE_BY_WIRE); }
    boolean usePushButtonDrive() { return eeprom->getBooleanSetting(EEPROM_USE_PUSH_BUTTON_DRIVE); }
    
    float getSpeedMultiplier() {
      int eepromValue = eeprom->getIntegerSetting(EEPROM_MAX_SPEED);
      return eepromValue / 100.0;
    }
    
    int getSpeedMultiplierInt() {
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
      
    String getStatus() {
      String ret = String("[Configuration] ");
      ret.concat(String("Version: "));ret.concat(getConfigurationVersion());
      ret.concat(String(" Invert Joystick X:"));ret.concat(getInvertJoystickX());
      ret.concat(String(" Invert Joystick Y:"));ret.concat(getInvertJoystickY());
      ret.concat(String(" Speed Multiplier:"));ret.concat(getSpeedMultiplier());
      ret.concat(String(" "));ret.concat(getSpeedMultiplierInt());
      ret.concat(String(" Joystick:"));ret.concat(useJoystick());
      ret.concat(String(" PushButton:"));ret.concat(usePushButtonDrive());
      ret.concat(String(" RC:"));ret.concat(useRc());
      ret.concat(String(" DriveByWire:"));ret.concat(useSteeringPotentiometerAndGoButton());
      ret.concat(String(" Min/C/Max:"));ret.concat(getSteeringMin());ret.concat(" ");ret.concat(getSteeringCenter());ret.concat(" ");ret.concat(getSteeringMax());
      
      return ret;
    }
};

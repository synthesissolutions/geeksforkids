/**
 * Configuration Class
 * 
 * This class serves to interpret the dip switch setting to define the configuration for this car
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
    boolean getInvertJoystickX() {return eeprom->getBooleanSetting("invertJoystickX");}
    boolean getInvertJoystickY() {return eeprom->getBooleanSetting("invertJoystickY");}
    float getSpeedMultiplier() {
      int eepromValue = eeprom->getIntegerSetting("maxSpeed");
      return eepromValue / 100.0;
    }
    int getSpeedMultiplierInt() {
      int eepromValue = eeprom->getIntegerSetting("maxSpeed");
      return eepromValue;
    }
    boolean useSteeringPotentiometerAndGoButton() {
      return false;
    }
  
    String getStatus() {
      String ret = String("[Configuration] ");
      ret.concat(String("Invert Joystick X:"));ret.concat(getInvertJoystickX());
      ret.concat(String(" Invert Joystick Y:"));ret.concat(getInvertJoystickY());
      ret.concat(String(" Speed Multiplier:"));ret.concat(getSpeedMultiplier());
      ret.concat(String(" "));ret.concat(getSpeedMultiplierInt());
      ret.concat(String(" User Steering Pot and Go Button:"));ret.concat(useSteeringPotentiometerAndGoButton());
      
      return ret;
    }
};

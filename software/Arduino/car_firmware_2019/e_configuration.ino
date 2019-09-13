/**
 * Configuration Class
 * 
 * This class serves to interpret the dip switch setting to define the configuration for this car
 */

class Configuration {
  private:
    
  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    Configuration() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init() {
    }

    /*
     * getters ... translate dip switch settings into car configuration
     */
    boolean getInvertJoystickX() {return false;}
    boolean getInvertJoystickY() {return false;}
    float getSpeedMultiplier() {
      int index = 0; // read 2 bit integer (0-3) to use as an index into the speed multiplier array
      return THROTTLE_SPEED_MULTIPLIER[index];
    }
    boolean useSteeringPotentiometerAndGoButton() {
      return false;
    }
  
    String getStatus() {
      String ret = String("[Configuration] ");
      ret.concat(String("Invert Joystick X:"));ret.concat(getInvertJoystickX());
      ret.concat(String(" Invert Joystick Y:"));ret.concat(getInvertJoystickY());
      ret.concat(String(" Speed Multiplier:"));ret.concat(getSpeedMultiplier());
      ret.concat(String(" User Steering Pot and Go Button:"));ret.concat(useSteeringPotentiometerAndGoButton());
      
      return ret;
    }
};

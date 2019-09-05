/**
 * Configuration Class
 * 
 * This class serves to interpret the dip switch setting to define the configuration for this car
 */

class Configuration {
  private:

  DIPSwitches *dips;
    
  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    Configuration() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init(DIPSwitches *d) {
      dips = d;
    }

    /*
     * getters ... translate dip switch settings into car configuration
     */
    boolean getInvertJoystickX() {return !dips->getPin3();}
    boolean getInvertJoystickY() {return dips->getPin4();}
    float getSpeedMultiplier() {
      int index = dips->getPin1() * 2 + dips->getPin2(); // read 2 bit integer (0-3) to use as an index into the speed multiplier array
      return THROTTLE_SPEED_MULTIPLIER[index];
    }
    boolean useSteeringPotentiometerAndGoButton() {
      return dips->getPin5();
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


/**
 * DriveByWireAndGoButton class
 * 
 * This class encapulates all the pin read and various calculations for reading the steering potentiometer and go button.  
 *   Notably, it has a set of "scaled" getter methods that will return the value from the joystick in units from -100 to 100.  
 *   This should help with future iterations of the hardare, helping to abstract away the internals of reading 
 *   the values.
 */

class DriveByWireAndGoButton {
  private:
    boolean steeringSignalHigh;
    unsigned long steeringPulseStart;
    unsigned long steeringPWM;
    int steeringScaled = -1;
    
    unsigned int steeringMinPWM = STEERING_HALL_SENSOR_MIN;
    unsigned int steeringCenterPWM = STEERING_HALL_SENSOR_CENTER;
    unsigned int steeringMaxPWM = STEERING_HALL_SENSOR_MAX;
    
    int steeringSensorPin;
    int throttleButtonPin;
    int reversePin;

    int steeringDeadzoneLow = HALL_SENSOR_STEERING_DEADZONE_LOW;
    int steeringDeadzoneHigh = HALL_SENSOR_STEERING_DEADZONE_HIGH;

    unsigned long lastSignificantInputMillis = 0;
    boolean  invertSteering = HALL_SENSOR_INVERT_STEERING;
 
  public:
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).
    DriveByWireAndGoButton() {
    }

    /*
     * init - initialize the joystick instance with the pins for x and y axes and the reverse switch
     */
    void init(int steeringSensorPin, int throttleButtonPin, int reversePin) {
      this->steeringSensorPin = steeringSensorPin;
      this->throttleButtonPin = throttleButtonPin;
      this->reversePin = reversePin;
      
      pinMode(steeringSensorPin, INPUT_PULLUP);
      pinMode(throttleButtonPin, INPUT_PULLDOWN);
      pinMode(reversePin, INPUT);
    }
    
    /*
     * setXAxisDeadzone - in scaled units (-100 to 100)
     */
    void setSteeringDeadzone(int dzLow, int dzHigh) {
      this->steeringDeadzoneLow = dzLow;
      this->steeringDeadzoneHigh = dzHigh;
    }

    int getSteeringScaled() {
      return steeringScaled;
    }

    // raw value from the Y axis potentiometer
    int getYAxisRaw() {
      boolean val = !digitalRead(throttleButtonPin);

      // Logic is reversed, True indicates the button is not pushed and False that it is pushed
      if (val) 
        return 0;
      else 
        return 1;
    }
    
    /* gets the y axis scaled 
     *  
     *  Check to see if the Go button is pressed and then check the reverse switch
     */
    int getThrottleScaled() {
      int val = getYAxisRaw();

      if (val > 0) {
        if (isForward())
          return -100;
        else
          return 100;
      } else
        return 0;
    }

    /* Is the reverse switch thrown?
     *  
     */
    boolean isReverse() {
      return !digitalRead(reversePin);
    }


    /* Is the forward switch thrown?
     *  
     */
    boolean isForward() {
      return !isReverse();
    }

    /*
     * Is the steering pot and go button considered active. Currentyly, this is always true.
     *
     */
    boolean isActive() {

      // not sure if we need to worry about centering with these controls
      return true;
      
    }

        /* 
     * Handler for IRQ updates for steering.
     * 
     * NOTE: This code is considered critical (should not be interrupted), but does not disable interrupts.  This is because we assume it's being 
     *       called in an IRQ handler and therefore interrupts are already disabled until we exit.  We are doing the math to figure out the pulse width
     *       and the scaled signal here, which is based on the assumption that the board in use (e.g. teensy) is much faster in clock speed than the 
     *       resolution of the PWM signal.  
     */
    void steeringIRQHandler() {

      // which state are we handling
      if(digitalRead(steeringSensorPin) == 1){
        // rising signal
        if (!steeringSignalHigh) {

          // record when the pulse started
          steeringPulseStart = micros();

          // set us up to look for the pulse end
          steeringSignalHigh = true;
        }
        
      } else {

        // falling signal
        if (steeringSignalHigh) {
          // and we haven't seen this pulse drop previously

          // calculate the pulse width in microseconds
          steeringPWM = micros()-steeringPulseStart;

          // is the pulse width in the expected range?
          if ((steeringPWM > 0) && (steeringPWM < steeringMaxPWM)) {
            
            // we have a complete pulse ... calculate the signal
            // just a linear scaling of PWM min/max to -100 - 100
            if (steeringPWM >= steeringCenterPWM) {
              steeringScaled = constrain(map(steeringPWM, steeringCenterPWM, steeringMaxPWM, 0, 100), 0, 100);
            } else {
              steeringScaled = constrain(map(steeringPWM, steeringMinPWM, steeringCenterPWM, -100, 0), -100, 0);              
            }
            
            
            // invert if necessary
            if (invertSteering) {
              steeringScaled = -steeringScaled;
            }

            // are we in the deadzone?
            if (steeringScaled > steeringDeadzoneLow && steeringScaled < steeringDeadzoneHigh) {
              // yes ... apply the deadzone
              steeringScaled = 0;
            } else {
              // no... leave the value alone, but record that we had a significant input
              lastSignificantInputMillis = millis();
            }
            
          }
          steeringSignalHigh = false;
        }

      }
    }

    void getStatus(char * status) {
      sprintf(status, "[Steering Sensor and Go Button] x PWM:%lu xscaled:%i yscaled (Go Button):%i IsReverse:%s IsForward:%s Map:%li",
        steeringPWM,
        getSteeringScaled(),
        getThrottleScaled(),
        isReverse() ? "true" : "false",
        isForward() ? "true" : "false",
        map(steeringPWM, steeringCenterPWM, steeringMaxPWM, 0, 100));
        
//      String ret = String("[Steering Sensor and Go Button] ");
//      ret.concat(String("x PWM:"));ret.concat(steeringPWM);
//      ret.concat(String("xscaled:"));ret.concat(getSteeringScaled());
//      ret.concat(String(" yscaled (Go Button):"));ret.concat(getThrottleScaled());
//      ret.concat(String(" IsReverse:"));ret.concat(isReverse());
//      ret.concat(String(" IsForward:"));ret.concat(isForward());
//      ret.concat(String(" Map:"));ret.concat(map(steeringPWM, steeringCenterPWM, steeringMaxPWM, 0, 100));

//      return ret;
    }
};

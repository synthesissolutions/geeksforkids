
/**
 * SteeringPotGoButton class
 * 
 * This class encapulates all the pin read and various calculations for reading the steering potentiometer and go button.  
 *   Notably, it has a set of "scaled" getter methods that will return the value from the joystick in units from -100 to 100.  
 *   This should help with future iterations of the hardare, helping to abstract away the internals of reading 
 *   the values.
 */

class SteeringPotGoButton {
  private:
    int xAxisPin;
    int yAxisPin;
    int reversePin;

    // settting default values here ... being a little lazy by defaulting from constants.  

    // these are in raw pin read units (0 to 1024)
    int xAxisCenter = STEERING_POT_X_AXIS_CENTER;
    int xAxisMin = STEERING_POT_X_AXIS_MIN;
    int xAxisMax = STEERING_POT_X_AXIS_MAX;

    // these are in scaled units (-100 to 100)
    int xAxisDZLow = STEERING_POT_X_AXIS_DEADZONE_LOW;
    int xAxisDZHigh = STEERING_POT_X_AXIS_DEADZONE_HIGH;
 
  public:
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).
    SteeringPotGoButton() {
    }

    /*
     * init - initialize the joystick instance with the pins for x and y axes and the reverse switch
     */
    void init(int xAxisPin, int yAxisPin, int reversePin) {
      this->xAxisPin = xAxisPin;
      this->yAxisPin = yAxisPin;
      this->reversePin = reversePin;
      pinMode(xAxisPin, INPUT);
      pinMode(yAxisPin,INPUT_PULLUP);
      pinMode(reversePin,INPUT_PULLUP);
    }

    /*
     * setXAxisRange - sets the range for converting the xAxis to scaled units
     */
    void setXAxisRange(int minv, int centerv, int maxv) {     
      this->xAxisCenter = centerv;
      this->xAxisMin = minv;
      this->xAxisMax = maxv; 
    }
    
    /*
     * setXAxisDeadzone - in scaled units (-100 to 100)
     */
    void setXAxisDeadzone(int xAxisDZLow, int xAxisDZHigh) {
      this->xAxisDZLow = xAxisDZLow;
      this->xAxisDZHigh = xAxisDZHigh;
    }

    // raw value from the x axis potentiometer
    int getXAxisRaw() {
      int val = analogRead(xAxisPin);
      return val;
    }

    // raw value from the Y axis potentiometer
    int getYAxisRaw() {
      boolean val = digitalRead(yAxisPin);

      // Logic is reversed, True indicates the button is not pushed and False that it is pushed
      if (val) 
        return 0;
      else 
        return 1;
    }

    /* gets the x axis scaled 
     *  
     *  Algorithm is to simply do a linear scaling based on the range, and then apply the deadzone
     */
    int getXAxisScaled() {
      int val = getXAxisRaw();

      // constrain to be between min and max, and then scale to -100 to 100
      val = map(constrain(val,xAxisMin,xAxisMax),xAxisMin,xAxisMax,-100,100);

      // apply the deadzone
      if (xAxisDZLow < val && val<xAxisDZHigh) val=0;

      // TODO Need to set an invert variable and use it instead of hard coding the inverse here
      return -val;
    }

    /* gets the y axis scaled 
     *  
     *  Check to see if the Go button is pressed and then check the reverse switch
     */
    int getYAxisScaled() {
      int val = getYAxisRaw();

      if (val > 0) {
        if (isForward())
          return 100;
        else
          return -100;
      } else
        return 0;
    }

    /* Is the reverse switch thrown?
     *  
     */
    boolean isReverse() {
      return digitalRead(reversePin);
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

    String getStatus() {
      String ret = String("[Steering Pot and Go Button] ");
      ret.concat(String("x:"));ret.concat(getXAxisRaw());
      ret.concat(String(" xscaled:"));ret.concat(getXAxisScaled());
      ret.concat(String(" y (Go Button):"));ret.concat(getYAxisRaw());
      ret.concat(String(" yscaled:"));ret.concat(getYAxisScaled());
      ret.concat(String(" IsReverse:"));ret.concat(isReverse());
      ret.concat(String(" IsForward:"));ret.concat(isForward());

      return ret;
    }

 
};

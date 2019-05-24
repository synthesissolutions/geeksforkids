
/**
 * Joystick class
 * 
 * This class encapulates all the pin read and various calculations for reading the joystick.  Notably, it has a 
 *   set of "scaled" getter methods that will return the value from the joystick in units from -100 to 100.  This 
 *   should help with future iterations of the hardare, helping to abstract away the internals of reading 
 *   the joystick values.
 */

class Joystick {
  private:
    int xAxisPin;
    int yAxisPin; 

    // settting default values here ... being a little lazy by defaulting from constants.  

    // these are in raw pin read units (0 to 1024)
    int xAxisCenter = X_AXIS_CENTER;
    int xAxisMin = X_AXIS_MIN;
    int xAxisMax = X_AXIS_MAX;

    // these are in raw pin read units (0 to 1024)
    int yAxisCenter = Y_AXIS_CENTER;
    int yAxisMin = Y_AXIS_MIN;
    int yAxisMax = Y_AXIS_MAX;

    // these are in scaled units (-100 to 100)
    int xAxisDZLow = X_AXIS_DEADZONE_LOW;
    int xAxisDZHigh = X_AXIS_DEADZONE_HIGH;
    int yAxisDZLow = Y_AXIS_DEADZONE_LOW;
    int yAxisDZHigh = Y_AXIS_DEADZONE_HIGH;

    // direction inversion if necessary
    boolean invertXAxis = JOYSTICK_INVERT_X_AXIS;
    boolean invertYAxis = JOYSTICK_INVERT_Y_AXIS;

    boolean hasCentered=false;
 
  public:
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).
    Joystick() {
    }

    /*
     * init - initialize the joystick instance with the pins for x and y axes
     */
    void init(int xAxisPin, int yAxisPin) {
      this->xAxisPin = xAxisPin;
      this->yAxisPin = yAxisPin; 
      pinMode(xAxisPin, INPUT);
      pinMode(yAxisPin, INPUT);
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
     * setXAxisRange - sets the range for converting the xAxis to scaled units
     */
    void setYAxisRange(int minv, int centerv, int maxv) {     
      this->yAxisCenter = centerv;
      this->yAxisMin = minv;
      this->yAxisMax = maxv; 
    }

    /*
     * setXAxisDeadzone - in scaled units (-100 to 100)
     */
    void setXAxisDeadzone(int xAxisDZLow, int xAxisDZHigh) {
      this->xAxisDZLow = xAxisDZLow;
      this->xAxisDZHigh = xAxisDZHigh;
    }

    /*
     * setYAxisDeadzone - in scaled units (-100 to 100)
     */
    void setYAxisDeadzone(int yAxisDZLow, int yAxisDZHigh) {
      this->yAxisDZLow = yAxisDZLow;
      this->yAxisDZHigh = yAxisDZHigh;
    }

    // raw value from the x axis potentiometer
    int getXAxisRaw() {
      int val = analogRead(xAxisPin);
      return val;
    }

    // raw value from the Y axis potentiometer
    int getYAxisRaw() {
      int val = analogRead(yAxisPin);
      return val;
    }

    /* gets the x axis scaled 
     *  
     *  Algorithm is to simply do a linear scaling based on the range, and then apply the deadzone
     */
    int getXAxisScaled() {
      int val = getXAxisRaw();

      // constrain to be between min and max, and then scale to -100 to 100
      val = map(constrain(val,xAxisMin,xAxisMax),xAxisMin,xAxisMax,-100,100);

      // invert if necessary
      if (invertXAxis) {
        val = -val;
      }

      // apply the deadzone
      if (xAxisDZLow < val && val<xAxisDZHigh) val=0;
      
      return val;
    }

    /* gets the y axis scaled 
     *  
     *  Algorithm is to simply do a linear scaling based on the range, and then apply the deadzone
     */
    int getYAxisScaled() {
      int val = getYAxisRaw();

      // constrain to be between min and max, and then scale to -100 to 100
      val = map(constrain(val,yAxisMin,yAxisMax),yAxisMin,yAxisMax,-100,100);

      // invert if necessary
      if (invertYAxis) {
        val = -val;
      }
      
      // apply the deadzone
      if (yAxisDZLow < val && val<yAxisDZHigh) val=0;
      
      return val;
    }

    /*
     * Is the joystick considered active.  To be active, we must have seen it have a scaled value of 0 at least once on both axes.
     *  This helps ensure that the car doesn't start moving immediately when turned on if the joystick isn't centered. 
     *
     */
    boolean isActive() {

      /*
       * If we've not yet centered the controls, then we're not active yet
       */
      if (!hasCentered) {
        if (getXAxisScaled()==0 && getYAxisScaled()==0) {
                  
          // controls are centered, OK to go on
          hasCentered=true;
          
        } else {

          // controls have not yet centered, we're not active!
          return false;
          
        }
        
      }

      // we got here because we've seen both axes center... so we're OK to be active!
      return true;
      
    }

    String getStatus() {
      String ret = String("[Joystick] ");
      ret.concat(String("x:"));ret.concat(getXAxisRaw());
      ret.concat(String(" xscaled:"));ret.concat(getXAxisScaled());if (invertXAxis) ret.concat("(inverted)");
      ret.concat(String(" y:"));ret.concat(getYAxisRaw());
      ret.concat(String(" yscaled:"));ret.concat(getYAxisScaled());if (invertYAxis) ret.concat("(inverted)");
      ret.concat(String(" isActive:"));ret.concat(isActive());
      return ret;
    }

 
};

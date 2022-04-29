
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
    int xAxisCenter = JOYSTICK_X_AXIS_CENTER;
    int xAxisMin = JOYSTICK_X_AXIS_MIN;
    int xAxisMax = JOYSTICK_X_AXIS_MAX;

    // these are in raw pin read units (0 to 1024)
    int yAxisCenter = JOYSTICK_Y_AXIS_CENTER;
    int yAxisMin = JOYSTICK_Y_AXIS_MIN;
    int yAxisMax = JOYSTICK_Y_AXIS_MAX;

    // these are in scaled units (-100 to 100)
    int xAxisDZLow = JOYSTICK_X_AXIS_DEADZONE_LOW;
    int xAxisDZHigh = JOYSTICK_X_AXIS_DEADZONE_HIGH;
    int yAxisDZLow = JOYSTICK_Y_AXIS_DEADZONE_LOW;
    int yAxisDZHigh = JOYSTICK_Y_AXIS_DEADZONE_HIGH;

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
     * setYAxisRange - sets the range for converting the yAxis to scaled units
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
    double getXAxisRaw() {
      int newX = analogRead(xAxisPin);

      return newX;
    }

    // raw value from the Y axis potentiometer
    double getYAxisRaw() {
      int newY = analogRead(yAxisPin);
      
      return newY;
    }

    // return True/False is the X Axis Inverted
    boolean getInvertXAxis() {
      return invertXAxis;
    }

    // return True/False is the Y Axis Inverted
    boolean getInvertYAxis() {
      return invertYAxis;
    }

    // Set the X Axis inversion to True or False
    void setInvertXAxis(boolean val) {
      invertXAxis = val;
    }

    // Set the Y Axis inversion to True or False
    void setInvertYAxis(boolean val) {
      invertYAxis = val;
    }
    
    int getLeftScaled() {
      // Convert X and Y raw values to scaled values from -1 to 1.
      // and swap Y value to match normal graphing with +Y being up and -Y being down
      double center = xAxisCenter;
      double x = (getXAxisRaw() - center) / center;
      double y = -(getYAxisRaw() - center) / center;

      double magnitude = sqrt(x*x + y*y) * 100.0;
      x = x * 100.0;
      y = y * 100.0;

      int leftScaled = 0;

      // apply the deadzone
      if (xAxisDZLow < -magnitude && magnitude < xAxisDZHigh) {
        return 0;
      }
      
      if (x >= 0 && y >= 0) {
        // 1st quadrant
        leftScaled = magnitude;
      } else if (x >= 0 and y < 0) {
        // 2nd quadrant
        if (x == 0) {
          leftScaled = -magnitude; // driving backwards
        } else if (y == 0) {
          leftScaled = magnitude;  // spinning to the right
        } else {
          // somewhere in between
          if (abs(x) == abs(y)) {
            leftScaled = 0; // dead wheel turn on diaganol
          } else if (abs(x) > abs(y)) {
            // left is positive
            leftScaled = (1.0 - (abs(y) / abs(x))) * 100.0;
          } else {
            // left is negative
            leftScaled = (1.0 - (abs(x) / abs(y))) * -100.0;
          }
        }
      } else if (x <= 0 and y <= 0) {
        // 3rd quadrant
        leftScaled = -magnitude;
      } else {
        // 4th quadrant
        if (x == 0) {
          leftScaled = magnitude; // driving forward
        } else if (y == 0) {
          leftScaled = -magnitude;  // spinning to the left
        } else {
          // somewhere in between
          if (abs(x) == abs(y)) {
            leftScaled = 0;   // dead wheel turn on diaganol
          } else if (abs(x) > abs(y)) {
            // left is negative
            leftScaled = (1.0 - (abs(y) / abs(x))) * -100.0;
          } else {
            // left is positive
            leftScaled = (1.0 - (abs(x) / abs(y))) * 100;
          }
        }
      }

      // invert if necessary
      // treat the invertXAxis as invertLeft
      //if (invertXAxis) {
        //leftScaled = -leftScaled;
      //}

      return leftScaled;
    }

    /* gets the y axis scaled 
     *  
     *  Algorithm is to simply do a linear scaling based on the range, and then apply the deadzone  
     */
    int getRightScaled() {
      // Convert X and Y raw values to scaled values from -1 to 1.
      // and swap Y value to match normal graphing with +Y being up and -Y being down
      double center = xAxisCenter;
      double x = (getXAxisRaw() - center) / center;
      double y = -(getYAxisRaw() - center) / center;

      double magnitude = sqrt(x*x + y*y) * 100.0;
      x = x * 100.0;
      y = y * 100.0;

      int rightScaled = 0;

      // apply the deadzone
      if (yAxisDZLow < -magnitude && magnitude < yAxisDZHigh) {
        return 0;
      }
      
      if (x >= 0 && y >= 0) {
        // 1st quadrant
        if (x == 0) {
          rightScaled = magnitude; // driving forward
        } else if (y == 0) {
          rightScaled = -magnitude;  // spinning to the right
        } else {
          // somewhere in between
          if (abs(x) == abs(y)) {
            rightScaled = 0;    // dead wheel turn on diaganol
          } else if (abs(x) > abs(y)) {
            // right is negative
            rightScaled = (1.0 - (abs(y) / abs(x))) * -100.0;
          } else {
            // right is positive
            rightScaled = (1.0 - (abs(x) / abs(y))) * 100.0;
          }
        }
      } else if (x >= 0 and y < 0) {
        // 2nd quadrant
        rightScaled = -magnitude;
      } else if (x <= 0 and y <= 0) {
        // 3rd quadrant
        if (x == 0) {
          rightScaled = -magnitude; // driving backward
        } else if (y == 0) {
          rightScaled = magnitude;  // spinning to the left
        } else {
          // somewhere in between
          if (abs(x) == abs(y)) {
            rightScaled = 0;    // dead wheel turn on diaganol
          } else if (abs(x) > abs(y)) {
            // right is positive
            rightScaled = (1.0 - (abs(y) / abs(x))) * 100.0;
          } else {
            // right is negative
            rightScaled = (1.0 - (abs(x) / abs(y))) * -100.0;
          }
        }
      } else {
        // 4th quadrant
        rightScaled = magnitude;
      }

      // invert if necessary
      // treat the invertYAxis as invertRight
      //if (invertYAxis) {
        //rightScaled = -rightScaled;
      //}

      return rightScaled;
    }

    /*
     * Is the joystick considered active.  To be active, we must have seen it have a scaled value of 0 at least once on both axes.
     *  This helps ensure that the car doesn't start moving immediately when turned on if the joystick isn't centered. 
     *
     */
    boolean isActive() {
       if (1==1) return true;

      /*
       * If we've not yet centered the controls, then we're not active yet
       */
      if (!hasCentered) {
        if (getLeftScaled()==0 && getRightScaled()==0) {
                  
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

    void getStatus(char * status) {
      sprintf(status, "[Joystick] x:%f Left Scaled:%i %s y:%f Right Scaled:%i %s isActive:%s", 
          getXAxisRaw(),
          getLeftScaled(),
          invertXAxis ? "(inverted)" : "",
          getYAxisRaw(),
          getRightScaled(),
          invertYAxis ? "(inverted)" : "",
          isActive() ? "true" : "false");
    }
};

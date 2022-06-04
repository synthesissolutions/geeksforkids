
/**
 * Joystick class
 * 
 * This class encapulates all the pin read and various calculations for reading the joystick.  Notably, it has a 
 *   set of "scaled" getter methods that will return the value from the joystick in units from -100 to 100.  This 
 *   should help with future iterations of the hardare, helping to abstract away the internals of reading 
 *   the joystick values.
 */

#define JOY_X_READINGS 15
#define JOY_Y_READINGS 15


class Joystick {
  private:
    int xAxisPin;
    int yAxisPin;

    boolean useSteeringPwm = false;
    boolean useThrottlePwm = false;

    // Variables to handle extending the throttle time
    // When true, this allows a child to push go button briefly and have 
    // the car travel longer than the time the button was pushed.
    bool extendThrottle = false;
    int extendThrottleSpeedScaled = 0;
    int extendThrottleTimeMilliseconds = 500;
    long lastThrottleOnMillis = 0;
    
    // variables to track the PWM signals
    unsigned long steeringPulseStart; // the timestamp in ms for the current PWM steering pulse
    unsigned long steeringPwm = 0;    // the length of the last full PWM steering pulse in microseconds
    boolean steeringSignalHigh = false; // flag indicating that the start of a PWM signal (rising edge) has occured
    unsigned long throttlePulseStart; // the timestamp in ms for the current PWM throttle pulse
    unsigned long throttlePwm = 0;    // the length of the last full PWM throttle pulse in microseconds
    boolean throttleSignalHigh = false; // flag indicating that the start of a PWM signal (rising edge) has occured

    // settting default values here

    // these are in raw pin read units (0 to 1024) for analog and ?? for PWM
    int xAxisCenter = JOYSTICK_X_AXIS_CENTER;
    int xAxisMin = JOYSTICK_X_AXIS_MIN;
    int xAxisMax = JOYSTICK_X_AXIS_MAX;

    // these are in raw pin read units (0 to 1024) for analog and ?? for PWM
    int yAxisCenter = JOYSTICK_Y_AXIS_CENTER;
    int yAxisMin = JOYSTICK_Y_AXIS_MIN;
    int yAxisMax = JOYSTICK_Y_AXIS_MAX;

    // direction inversion if necessary
    boolean invertXAxis = JOYSTICK_INVERT_X_AXIS;
    boolean invertYAxis = JOYSTICK_INVERT_Y_AXIS;

    int joyXReadings[JOY_X_READINGS];
    int joyXIndex = 0;

    int joyYReadings[JOY_Y_READINGS];
    int joyYIndex = 0;

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

    void setUseSteeringPwm(boolean setting) {
      useSteeringPwm = setting;
    }

    void setUseThrottlePwm(boolean setting) {
      useThrottlePwm = setting;
    }

    void setExtendThrottle(boolean value) {
      extendThrottle = value;
    }

    void setExtendThrottleTimeMilliseconds(int value) {
      extendThrottleTimeMilliseconds = value;
    }
    
    // raw value from the x axis potentiometer
    int getXAxisRaw() {
      int newX;
      if (useSteeringPwm) {
        newX = steeringPwm;
      } else {
        newX = analogRead(xAxisPin);
      }

      joyXIndex++;
      if (joyXIndex >= JOY_X_READINGS) {
        joyXIndex = 0;
      }

      joyXReadings[joyXIndex] = newX;
      
      int total = 0;

      for (int i = 0; i < JOY_X_READINGS; i++) {
        total += joyXReadings[i];
      }
      
      return total / JOY_X_READINGS;
    }

    // raw value from the Y axis potentiometer
    int getYAxisRaw() {
      int newY;
      if (useThrottlePwm) {
        newY = throttlePwm;
      } else {
        newY = analogRead(yAxisPin);
      }

      joyYIndex++;
      if (joyYIndex >= JOY_Y_READINGS) {
        joyYIndex = 0;
      }

      joyYReadings[joyYIndex] = newY;
      
      int total = 0;

      for (int i = 0; i < JOY_Y_READINGS; i++) {
        total += joyYReadings[i];
      }
      
      return total / JOY_Y_READINGS;
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
    
    /* gets the x axis scaled 
     *  
     *  Algorithm is to simply do a linear scaling based on the range, and then apply the deadzone
     */
    int getXAxisScaled() {
      int val = getXAxisRaw();

      // The center value may not be half way between min and max
      // so calculate above and below center individually
      if (val < xAxisCenter) {
        val = map(constrain(val, xAxisMin, xAxisCenter), xAxisMin, xAxisCenter, -100, 0);
      } else if (val > xAxisCenter) {
        val = map(constrain(val, xAxisCenter, xAxisMax), xAxisCenter, xAxisMax, 0, 100);
      } else {
        val = 0;
      }
      
      // invert if necessary
      if (invertXAxis) {
        val = -val;
      }

      // apply the deadzone
      if (JOYSTICK_X_AXIS_DEADZONE_LOW < val && val < JOYSTICK_X_AXIS_DEADZONE_HIGH) {
        val = 0;
      }
      
      return val;
    }

    /* gets the y axis scaled 
     *  
     *  Algorithm is to simply do a linear scaling based on the range, and then apply the deadzone  
     */
    int getYAxisScaled() {
      int val = getYAxisRaw();

      // The center value may not be half way between min and max
      // so calculate above and below center individually
      if (val < yAxisCenter) {
        val = map(constrain(val, yAxisMin, yAxisCenter), yAxisMin, yAxisCenter, -100, 0);
      } else if (val > yAxisCenter) {
        val = map(constrain(val, yAxisCenter, yAxisMax), yAxisCenter, yAxisMax, 0, 100);
      } else {
        val = 0;
      }

      // invert if necessary
      if (invertYAxis) {
        val = -val;
      }
      
      // apply the deadzone
      if (JOYSTICK_Y_AXIS_DEADZONE_LOW < val && val < JOYSTICK_Y_AXIS_DEADZONE_HIGH) {
        val = 0;
      }

      // If we are extending the throttle, keep track of the last time and speed the throttle was not 0
      // if the throttle is 0, then override the val until the throttle extend time has expired
      if (extendThrottle && val != 0) {
        if (val > 0) {
          extendThrottleSpeedScaled = -66;
        } else {
          extendThrottleSpeedScaled = 66;
        }
        extendThrottleSpeedScaled = 100; // this is really only valid for digital controls like control panel but good enough for now
        lastThrottleOnMillis = millis();
      } else if (extendThrottle && (millis() > 5000) && (millis() - lastThrottleOnMillis < extendThrottleTimeMilliseconds)) {
        val = extendThrottleSpeedScaled;
      }
      
      return val;
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

    /* 
     * Handler for IRQ updates for steering.
     * 
     * NOTE: This code is considered critical (should not be interrupted), but does not disable interrupts.  This is because we assume it's being 
     *       called in an IRQ handler and therefore interrupts are already disabled until we exit.  We are doing the math to figure out the pulse width
     *       and the scaled signal here, which is based on the assumption that the board in use (e.g. teensy) is much faster in clock speed than the 
     *       resolution of the PWM signal.  
     */
    void steeringIRQHandler() {
      if(digitalRead(xAxisPin) == 1){
        if (!steeringSignalHigh) {
          // rising edge of the PWM signal
          // record when the pulse started
          steeringPulseStart = micros();
          steeringSignalHigh = true;
        }
        
      } else if (steeringSignalHigh) {
        // falling edge of the PWM signal
        // record the duty cycle in microseconds
        steeringPwm = micros() - steeringPulseStart;

        // reset for the next pulse
        steeringSignalHigh = false;
      }
      
    }
   
    /* 
     * Handler for IRQ updates for throttle.
     * 
     * NOTE: This code is considered critical (should not be interrupted), but does not disable interrupts.  This is because we assume it's being 
     *       called in an IRQ handler and therefore interrupts are already disabled until we exit.  We are doing the math to figure out the pulse width
     *       and the scaled signal here, which is based on the assumption that the board in use (e.g. teensy) is much faster in clock speed than the 
     *       resolution of the PWM signal.  
     */
    void throttleIRQHandler() {
      if(digitalRead(yAxisPin) == 1){
        if (!throttleSignalHigh) {
          // rising edge of the PWM signal
          // record when the pulse started
          throttlePulseStart = micros();
          throttleSignalHigh = true;
        }
      } else if (throttleSignalHigh) {
        // falling edge of the PWM signal
        // record the duty cycle in microseconds
        throttlePwm = micros() - throttlePulseStart;

        // reset for the next pulse
        throttleSignalHigh = false;
      }
    }
    
    void getStatus(char * status) {
      sprintf(status, "[Joystick] x:%i xscaled:%i%s y:%i yscaled:%i%s isActive:%s Extend Throttle: %s %i %i %i", 
          getXAxisRaw(),
          getXAxisScaled(),
          invertXAxis ? "(inverted)" : "",
          getYAxisRaw(),
          getYAxisScaled(),
          invertYAxis ? "(inverted)" : "",
          isActive() ? "true" : "false",
          extendThrottle ? "true" : "false",
          extendThrottleTimeMilliseconds,
          millis() - lastThrottleOnMillis,
          extendThrottleSpeedScaled);
    }
};

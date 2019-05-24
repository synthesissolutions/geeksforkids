/**
 * Steering class
 * 
 * This class serves to be the actual interface to driving the steering for the car.  The intent of this class is to 
 *   allow for a steering position to be set in scaled units (-100 to 100), and this class will take care of making the 
 *   changes to the steering as appropriate.
 */

class Steering {
  private:

    int pinSteeringLeft;
    int pinSteeringRight;
    int pinSteeringEnable;
    int pinSteeringPosition;

    int steeringTargetScaled = 0;          // scaled units (-100 to 100)
    int steeringPositionScaled = 0;        // scaled units (-100 to 100)
    int targetDeltaScaled = 0;             // scaled units (-100 to 100)

    boolean isMoving = false;
    
    // settting default values here ... being a little lazy by defaulting from constants.  
    int steeringMin = STEERING_MIN;                     // encoder units (0 to 1023)
    int steeringMax = STEERING_MAX;                     // encoder units (0 to 1023)
    int steeringCenter = STEERING_CENTER;               // encoder units (0 to 1023)
    int steeringStopDelta = STEERING_STOP_DELTA;        // scaled units (-100 to 100)
    int steeringStartDelta = STEERING_START_DELTA;      // scaled units (-100 to 100)
    int steeringSpeed = STEERING_SPEED;                 // PWM (0 to 255)

    /*
     * run the motor ... direction is based on the current position and the target
     */
    void runMotor() {
      // How we set the pins is based on the direction we need to go
      if (steeringPositionScaled < steeringTargetScaled) {
        // turn left
        digitalWrite(pinSteeringLeft, HIGH);
        digitalWrite(pinSteeringRight, LOW);  
      } else {
        // turn right
        digitalWrite(pinSteeringLeft, LOW);
        digitalWrite(pinSteeringRight, HIGH);  
      }

      // make sure the motor power is on
      analogWrite(pinSteeringEnable, steeringSpeed);

      // and make note that we're moving
      isMoving = true;
    }

    /*
     * stop the motor
     */
    void stopMotor() {
        isMoving = false;
        digitalWrite(pinSteeringLeft, LOW);
        digitalWrite(pinSteeringRight, LOW);  
        analogWrite(pinSteeringEnable, 0); 

        // and make note that we're not moving
        isMoving = false;
    }

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).
    Steering() {
    }

    // initial setup
    void init(int pinLeft, int pinRight, int pinEnable, int pinPosition) {
      // set the pins
      pinSteeringLeft = pinLeft;
      pinSteeringRight = pinRight;
      pinSteeringEnable = pinEnable;
      pinSteeringPosition = pinPosition;

      // set the pins to be output and set the speed
      pinMode(pinSteeringLeft, OUTPUT);
      pinMode(pinSteeringRight, OUTPUT);
      pinMode(pinSteeringEnable, OUTPUT);
      analogWrite(pinSteeringEnable, steeringSpeed);
    }

    int getSteeringPosition() {
      return steeringTargetScaled;
    }

    /*
     * Sets the new target for the steering position.  Expects the new target to be in scaled units: -100 to 100, 0=center. 
     */
    void setSteeringPosition(int target, boolean invert) {
      // constrain and set the steering target (in scaled units)
      target = constrain(target,-100,100);

      // should the steering be inverted?
      if (invert) {
        target = map(target,-100,100,100,-100);  
      }
      
      steeringTargetScaled = target;

      // now call update
      updateSteering();
      
    }

    /*
     * Update the steering ... this is the actual method that handles moving of the servo
     * 
     * NOTE ... it is very important that this method get called frequently.  Calling setSteeringPosition() every time through the loop
     *   is probably enough.  But... if you're not calling that very frequently, then this MUST be called in your main loop so that the 
     *   steering servo is monitored properly.
     *   
     * NOTE #2 ... this could probably be handled automagically with an IntervalTimer.  Seems like a good research project for someone.  ;-)
     * 
     */
    void updateSteering() {
      // figure out the current steering servo position and how far we are from the target
      //steeringPositionScaled = float(analogRead(pinSteeringPosition))*100./1023.;              // We're always going to work in scaled units
      steeringPositionScaled = constrain(map(analogRead(pinSteeringPosition),0,1023,-100,100),-100,100);              // We're always going to work in scaled units
      targetDeltaScaled = abs(steeringPositionScaled - steeringTargetScaled);

      // Are we moving already?
      if (isMoving) {
        
        // we are moving already ... should we stop?
        if (targetDeltaScaled <= steeringStopDelta) {
           // yes we should
           stopMotor();  
        } else {
          // nope ... gotta keep turning
          runMotor();
        }
 
      } else {

        // we're not moving ... should we start?
        if (targetDeltaScaled >= steeringStopDelta) {
           // yes we should
           runMotor();  
        } else {
          // nope ... let's make sure the motor is stopped
          stopMotor();
        }
        
      }
    }

    String getStatus() {
      String ret = String("[Steering] ");
      ret.concat(String("current:"));ret.concat(steeringPositionScaled);
      ret.concat(String(" target:"));ret.concat(steeringTargetScaled);
      ret.concat(String(" isMoving:"));ret.concat(isMoving);
      return ret;
    }
 
  
};

/**
 * Steering class
 * 
 * This class serves to be the actual interface to driving the steering for the car.  The intent of this class is to 
 *   allow for a steering position to be set in scaled units (-100 to 100), and this class will take care of making the 
 *   changes to the steering as appropriate.
 */

class Steering {
  private:

    int directionPin;
    int speedPwmPin;
    int currentPositionPin;

    int steeringTargetScaled = 0;          // scaled units (-100 to 100)
    int steeringPositionScaled = 0;        // scaled units (-100 to 100)
    int targetDeltaScaled = 0;             // scaled units (-100 to 100)

    boolean isMoving = false;
    
    // settting default values here ... being a little lazy by defaulting from constants.  
    int steeringMinScaled = -100;
    int steeringMaxScaled = 100;
    int steeringCenterScaled = 0;

    /*
     * run the motor ... direction is based on the current position and the target
     */
    void runMotor() {
      // How we set the pins is based on the direction we need to go
      if (steeringPositionScaled < steeringTargetScaled) {
        // turn left
        digitalWrite(directionPin, HIGH);
      } else {
        // turn right
        digitalWrite(directionPin, LOW);
      }

      // make sure the motor power is on
      analogWrite(speedPwmPin, STEERING_SPEED);

      // and make note that we're moving
      isMoving = true;
    }

    /*
     * stop the motor
     */
    void stopMotor() {
        isMoving = false;
        digitalWrite(directionPin, HIGH);
        analogWrite(speedPwmPin, 0); 

        // and make note that we're not moving
        isMoving = false;
    }

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).
    Steering() {
    }

    // initial setup
    void init(int pinDir, int pinPwm, int pinPosition) {
      // set the pins
      directionPin = pinDir;
      speedPwmPin = pinPwm;
      currentPositionPin = pinPosition;

      // set the pins to be output and set the speed
      pinMode(directionPin, OUTPUT);
      pinMode(speedPwmPin, OUTPUT);

      analogWrite(speedPwmPin, 0);
    }

    int getSteeringPosition() {
      return steeringTargetScaled;
    }

    /*
     * Sets the new target for the steering position.  Expects the new target to be in scaled units: -100 to 100, 0=center. 
     */
    void setSteeringPosition(int target) {
      // constrain and set the steering target (in scaled units)
      steeringTargetScaled = constrain(map(target, -100, 100, steeringMinScaled, steeringMaxScaled), steeringMinScaled, steeringMaxScaled);

      updateSteering();      
    }

    void setSteeringCenterScaled(int newCenter) {
      steeringCenterScaled = newCenter;
    }

    void setSteeringMinScaled(int newMin) {
      steeringMinScaled = newMin;
    }

    void setSteeringMaxScaled(int newMax) {
      steeringMaxScaled = newMax;
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
      // Convert analog read value to scaled units
      steeringPositionScaled = map(analogRead(currentPositionPin), 0, 1023, -100, 100);

      // Use steeringPositionScaled + steeringCenterScaled to account for configuration setting
      // add instead of subtract because configuration use > 0 for adjustments to the right but the actuator has > vaues to the left
      steeringPositionScaled = constrain(steeringPositionScaled + steeringCenterScaled, steeringMinScaled, steeringMaxScaled);

      targetDeltaScaled = abs(steeringPositionScaled - steeringTargetScaled);

      // Are we moving already?
      if (isMoving) {
        
        // we are moving already ... should we stop?
        if (targetDeltaScaled <= STEERING_STOP_DELTA) {
           // yes we should
           stopMotor();  
        } else {
          // nope ... gotta keep turning
          runMotor();
        }
 
      } else {

        // we're not moving ... should we start?
        if (targetDeltaScaled >= STEERING_STOP_DELTA) {
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
      ret.concat(String(" Actuator Position Raw:"));ret.concat(analogRead(currentPositionPin));
      return ret;
    }
 
  
};

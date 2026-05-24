/**
 * Steering class
 * 
 * This class serves to be the actual interface to driving the steering for the car.  The intent of this class is to 
 *   allow for a steering position to be set in scaled units (-100 to 100), and this class will take care of making the 
 *   changes to the steering as appropriate.
 */

#define CURRENT_POSITION_READINGS 5

class Steering {
  private:

    int forwardPin;
    int reversePin;
    int currentPositionPin;

    int steeringTargetScaled = 0;          // scaled units (-100 to 100)
    int steeringPositionScaled = 0;        // scaled units (-100 to 100)
    int targetDeltaScaled = 0;             // scaled units (-100 to 100)

    int currentPositions[CURRENT_POSITION_READINGS];
    int currentPositionIndex = 0;
    
    boolean isMoving = false;
    
    // settting default values here ... being a little lazy by defaulting from constants.  
    int steeringMinScaled = -100;
    int steeringMaxScaled = 100;
    int steeringCenterScaled = 0;
    int steeringStopDeltaScaled = STEERING_STOP_DELTA;

    /*
     * run the motor ... direction is based on the current position and the target
     */
    void runMotor() {    
      // How we set the pins is based on the direction we need to go
      if (steeringPositionScaled < steeringTargetScaled) {
        // turn left
        digitalWrite(forwardPin, LOW);
        analogWrite(reversePin, STEERING_SPEED);
      } else {
        // turn right
        analogWrite(forwardPin, STEERING_SPEED);
        digitalWrite(reversePin, LOW);
      }

      // note that we're moving
      isMoving = true;
    }

    /*
     * stop the motor
     */
    void stopMotor() {
        // TODO need to decide on coast vs. brake, probably doesn't matter for linear actuator though
        isMoving = false;
        digitalWrite(forwardPin, LOW);
        digitalWrite(reversePin, LOW); 
    }

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).
    Steering() {
    }

    // initial setup
    void init(int pinForward, int pinReverse, int pinPosition) {
      // set the pins
      forwardPin = pinForward;
      reversePin = pinReverse;
      currentPositionPin = pinPosition;

      // set the pins to be output and set the speed
      pinMode(forwardPin, OUTPUT);
      pinMode(reversePin, OUTPUT);

      // Set to coast as default
      digitalWrite(forwardPin, LOW);
      digitalWrite(reversePin, LOW);
    }

    void initAveragingArrays() {
      for (int i = 0; i < CURRENT_POSITION_READINGS; i++) {
        currentPositions[i] = analogRead(currentPositionPin);
      }
    }
    
    int getSteeringPosition() {
      return steeringTargetScaled;
    }

    // Used during a bad start scenario or when the car is being configured
    void forceStop() {
        digitalWrite(forwardPin, LOW);
        digitalWrite(reversePin, LOW);
    }
    
    /*
     * Sets the new target for the steering position.  Expects the new target to be in scaled units: -100 to 100, 0=center. 
     */
    void setSteeringPosition(int target) {
      // constrain and set the steering target (in scaled units)
      if (target <= 0) {
        steeringTargetScaled = constrain(map(target, -100, 0, steeringMinScaled, steeringCenterScaled), steeringMinScaled, steeringCenterScaled);
      } else {
        steeringTargetScaled = constrain(map(target, 1, 100, steeringCenterScaled+1, steeringMaxScaled), steeringCenterScaled+1, steeringMaxScaled);
      }
      

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

    void setSteeringDeltaScaled(int newDelta) {
      steeringStopDeltaScaled = newDelta;
    }

    int getCurrentPosition() {
      int newPosition = analogRead(currentPositionPin);

      currentPositionIndex++;
      if (currentPositionIndex >= CURRENT_POSITION_READINGS) {
        currentPositionIndex = 0;
      }

      currentPositions[currentPositionIndex] = newPosition;
      
      int total = 0;
      int averagePosition;

      for (int i = 0; i < CURRENT_POSITION_READINGS; i++) {
        total += currentPositions[i];
      }
      
      return total / CURRENT_POSITION_READINGS;
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
      steeringPositionScaled = map(getCurrentPosition(), 0, 1023, -100, 100);
      targetDeltaScaled = abs(steeringPositionScaled - steeringTargetScaled);

      // Are we moving already?
      if (isMoving) {
        
        // we are moving already ... should we stop?
        if (targetDeltaScaled <= steeringStopDeltaScaled) {
           // yes we should
           stopMotor();  
        } else {
          // nope ... gotta keep turning
          runMotor();
        }
 
      } else {

        // we're not moving ... should we start?
        if (targetDeltaScaled >= steeringStopDeltaScaled) {
           // yes we should
           runMotor();  
        } else {
          // nope ... let's make sure the motor is stopped
          stopMotor();
        }
        
      }
    }

    void getStatus(char * status) {
      sprintf(status, "[Steering] current:%i target:%i isMoving:%s Actuator Position Raw:%i",
        steeringPositionScaled,
        steeringTargetScaled,
        isMoving ? "true" : "false",
        getCurrentPosition());
    }
};

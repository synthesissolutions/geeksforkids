/**
 * Steering class
 * 
 * This class serves to be the actual interface to driving the steering for the car.  The intent of this class is to 
 *   allow for a steering position to be set in scaled units (-100 to 100), and this class will take care of making the 
 *   changes to the steering as appropriate.
 */

#include <Wire.h>

#define I2C_ADDRESS 4
#define TRANSMISSION_DELAY_MILLIS 5     // currently this is smaller than the main loop delay so we will always transmit a new value

class Steering {
  private:

    int steeringTargetScaled = 0;          // scaled units (-100 to 100)
    int steeringPositionScaled = 0;        // scaled units (-100 to 100)
    int targetDeltaScaled = 0;             // scaled units (-100 to 100)
    
    // settting default values here ... being a little lazy by defaulting from constants.  
    int steeringMinScaled = -100;
    int steeringMaxScaled = 100;
    int steeringCenterScaled = 0;

    long lastTransmissionTime = 0;

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).
    Steering() {

    }

    // initial setup
    void init() {
      Wire.begin();
    }

    int getSteeringPosition() {
      return steeringTargetScaled;
    }

    // Used during a bad start scenario
    void forceStop() {
        setSteeringPosition(0);
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
     * Update the steering ... sends position data over I2C
     * 
     * NOTE ... it is very important that this method get called frequently.  Calling setSteeringPosition() every time through the loop
     *   is probably enough.  But... if you're not calling that very frequently, then this MUST be called in your main loop so that the 
     *   steering servo is monitored properly.
     *   
     * NOTE #2 ... this could probably be handled automagically with an IntervalTimer.  Seems like a good research project for someone.  ;-)
     * 
     */
    void updateSteering() {
      if (millis() - TRANSMISSION_DELAY_MILLIS > lastTransmissionTime) {
        // steeringMaxScaled should be from -100 to +100 which fits in a 1 signed byte
        int8_t transmitValue = steeringTargetScaled;
        Wire.beginTransmission(I2C_ADDRESS);
        Wire.write(transmitValue);
        Wire.endTransmission();
        lastTransmissionTime = millis();
      }
    }

    void getStatus(char * status) {
      sprintf(status, "[Steering] target:%i", steeringTargetScaled);
    }
};

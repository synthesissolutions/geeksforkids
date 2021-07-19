/**
 * Throttle class
 * 
 * This class serves to be the actual interface to driving the throttle for the car.  The intent of this class is to 
 *   allow for a throttle position to be set in scaled units (-100 to 100), and this class will take care of making the 
 *   changes to the steering as appropriate.
 *   
 *   A key feature of this class is the idea of moving the throttle to a new value over time (rather than an imeediate change), 
 *     to help minimize jerky behavior.  
 */

class Throttle {

  private:

    int directionLeftPin;
    int speedPwmLeftPin;
    int directionRightPin;
    int speedPwmRightPin;

    int leftScaled;
    int leftPwmOut;
    int rightScaled;
    int rightPwmOut;

  public: 

    // default constructor that really does nothing
    Throttle() {
    }

    // initial setup
    void init(int dirLeftPin, int pwmLeftPin, int dirRightPin, int pwmRightPin) {
      // set the pins
      directionLeftPin = dirLeftPin;
      speedPwmLeftPin = pwmLeftPin;
      directionRightPin = dirRightPin;
      speedPwmRightPin = pwmRightPin;

      // set the pin modes
      pinMode(directionLeftPin, OUTPUT);
      pinMode(speedPwmLeftPin, OUTPUT);
      pinMode(directionRightPin, OUTPUT);
      pinMode(speedPwmRightPin, OUTPUT);
    }

    /*
     * set the scaled throttle target.  Expected range is -100 to 100, 0=stopped
     */
    void setThrottle(int left, int right) {
      if (left < -100) left = -100;
      if (left > 100) left = 100;

      if (right < -100) right = -100;
      if (right > 100) right = 100;

      // record the latest setting for logging purposes
      leftScaled = left;
      rightScaled = right;
      
      // figure out the throttle pwm setting (ignoring the direction)
      leftPwmOut = map(abs(left), 0.0, 100.0, THROTTLE_PWM_MIN, THROTTLE_PWM_MAX);
      rightPwmOut = map(abs(right), 0.0, 100.0, THROTTLE_PWM_MIN, THROTTLE_PWM_MAX);

      // now set the direction and the throttle
      if (left == 0) {
        // stop
        digitalWrite(directionLeftPin, HIGH);
        analogWrite(speedPwmLeftPin, THROTTLE_PWM_MIN); 
      } else if (left < 0) {
        //reverse
        digitalWrite(directionLeftPin, LOW);
        analogWrite(speedPwmLeftPin, leftPwmOut);   
      } else if (left > 0) {
        //forward
        digitalWrite(directionLeftPin, HIGH);
        analogWrite(speedPwmLeftPin, leftPwmOut);       
      }

      if (right == 0) {
        // stop
        digitalWrite(directionRightPin, HIGH);
        analogWrite(speedPwmRightPin, THROTTLE_PWM_MIN);                
      } else if (right < 0) {
        //reverse
        digitalWrite(directionRightPin, LOW);
        analogWrite(speedPwmRightPin, rightPwmOut);             
      } else if (right > 0) {
        //forward
        digitalWrite(directionRightPin, HIGH);
        analogWrite(speedPwmRightPin, rightPwmOut);       
      }
    }

    void getStatus(char * status) {
      sprintf(status, "[Throttle] Left:%i scaled %i PWM  Right: %i scaled %i PWM",
        leftScaled,
        leftPwmOut,
        rightScaled,
        rightPwmOut);
    }
};

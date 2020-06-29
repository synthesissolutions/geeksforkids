
/**
 * ButtonDrive class
 * 
 * This class encapulates all the pin read and various calculations for reading the drive buttons.'
 * 
 */

class ButtonDrive {
  private:
    int leftButtonPin;
    int rightButtonPin; 
    int straightButtonPin;
    int reversePin;
 
  public:
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).
    ButtonDrive() { }

    /*
     * init - initialize the ButtonDrive instance with the pins for x and y axes
     */
    void init(int leftButtonPin, int rightButtonPin, int straightButtonPin, int reversePin) {
      this->leftButtonPin = leftButtonPin;
      this->rightButtonPin = rightButtonPin;
      this->straightButtonPin = straightButtonPin;
      this->reversePin = reversePin;
      
      pinMode(leftButtonPin, INPUT_PULLUP);
      pinMode(rightButtonPin, INPUT_PULLUP);
      pinMode(straightButtonPin, INPUT_PULLUP);
      pinMode(reversePin, INPUT_PULLUP);
    }

    // The logic on all button pins is reversed since the buttons connect to ground when pressed
    boolean isLeftButtonPushed() {
      return !digitalRead(leftButtonPin);
    }

    boolean isRightButtonPushed() {
      return !digitalRead(rightButtonPin);
    }

    boolean isStraightButtonPushed() {
      return !digitalRead(straightButtonPin);
    }

    boolean isReverse() {
      return !digitalRead(reversePin);
    }
   
    /* gets the x axis scaled 
     *  
     *  Check to see if the right or left button are pressed and return the scaled value as appropriate
     */
    int getXAxisScaled() {
      if (isLeftButtonPushed()) {
        return -100;
      } else if (isRightButtonPushed()) {
        return 100;
      }

      return 0;
    }

    /* gets the y axis scaled 
     *  
     *  Check to see if any of the buttons are pressed and return the scaled value as appropriate
     */
    int getYAxisScaled() {
      if (isLeftButtonPushed() || isRightButtonPushed() || isStraightButtonPushed()) {
        if (isReverse()) {
          return -100;
        } else {
          return 100;
        }
      }

      return 0;
    }

    String getStatus() {
      String ret = String("[Drive Buttons] ");
      
      ret.concat(String("Left: "));ret.concat(isLeftButtonPushed());
      ret.concat(String(" Right: "));ret.concat(isRightButtonPushed());
      ret.concat(String(" Straight: "));ret.concat(isStraightButtonPushed());
      ret.concat(String(" Reverse: "));ret.concat(isReverse());
      ret.concat(String(" xscaled:"));ret.concat(getXAxisScaled());
      ret.concat(String(" yscaled:"));ret.concat(getYAxisScaled());

      return ret;
    }
};

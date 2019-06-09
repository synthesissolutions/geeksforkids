/**
 * DIPSwitches Class
 * 
 * This class serves to be the interface to the DIP switches on the controller board.  
 */

class Button {
  private:

    int buttonPin;
    unsigned long lastChangedMillis = 0;
    boolean wasClicked = false;
    boolean stableIsPushed = false;
    boolean unstableIsPushed = false;

    const unsigned int STEADY_STATE_MILLIS = 20;   // Minimum number of milliseconds in the new state before we count it as an actual state change


  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    Button() {  
    }

    /*
     * init - initialize the button pin
     */
    void init(int pin) {
      buttonPin = pin;
      pinMode(buttonPin,INPUT_PULLUP);
    }

    /*
     * getters ... just doing digital reads
     * 
     *  We are using INPUT_PULLUP so the Off Position on the dip switch reads as 1 and On as 0
     *  So we hide this detail by negating the reading from the pin.
     */

    void updateButton() {
      boolean newState = !digitalRead(buttonPin);

      if (lastChangedMillis == 0 && newState == stableIsPushed) {
        // Not tracking a potential change and the reading is the same as the current stable state
        // nothing to do, keep the current stable state
        return;
      } else {
        if (lastChangedMillis == 0) {
          // New potential state change
          lastChangedMillis = millis();
          unstableIsPushed = newState;
        } else {
          // check to see if the unstableIsPushed continues to be the new state
          // if it stays the new state without fluctuation for STEADY_STATE_MILLIS milliseconds
          // then it becomes the new stable state
          if (newState != unstableIsPushed) {
            // we fluctuated, check to see if we are back to the original steady state or on a new state
            if (newState == stableIsPushed) {
              lastChangedMillis = 0;
            } else {
              lastChangedMillis = millis();
            }
          } else if (millis() - lastChangedMillis > STEADY_STATE_MILLIS) {
            // We have successfully changed state
            stableIsPushed = newState;
            lastChangedMillis = 0;
            if (!stableIsPushed) {
              // if we went from pushed to not pushed, then a click occured
              wasClicked = true;
            } else {
              wasClicked = false;
            }
          }
        }
      }
    }
    
    boolean isPressed() {return stableIsPushed;}
    boolean isReleased() {return !stableIsPushed;}

    boolean clicked() {
      return wasClicked;
    }

    void clearClicked() {
      wasClicked = false;
    }
  
    String getStatus() {
      String ret = String("[Button] ");
      ret.concat(String("Last Changed:"));ret.concat(lastChangedMillis);
      ret.concat(String(" Stable:"));ret.concat(stableIsPushed);
      ret.concat(String(" Unstable:"));ret.concat(unstableIsPushed);
      ret.concat(String(" Cliked:"));ret.concat(wasClicked);

      return ret;
    }
  
};

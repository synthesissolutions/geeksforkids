/*
 * Very simple, very dirty logger
 * 
 * Very much hard coded to the known config for the car.  Intended to produce a semi-pretty log.
 * 
 * Would be nice if we had a "loggable" interface ... but not really worth trying to do it
 * 
 */
class Logger {
  private:

    int currentLine=0;

    unsigned long lastUpdateTime;
    unsigned long updateDeltaT;

    unsigned int txSpeed = SERIAL_BAUD_RATE;

    String lines[20];

    // Yeah... don't like that the logger has to have these explicity defined.  But it's good enough for now.
    DIPSwitches *dips;
    Configuration *configuration;
    Joystick *joystick;
    SteeringPotGoButton *potGo;
    RemoteControl *rc;
    Steering *steering;
    Throttle *throttle;
    TFTDisplay *tftDisplay;
    int pushCount = 0;
    Button testButton;

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).
    Logger() {
    }

    /*
     * Set up the logging.  An updateTime of 0 will turn logging off.  Very much tied to knowing what objects we're going to log status for!!!
     */
    void init(int updateTime, DIPSwitches *d, Configuration *c, Joystick *j, SteeringPotGoButton *pg, RemoteControl *r, Steering *s, Throttle *t, TFTDisplay *tft) {

      Serial.begin(txSpeed);

      testButton.init(PIN_CONTROL_NEXT);
  
      dips = d;
      configuration = c;
      joystick = j;
      potGo = pg;
      rc = r;
      steering = s;
      throttle = t;
      tftDisplay = tft;
      
      updateDeltaT = updateTime;
      lastUpdateTime = millis();
      Serial.println("Logging started ...");
    }

    // provides a way to add an ad-hoc line to the logging output.  Not sure this is super userful, but eh.
    void addLogLine(String line) {

      // is logging turned on?
      if (updateDeltaT==0) return;

      // as long as we don't already have 20 lines, add the line to the array
      if (currentLine<20) {
        lines[currentLine] = line;
        currentLine++;
      }
      
    }

    // writes the log if it is time to do so.  just spits out the status from all objects, plus any other logging lines 
    void writeLog() {

      // is logging turned on?
      if (updateDeltaT==0) return;

      testButton.updateButton();
      if (testButton.clicked()) {
        pushCount++;
        testButton.clearClicked();
      }
        
      // is it time yet to do another log (we don't want to log too much)
      if (millis()-lastUpdateTime >= updateDeltaT) {

        // Clear TFT
        tftDisplay->clearScreenBlack();
        tftDisplay->setCursor(0,0);
        
        // Yep ... it's time.
        Serial.print("Log Time:");Serial.println(millis());


        Serial.print("Push Count: ");Serial.print(pushCount);
        if (testButton.isPressed()) {
          Serial.println(" Button Pressed!");
        } else {
          Serial.println(" Button NOT Pressed");
        }
        
        tftDisplay->print(2, ILI9341_GREEN, "Log Time: ");
        tftDisplay->println(2, ILI9341_GREEN, millis());
        tftDisplay->println(2, ILI9341_DARKCYAN, dips->getMinimalStatus());
        tftDisplay->println(2, ILI9341_DARKCYAN, configuration->getMinimalStatus());
        tftDisplay->println(2, ILI9341_WHITE, joystick->getMinimalStatus());
        if (configuration->useSteeringPotentiometerAndGoButton()) tftDisplay->println(2, ILI9341_WHITE, potGo->getMinimalStatus());
        tftDisplay->println(2, ILI9341_WHITE, rc->getMinimalStatus());
        tftDisplay->println(2, ILI9341_RED, steering->getMinimalStatus());
        tftDisplay->println(2, ILI9341_RED, throttle->getMinimalStatus());

        // Go through the known instances (they'd better all be here).  Would be better to have an interface and a 
        //   vector of these to iterate over.
        Serial.println(dips->getStatus());
        Serial.print(configuration->getStatus());Serial.println();
        Serial.print(joystick->getStatus());Serial.println();
        Serial.print(potGo->getStatus());Serial.println();
        Serial.print(rc->getStatus());Serial.println();
        Serial.print(steering->getStatus());Serial.println();
        Serial.print(throttle->getStatus());Serial.println();
        Serial.print(tftDisplay->getStatus());Serial.println();
        Serial.print(testButton.getStatus());Serial.println();
        
        // now the ad-hoc lines... this also helps space everythig out so the log is a bit easier to read
        for (int i=0; i<20; i++) {
          Serial.println(lines[i]);   
          // the line has been printed... clear it for the next time  
          lines[i]=String("");   
        }
        // reset the current line for ad-hoc logging to start again at the top
        currentLine=0;

        // couple of extra spaces
        Serial.println();
        Serial.println();

        // and set up for the next time writeLog is called
        lastUpdateTime = millis();
      }
    }
};

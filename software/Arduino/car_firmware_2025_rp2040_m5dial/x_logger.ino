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

    char lines[LOGGER_LINE_COUNT][LOGGER_LINE_LENGTH];
    char statusLine[LOGGER_LINE_LENGTH];
    
    // Yeah... don't like that the logger has to have these explicity defined.  But it's good enough for now.
    Eeprom *eeprom;
    Configuration *configuration;
    Joystick *joystick;
    RemoteControl *rc;
    Steering *steering;
    Throttle *throttle;

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).
    Logger() {
    }

    /*
     * Set up the logging.  An updateTime of 0 will turn logging off.  Very much tied to knowing what objects we're going to log status for!!!
     */
    void init(int updateTime, Eeprom *e, Configuration *c, Joystick *j, RemoteControl *r, Steering *st, Throttle *t) {

      Serial.begin(txSpeed);

      eeprom = e;
      configuration = c;
      joystick = j;
      rc = r;
      steering = st;
      throttle = t;
      
      updateDeltaT = updateTime;
      lastUpdateTime = millis();
      Serial.println("Logging started ...");
    }

    // provides a way to add an ad-hoc line to the logging output.  Not sure this is super userful, but eh.
    void addLogLine(const char * line) {

      // is logging turned on?
      if (updateDeltaT==0) return;

      // as long as we don't already have 20 lines, add the line to the array
      if (currentLine<LOGGER_LINE_COUNT) {
        sprintf(lines[currentLine], "%s", line);
        currentLine++;
      }
      
    }

    // writes the log if it is time to do so.  just spits out the status from all objects, plus any other logging lines 
    void writeLog() {
      // is logging turned on?
      if (updateDeltaT==0) return;

      // is it time yet to do another log (we don't want to log too much)
      if (millis()-lastUpdateTime >= updateDeltaT) {
        Serial.print("Version: ");Serial.println(RELEASE_VERSION);
        
        Serial.print("Log Time:");Serial.println(millis());
  
        // Go through the known instances (they'd better all be here).  Would be better to have an interface and a 
        //   vector of these to iterate over. 
        configuration->getStatus(statusLine);
        Serial.write(statusLine, strlen(statusLine));
        Serial.println();

        joystick->getStatus(statusLine);
        Serial.write(statusLine, strlen(statusLine));
        Serial.println();
        
        if (configuration->useRc()) {
          rc->getStatus(statusLine);
          Serial.write(statusLine, strlen(statusLine));
          Serial.println();
        }
        
        steering->getStatus(statusLine);
        Serial.write(statusLine, strlen(statusLine));
        Serial.println();

        throttle->getStatus(statusLine);
        Serial.write(statusLine, strlen(statusLine));
        Serial.println();

        eeprom->getStatus(statusLine);
        Serial.write(statusLine, strlen(statusLine));
        Serial.println();

        // now the ad-hoc lines... this also helps space everythig out so the log is a bit easier to read
        for (int i=0; i<currentLine; i++) {
          Serial.write(lines[i], strlen(lines[i]));   
          Serial.println();   // have to add this, as Serial.write doesn't include a CR
          // the line has been printed... clear it for the next time  
          lines[i][0] = (char)0;
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

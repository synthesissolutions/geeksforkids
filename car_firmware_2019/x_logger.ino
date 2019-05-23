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
    DIPSwitches *dips;
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
    void init(int updateTime, DIPSwitches *d, Joystick *j, RemoteControl *r, Steering *s, Throttle *t) {

      Serial.begin(txSpeed);
  
      dips = d;
      joystick = j;
      rc = r;
      steering = s;
      throttle = t;
      
      updateDeltaT = updateTime;
      lastUpdateTime = millis();
      Serial.println("Logging started ...");
    }

    // provides a way to add an ad-hoc line to the logging output.  Not very elegant
    void addLogLine(String line) {

      // is logging turned on?
      if (updateDeltaT==0) return;
      
      if (currentLine<20) {
        lines[currentLine] = line;
        currentLine++;
      }
      
    }

    // writes the log if it is time to do so.  just spits out the status from all objects, plus any other logging lines 
    void writeLog() {

      // is logging turned on?
      if (updateDeltaT==0) return;

      if (millis()-lastUpdateTime >= updateDeltaT) {
        Serial.print("Log Time:");Serial.println(millis());
        
        Serial.print(dips->getStatus());
        Serial.print(joystick->getStatus());
        Serial.print(rc->getStatus());
        Serial.print(steering->getStatus());
        Serial.print(throttle->getStatus());
        
        Serial.println();
        for (int i=0; i<20; i++) {
          Serial.println(lines[i]);     
          lines[i]=String("");   
        }
        
        currentLine=0;
        lastUpdateTime = millis();
        Serial.println();
        Serial.println();
      }
    }

  
};

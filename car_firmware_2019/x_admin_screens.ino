/**
 * Admin Screen Classes
 * 
 * This file contains multiple class definitions for the various Admin screens.
 * This set of classes is tightly coupled to the other classes in this sketch.
 */

/**
 * AdminScreen Virtual Class
 * 
 * This defines the AdminScreen interface
 */

class AdminScreen {
  public:
    virtual String getTitle() = 0;
    virtual String getShortTitle() = 0;
    virtual void render() = 0;

    String coordToString(int x, int y) {
      String val = "("; 
      val.concat(x); 
      val.concat(", "); 
      val.concat(y);
      val.concat(")");

      return val;
    }
};

/**
 * OverviewScreen Class
 * 
 * This class creates the Overview Admin Screen  
 */

class OverviewScreen : public AdminScreen {
  private:

    TFTDisplay *tftDisplay;
    DIPSwitches *dips;
    Configuration *configuration;
    Joystick *joystick;
    SteeringPotGoButton *potGo;
    RemoteControl *rc;
    Steering *steering;
    Throttle *throttle;   

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    OverviewScreen() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init(DIPSwitches *d, Configuration *c, Joystick *j, SteeringPotGoButton *pg, RemoteControl *r, Steering *s, Throttle *t, TFTDisplay *tft) {
      dips = d;
      configuration = c;
      joystick = j;
      potGo = pg;
      rc = r;
      steering = s;
      throttle = t;
      tftDisplay = tft;
    }

    virtual String getTitle() {
      return "Overview";
    }

    virtual String getShortTitle() {
      return "Ov";
    }

    virtual void render() {
      tftDisplay->print(2, ILI9341_GREEN, "Time: ");
      tftDisplay->println(2, ILI9341_GREEN, millis());
      tftDisplay->println(2, ILI9341_DARKCYAN, dips->getMinimalStatus());
      tftDisplay->println(2, ILI9341_DARKCYAN, configuration->getMinimalStatus());
      tftDisplay->println(2, ILI9341_WHITE, joystick->getMinimalStatus());
      if (configuration->useSteeringPotentiometerAndGoButton()) tftDisplay->println(2, ILI9341_WHITE, potGo->getMinimalStatus());
      tftDisplay->println(2, ILI9341_WHITE, rc->getMinimalStatus());
      tftDisplay->println(2, ILI9341_RED, steering->getMinimalStatus());
      tftDisplay->println(2, ILI9341_RED, throttle->getMinimalStatus());
    }
};

/**
 * JoyStickAdminScreen Class
 * 
 * This class creates the Overview Admin Screen  
 */

class JoyStickAdminScreen : public AdminScreen {
  private:

    TFTDisplay *tftDisplay;
    Joystick *joystick;
    Configuration *configuration;

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    JoyStickAdminScreen() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init(Joystick *j, Configuration *c, TFTDisplay *t) {
      joystick = j;
      configuration = c;
      tftDisplay = t;
    }

    virtual String getTitle() {
      return "Joystick";
    }

    virtual String getShortTitle() {
      return "J";
    }

    virtual void render() {
      String active = ""; if (joystick->isActive()) active.concat("Active"); else active.concat("NOT Active");
      String raw = "Raw: "; raw.concat(coordToString(joystick->getXAxisRaw(), joystick->getYAxisRaw()));
      String scaled = "Scaled: "; scaled.concat(coordToString(joystick->getXAxisScaled(), joystick->getYAxisScaled()));
      String inverted = "Inverted: "; 
      if (!joystick->getInvertXAxis() && !joystick->getInvertYAxis()) 
        inverted.concat("None"); 
      else {
        if (joystick->getInvertXAxis()) inverted.concat("X ");
        if (joystick->getInvertYAxis()) inverted.concat("Y");
      }
      String maxSpeedLabel = "Max Speed: ";
      String maxSpeed = "";
      maxSpeed.concat((int)(configuration->getSpeedMultiplier() * 100));
      maxSpeed.concat("%");

      tftDisplay->println(STANDARD_TEXT_SIZE, ILI9341_WHITE, active);
      tftDisplay->println(STANDARD_TEXT_SIZE, ILI9341_WHITE, raw);
      tftDisplay->println(STANDARD_TEXT_SIZE, ILI9341_WHITE, scaled);
      tftDisplay->println(STANDARD_TEXT_SIZE, ILI9341_WHITE, inverted);
      tftDisplay->print(STANDARD_TEXT_SIZE, ILI9341_WHITE, maxSpeedLabel);
      tftDisplay->println(STANDARD_TEXT_SIZE, ILI9341_RED, maxSpeed);
    }
};

/**
 * JoyStickAdminScreen Class
 * 
 * This class creates the Overview Admin Screen  
 */

class RCAdminScreen : public AdminScreen {
  private:

    TFTDisplay *tftDisplay;
    RemoteControl *rc;   

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    RCAdminScreen() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init(RemoteControl *r, TFTDisplay *t) {
      rc = r;
      tftDisplay = t;
    }

    virtual String getTitle() {
      return "RC";
    }

    virtual String getShortTitle() {
      return "RC";
    }

    virtual void render() {
      String active = ""; if (rc->isActive()) active.concat("Active"); else active.concat("NOT Active");
      String throttle = " Raw: "; throttle.concat(rc->getThrottlePWM()); throttle.concat("  Scaled: "); throttle.concat(rc->getThrottleScaled());
      String steering = " Raw: "; steering.concat(rc->getSteeringPWM()); steering.concat("  Scaled: "); steering.concat(rc->getSteeringScaled());

      if (rc->isBadRcStart()) {
        tftDisplay->println(STANDARD_TEXT_SIZE, ILI9341_RED, "Bad RC Start");
      }
      tftDisplay->println(STANDARD_TEXT_SIZE, ILI9341_WHITE, active);
      tftDisplay->println(STANDARD_TEXT_SIZE, ILI9341_WHITE, "Throttle");
      tftDisplay->println(STANDARD_TEXT_SIZE, ILI9341_WHITE, throttle);
      tftDisplay->println(STANDARD_TEXT_SIZE, ILI9341_WHITE, "Steering");
      tftDisplay->println(STANDARD_TEXT_SIZE, ILI9341_WHITE, steering);
    }
};


/**
 * SteeringPotGoAdminScreen Class
 * 
 * This class creates the Overview Admin Screen  
 */

class SteeringPotGoAdminScreen : public AdminScreen {
  private:

    TFTDisplay *tftDisplay;
    SteeringPotGoButton *potGo;

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    SteeringPotGoAdminScreen() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init(SteeringPotGoButton *p, TFTDisplay *t) {
      potGo = p;
      tftDisplay = t;
    }

    virtual String getTitle() {
      return "St Pot Go Button";
    }

    virtual String getShortTitle() {
      return "SPG";
    }

    virtual void render() {
      tftDisplay->println(STANDARD_TEXT_SIZE, ILI9341_WHITE, potGo->getMinimalStatus());
    }
};


/**
 * SteeringAdminScreen Class
 * 
 * This class creates the Overview Admin Screen  
 */

class SteeringAdminScreen : public AdminScreen {
  private:

    TFTDisplay *tftDisplay;
    Steering *steering;

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    SteeringAdminScreen() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init(Steering *s, TFTDisplay *t) {
      steering = s;
      tftDisplay = t;
    }

    virtual String getTitle() {
      return "Steering";
    }

    virtual String getShortTitle() {
      return "St";
    }

    virtual void render() {
      String current = "Cur Pos Scaled: "; current.concat(steering->getSteeringPositionScaled());
      String target = "Target Scaled: "; target.concat(steering->getSteeringTargetScaled());
      String raw = "Actuator Pos Raw: "; raw.concat(steering->getSteeringPositionRaw());
      
      tftDisplay->println(STANDARD_TEXT_SIZE, ILI9341_WHITE, current);
      tftDisplay->println(STANDARD_TEXT_SIZE, ILI9341_WHITE, target);
      tftDisplay->println(STANDARD_TEXT_SIZE, ILI9341_WHITE, raw);
    }
};


/**
 * ThrottleAdminScreen Class
 * 
 * This class creates the Overview Admin Screen  
 */

class ThrottleAdminScreen : public AdminScreen {
  private:

    TFTDisplay *tftDisplay;
    Throttle *throttle;  

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    ThrottleAdminScreen() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init(Throttle *th, TFTDisplay *t) {
      throttle = th;
      tftDisplay = t;
    }

    virtual String getTitle() {
      return "Throttle";
    }

    virtual String getShortTitle() {
      return "Th";
    }

    virtual void render() {
      String current = "Current Scaled: "; current.concat(throttle->getCurrentThrottleScaled());
      String target = "Target Scaled: "; target.concat(throttle->getTargetThrottleScaled());
      String pwm = "PWM Out: "; pwm.concat(throttle->getCurrentPWMOut());
      
      tftDisplay->println(STANDARD_TEXT_SIZE, ILI9341_WHITE, current);
      tftDisplay->println(STANDARD_TEXT_SIZE, ILI9341_WHITE, target);
      tftDisplay->println(STANDARD_TEXT_SIZE, ILI9341_WHITE, pwm);
    }
};


/**
 * AdminScreen Virtual Class
 * 
 * This defines the AdminScreen interface
 */
class AdminScreenManager {
  private:
    // For some reason it is necessary to define these here or they don't exist after init if created there
    OverviewScreen overviewScreen;
    JoyStickAdminScreen joystickScreen;
    RCAdminScreen rcScreen;
    SteeringPotGoAdminScreen potGoScreen;
    SteeringAdminScreen steeringScreen;
    ThrottleAdminScreen throttleScreen;
    
    AdminScreen *screens[6];
    int screenIndex = 0;
    
    unsigned long lastUpdateTime;
    unsigned long updateDeltaT;
    
    TFTDisplay *tftDisplay;
    DIPSwitches *dips;
    Configuration *configuration;
    Joystick *joystick;
    SteeringPotGoButton *potGo;
    RemoteControl *rc;
    Steering *steering;
    Throttle *throttle;

    Button nextButton;

    int screenCount() {
      return sizeof(screens) / sizeof(screens[0]);
    }
    
    void renderMenu() {
      tftDisplay->print(STANDARD_TEXT_SIZE, ILI9341_DARKGREY, "Menu:");
      for (int i = 0; i < screenCount(); i++) {
        tftDisplay->print(STANDARD_TEXT_SIZE, ILI9341_DARKGREY, " ");
        if (i == screenIndex) {
          tftDisplay->print(STANDARD_TEXT_SIZE, ILI9341_PURPLE, screens[i]->getShortTitle());
        } else {
          tftDisplay->print(STANDARD_TEXT_SIZE, ILI9341_DARKGREY, screens[i]->getShortTitle());
        }
      }

      tftDisplay->println(STANDARD_TEXT_SIZE, ILI9341_DARKGREY, "");
    }
    
  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    AdminScreenManager() {  
    }

    /*
     * init - initialize the various objects used by the admin screens and the admin buttons
     */
    void init(int updateTime, DIPSwitches *d, Configuration *c, Joystick *j, SteeringPotGoButton *pg, RemoteControl *r, Steering *s, Throttle *t, TFTDisplay *tft) {
      dips = d;
      configuration = c;
      joystick = j;
      potGo = pg;
      rc = r;
      steering = s;
      throttle = t;
      tftDisplay = tft;

      int i = 0;
      overviewScreen.init(d, c, j, pg, r, s, t, tft);
      screens[i++] = &overviewScreen;

      joystickScreen.init(j, c, tft);
      screens[i++] = &joystickScreen;

      rcScreen.init(r, tft);
      screens[i++] = &rcScreen;

      potGoScreen.init(pg, tft);
      screens[i++] = &potGoScreen;

      throttleScreen.init(t, tft);
      screens[i++] = &throttleScreen;

      steeringScreen.init(s, tft);
      screens[i++] = &steeringScreen;

      nextButton.init(PIN_CONTROL_NEXT);

      updateDeltaT = updateTime;
      lastUpdateTime = millis();
      Serial.println("Admin Screens started ...");
    }

    void update() {
      // is admin turned on?
      if (updateDeltaT==0) return;

      nextButton.updateButton();

      if (nextButton.clicked()) {
        screenIndex = (screenIndex + 1) % screenCount();
        nextButton.clearClicked();
        lastUpdateTime = millis()-updateDeltaT; // Force a refresh if the button was clicked
      }
        
      // is it time yet to do update the screen contents? (we don't want to update too much)
      if (millis()-lastUpdateTime >= updateDeltaT) {
        AdminScreen *currentScreen = screens[screenIndex];

        tftDisplay->clearScreenBlack();
        tftDisplay->setCursor(0,0);
        
        renderMenu();
        
        tftDisplay->drawLine(0, 18, 319, 19, ILI9341_DARKGREY);

        tftDisplay->printBlankLine(1);
        tftDisplay->println(HEADING_TEXT_SIZE, ILI9341_PURPLE, currentScreen->getTitle());
        tftDisplay->printBlankLine(1);
      
        currentScreen->render();

        lastUpdateTime = millis();
      }
    }
};

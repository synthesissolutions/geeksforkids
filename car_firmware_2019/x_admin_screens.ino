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

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    JoyStickAdminScreen() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init(Joystick *j, TFTDisplay *t) {
      joystick = j;
      tftDisplay = t;
    }

    virtual String getTitle() {
      return "Joystick";
    }

    virtual String getShortTitle() {
      return "J";
    }

    virtual void render() {
      tftDisplay->println(2, ILI9341_WHITE, joystick->getMinimalStatus());
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
    
    AdminScreen *screens[2];
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
      tftDisplay->print(2, ILI9341_DARKGREY, "Menu:");
      for (int i = 0; i < screenCount(); i++) {
        tftDisplay->print(2, ILI9341_DARKGREY, " ");
        if (i == screenIndex) {
          tftDisplay->print(2, ILI9341_PURPLE, screens[i]->getShortTitle());
        } else {
          tftDisplay->print(2, ILI9341_DARKGREY, screens[i]->getShortTitle());
        }
      }

      tftDisplay->println(2, ILI9341_DARKGREY, "");
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

      overviewScreen.init(d, c, j, pg, r, s, t, tft);
      screens[0] = &overviewScreen;

      joystickScreen.init(j, tft);
      screens[1] = &joystickScreen;

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
      }
        
      // is it time yet to do update the screen contents? (we don't want to update too much)
      if (millis()-lastUpdateTime >= updateDeltaT) {
        AdminScreen *currentScreen = screens[screenIndex];

        tftDisplay->clearScreenBlack();
        tftDisplay->setCursor(0,0);
        
        renderMenu();
        
        tftDisplay->println(2, ILI9341_DARKGREY, "Draw a dividing line here");

        tftDisplay->println(3, ILI9341_PURPLE, currentScreen->getTitle());
      
        currentScreen->render();

        lastUpdateTime = millis();
      }
    }
};

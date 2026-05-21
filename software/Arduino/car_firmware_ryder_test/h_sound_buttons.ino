 /**
 * SoundButtons Class
 * 
 * This class provides an interface to the 3 NeoPixels and 2 External LED strips
 */

#define SOUND_A           0
#define SOUND_B           1
#define ACTION_TRIGGER_1  2
#define ACTION_TRIGGER_2  3

class SoundButtons {
  private:
    GpioExpander *gpioExpander;
    bool trigger1Pressed = false;
    bool trigger2Pressed = false;
  
  public:
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).
    SoundButtons() {
    }

    /*
     * init - initialize the joystick instance with the pins for x and y axes
     */
    void init(GpioExpander *g) {
      gpioExpander = g;
      
      pinMode(DRIVE_SOUND_A, INPUT_PULLUP);
      pinMode(DRIVE_SOUND_B, INPUT_PULLUP);
    }

    void processSoundButtons() {
      if (!digitalRead(DRIVE_SOUND_A)) {
        // Trigger sound A
      }

      if (!digitalRead(DRIVE_SOUND_B)) {
        // Trigger sound B
      }

      trigger1Pressed = !gpioExpander->getActionTrigger1();
      trigger2Pressed = !gpioExpander->getActionTrigger2();
    }

    void getStatus(char * status) {
      sprintf(status, "[Sound Buttons] Sound A: %s Sound B: %s Action 1: %s Action 2: %s",
        !digitalRead(DRIVE_SOUND_A) ? "Pressed" : "-",
        !digitalRead(DRIVE_SOUND_B) ? "Pressed" : "-",
        trigger1Pressed ? "Pressed" : "-",
        trigger2Pressed ? "Pressed" : "-");
    }
};

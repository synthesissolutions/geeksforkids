 /**
 * GpioExpander Class
 * 
 * This class serves to be the interface to the to AW9523 GPIO Expander
 */

#include <Adafruit_AW9523.h>

Adafruit_AW9523 aw;

class GpioExpander {
  private:
    bool _gpioExpanderAvailable = false;
 
  public:
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).
    GpioExpander() {
    }

    /*
     * init - initialize the joystick instance with the pins for x and y axes
     */
    void init() {
      if (aw.begin(0x58)) {
        _gpioExpanderAvailable = true;

        // The first 8 pins are all inputs
        aw.pinMode(PIN_GPIO_EXP_SW_REVERSE, INPUT);
        aw.pinMode(PIN_GPIO_EXP_SW_FORWARD, INPUT);
        aw.pinMode(PIN_GPIO_EXP_SW_HIGH_LOW, INPUT);
        aw.pinMode(PIN_GPIO_EXP_SW_ACTION_TRIG2, INPUT);
        aw.pinMode(PIN_GPIO_EXP_SW_ACTION_TRIG1, INPUT);
        aw.pinMode(PIN_GPIO_EXP_MOTOR_FAULT, INPUT);
        aw.pinMode(PIN_GPIO_EXP_MOTOR_CHOPPING, INPUT);
        aw.pinMode(PIN_GPIO_EXP_TEMP_ALERT, INPUT);

        // The last 8 pins are all outputs
        aw.pinMode(PIN_GPIO_EXP_MOTOR_SLEEP, OUTPUT);
        aw.pinMode(PIN_GPIO_EXP_SPARE, OUTPUT);
        aw.pinMode(PIN_GPIO_EXP_DAC_MUTE, OUTPUT);
        aw.pinMode(PIN_GPIO_EXP_AMP_SD, OUTPUT);
        aw.pinMode(PIN_GPIO_EXP_LOAD_SWITCH_A, OUTPUT);
        aw.pinMode(PIN_GPIO_EXP_LOAD_SWITCH_B, OUTPUT);
        aw.pinMode(PIN_GPIO_EXP_LOAD_SWITCH_C, OUTPUT);
        aw.pinMode(PIN_GPIO_EXP_LOAD_SWITCH_D, OUTPUT);

        aw.digitalWrite(PIN_GPIO_EXP_MOTOR_SLEEP, LOW);
        aw.digitalWrite(PIN_GPIO_EXP_SPARE, LOW);
        aw.digitalWrite(PIN_GPIO_EXP_DAC_MUTE, LOW);
        aw.digitalWrite(PIN_GPIO_EXP_AMP_SD, LOW);

        // Enable all 12v JST XH connectors
        aw.digitalWrite(PIN_GPIO_EXP_LOAD_SWITCH_A, HIGH);
        aw.digitalWrite(PIN_GPIO_EXP_LOAD_SWITCH_B, HIGH);
        aw.digitalWrite(PIN_GPIO_EXP_LOAD_SWITCH_C, HIGH);
        aw.digitalWrite(PIN_GPIO_EXP_LOAD_SWITCH_D, HIGH);
      }
    }

    bool getGpioExpanderAvailable() {
      return _gpioExpanderAvailable;
    }

    void setMotorSleep(uint8_t val) {
      if (!_gpioExpanderAvailable) return;
      
      aw.digitalWrite(PIN_GPIO_EXP_MOTOR_SLEEP, val);
    }
    
    void setGpioExtra(uint8_t val) {
      if (!_gpioExpanderAvailable) return;
      
      aw.digitalWrite(PIN_GPIO_EXP_SPARE, val);
    }
    
    void setDacMute(uint8_t val) {
      if (!_gpioExpanderAvailable) return;
      
      aw.digitalWrite(PIN_GPIO_EXP_DAC_MUTE, val);
    }
    
    void setAmpSd(uint8_t val) {
      if (!_gpioExpanderAvailable) return;
      
      aw.digitalWrite(PIN_GPIO_EXP_AMP_SD, val);
    }
    
    bool getSwitchReverse() {
      if (!_gpioExpanderAvailable) return false;
      
      return aw.digitalRead(PIN_GPIO_EXP_SW_REVERSE);
    }

    bool getSwitchForward() {
      if (!_gpioExpanderAvailable) return false;
      
      return aw.digitalRead(PIN_GPIO_EXP_SW_FORWARD);
    }

    bool getSwitchHighLow() {
      if (!_gpioExpanderAvailable) return false;
      
      return aw.digitalRead(PIN_GPIO_EXP_SW_HIGH_LOW);
    }

    bool getActionTrigger2() {
      if (!_gpioExpanderAvailable) return false;
      
      return aw.digitalRead(PIN_GPIO_EXP_SW_ACTION_TRIG2);
    }

    bool getActionTrigger1() {
      if (!_gpioExpanderAvailable) return false;
      
      return aw.digitalRead(PIN_GPIO_EXP_SW_ACTION_TRIG1);
    }

    bool getMotorFault() {
      if (!_gpioExpanderAvailable) return false;
      
      return aw.digitalRead(PIN_GPIO_EXP_MOTOR_FAULT);
    }

    bool getMotorChopping() {
      if (!_gpioExpanderAvailable) return false;
      
      return aw.digitalRead(PIN_GPIO_EXP_MOTOR_CHOPPING);
    }

    bool getTemperatureAlert() {
      if (!_gpioExpanderAvailable) return false;
      
      return aw.digitalRead(PIN_GPIO_EXP_TEMP_ALERT);
    }

    void getStatus(char * status) {
      sprintf(status, "[GPIO Expander] avail: %s Sw Rev: %s Sw Fwd: %s Sw HiLow: %s Action 1: %s Action 2: %s Motor Fault: %s Motor Chopping %s Temperature Alert %s",
        getGpioExpanderAvailable() ? "true" : "false",
        getSwitchReverse() ? "true" : "false",
        getSwitchForward() ? "true" : "false",
        getSwitchHighLow() ? "true" : "false",
        getActionTrigger1() ? "true" : "false",
        getActionTrigger2() ? "true" : "false",
        getMotorFault() ? "true" : "false",
        getMotorChopping() ? "true" : "false",
        getTemperatureAlert() ? "true" : "false");
    }
};

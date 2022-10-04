 /**
 * RemoteControl Class
 * 
 * This class serves to be the interface to the to the parental remote control unit
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 128 // OLED display height, in pixels
#define OLED_RESET -1     // can set an oled reset pin if desired
Adafruit_SH1107 display = Adafruit_SH1107(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, 1000000, 100000);

// The number of throttle and steering readings to average to smooth results
#define RC_THROTTLE_READINGS 15
#define RC_STEERING_READINGS 15

// The number of readings to take to check for unusual values that would indicate
// a bad RC start. Typically caused by someone holding the throttle in while turning on the remote.
#define RC_START_LENGTH 10

class RemoteControl {
  private:

    int pinRCSteering;
    int pinRCThrottle;

    // variables to track the PWM signals
    unsigned long steeringPulseStart; // the timestamp in ms for the current PWM steering pulse
    unsigned long steeringPwm = 0;    // the length of the last full PWM steering pulse in microseconds
    boolean steeringSignalHigh = false; // flag indicating that the start of a PWM signal (rising edge) has occured
    unsigned long throttlePulseStart; // the timestamp in ms for the current PWM throttle pulse
    unsigned long throttlePwm = 0;    // the length of the last full PWM throttle pulse in microseconds
    boolean throttleSignalHigh = false; // flag indicating that the start of a PWM signal (rising edge) has occured
    
    // these are in raw pin read units (0 to 1024)
    int steeringMin = STEERING_RC_MIN;
    int steeringCenter = STEERING_RC_CENTER;
    int steeringMax = STEERING_RC_MAX;

    // these are in raw pin read units (0 to 1024)
    int throttleMin = THROTTLE_RC_MIN;
    int throttleCenter = THROTTLE_RC_CENTER;
    int throttleMax = THROTTLE_RC_MAX;
    
    // initial values of -1 ... used to help figure out if we've seen a 0 signal yet
    int steeringScaled = -1;
    int throttleScaled = -1;

    unsigned long lastSignificantInputMillis = 0;
    unsigned long lastThrottleInputMillis = 0;
    unsigned long lastSteeringInputMillis = 0;


    int throttleReadings[RC_THROTTLE_READINGS];
    int throttleIndex = 0;

    int steeringReadings[RC_STEERING_READINGS];
    int steeringIndex = 0;
    
    boolean hasCentered = false;

  public: 
    // Track the first few signal readings and mark a bad start if any of those readings
    // are outside of a small dead zone
    boolean badControlStart = false;
    unsigned long throttlePwmStart[10];
    int throttlePwmStartIndex = 0;
    unsigned long steeringPwmStart[10];
    int steeringPwmStartIndex = 0;

    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).
    RemoteControl() {
    }

    // initial setup
    void init(int steeringPin, int throttlePin) {
      pinRCSteering = steeringPin;
      pinRCThrottle = throttlePin;

      // Setup OLED Featherwing
      delay(250); // wait for the OLED to power up
      display.begin(0x3D, true); // Address 0x3C default
    
      // Show image buffer on the display hardware.
      // Since the buffer is intialized with an Adafruit splashscreen
      // internally, this will display the splashscreen.
      display.display();
      delay(50);
    
      // Clear the buffer.
      display.clearDisplay();
      display.display();
    
      display.setRotation(1);
    }

    void setSteeringRange(int sMin, int sCenter, int sMax) {
      steeringMin = sMin;
      steeringCenter = sCenter;
      steeringMax = sMax;
    }

    void setThrottleRange(int tMin, int tCenter, int tMax) {
      throttleMin = tMin;
      throttleCenter = tCenter;
      throttleMax = tMax;
    }
    
    /*
     * get the current steering position (scaled units -100 to 100)
     */
    int getSteeringScaled() {
      return steeringScaled;
    }
    
    int updateSteeringScaled() {
      int steeringRaw = steeringPwm;

      updateOled();
      
      // Value is not in the expected range return 0 as a safe value
      if (steeringRaw == 0 || steeringRaw >= RC_LIMIT) {
        return 0; 
      }

      if (steeringRaw < steeringCenter) {
        steeringScaled = constrain(map(steeringRaw, steeringMin, steeringCenter, -100, 0), -100, 0);
      } else if (steeringRaw > steeringCenter) {
        steeringScaled = constrain(map(steeringRaw, steeringCenter, steeringMax, 0, 100), 0, 100);        
      } else {
        steeringScaled = 0;
      }

      if (steeringScaled >= RC_STEERING_DEADZONE_LOW && steeringScaled <= RC_STEERING_DEADZONE_HIGH) {
        steeringScaled = 0;
        lastSteeringInputMillis = 0; // this does not count as a significant input since it didn't leave the deadzone
      } else {
        lastSignificantInputMillis = millis();
      }
      
      return steeringScaled;
    }

    void updateOled() {
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SH110X_WHITE);
      display.setCursor(0,0);
      display.println("Steering: ");
      display.println(steeringPwm);
      display.println("");
      display.print("Throttle: ");
      display.println(throttlePwm);
      display.display();
    }

    /*
     * get the current throttle position (scaled units -100 to 100)
     */
    int getThrottleScaled() {
      return throttleScaled;
    }
    
    int updateThrottleScaled() {  
      int throttleRaw = throttlePwm;

      // Value is not in the expected range return 0 as a safe value
      if (throttleRaw == 0 || throttleRaw >= RC_LIMIT) {
        return 0; 
      }

      if (throttleRaw < throttleCenter) {
        throttleScaled = constrain(map(throttleRaw, throttleMin, throttleCenter, -100, 0), -100, 0);
      } else if (throttleRaw > throttleCenter) {
        throttleScaled = constrain(map(throttleRaw, throttleCenter, throttleMax, 0, 100), 0, 100);        
      } else {
        throttleScaled = 0;
      }

      if (throttleScaled >= RC_THROTTLE_DEADZONE_LOW && throttleScaled <= RC_THROTTLE_DEADZONE_HIGH) {
        throttleScaled = 0;
        lastThrottleInputMillis = 0; // this does not count as a significant input since it didn't leave the deadzone
      } else {        
        lastSignificantInputMillis = millis();
      }

      return throttleScaled;
    }

    boolean isBadRcStart() {
      return badControlStart;
    }

    /*
     * Is the remote control "hot" ... meaning does the parent have control.  This also accounts for the timeout... e.g. has the parent had control recently.
     */
    boolean isActive() {
       
      //If we've not yet centered the controls, then we're not active yet
      if (!hasCentered) {
        if (steeringScaled == 0 && throttleScaled == 0) {
          hasCentered=true;          
        } else {
          return false;         
        }
      }

      // we're active if we've had a significant input recently enough
      if (millis() - lastSignificantInputMillis < RC_OVERRIDE_TIMEOUT) {
        return true;
      }
      
      return false;
    }

    /* 
     * Handler for IRQ updates for steering.
     * 
     * NOTE: This code is considered critical (should not be interrupted), but does not disable interrupts.  This is because we assume it's being 
     *       called in an IRQ handler and therefore interrupts are already disabled until we exit.  We are doing the math to figure out the pulse width
     *       and the scaled signal here, which is based on the assumption that the board in use (e.g. teensy) is much faster in clock speed than the 
     *       resolution of the PWM signal.  
     */
    void steeringIRQHandler() {
      if(digitalRead(pinRCSteering) == 1){
        if (!steeringSignalHigh) {
          // rising edge of the PWM signal
          // record when the pulse started
          steeringPulseStart = micros();
          steeringSignalHigh = true;
        }
        
      } else if (steeringSignalHigh) {
        // falling edge of the PWM signal
        // record the duty cycle in microseconds
        steeringPwm = micros() - steeringPulseStart;

        if (steeringPwmStartIndex < 10) {
          steeringPwmStart[steeringPwmStartIndex] = steeringPwm;
          steeringPwmStartIndex++;

          // CRITICAL NOTE: If the RC steering is not centered when it is turned on
          // then when it is turned off it will return a non-centered result.
          // !!!!! IMPORTANT !!!!! This means that when the RC remote is turned off in this
          // case and the car is still it will turn the wheel in that direction
          // and prevent the child from controlling via the joystick
          if (steeringPwm < 1400 || steeringPwm > 1600) {
            badControlStart = true;
          }
        }

        // reset for the next pulse
        steeringSignalHigh = false;
      }
      
    }
   
    /* 
     * Handler for IRQ updates for throttle.
     * 
     * NOTE: This code is considered critical (should not be interrupted), but does not disable interrupts.  This is because we assume it's being 
     *       called in an IRQ handler and therefore interrupts are already disabled until we exit.  We are doing the math to figure out the pulse width
     *       and the scaled signal here, which is based on the assumption that the board in use (e.g. teensy) is much faster in clock speed than the 
     *       resolution of the PWM signal.  
     */
    void throttleIRQHandler() {
      if(digitalRead(pinRCThrottle) == 1){
        if (!throttleSignalHigh) {
          // rising edge of the PWM signal
          // record when the pulse started
          throttlePulseStart = micros();
          throttleSignalHigh = true;
        }
      } else if (throttleSignalHigh) {
        // falling edge of the PWM signal
        // record the duty cycle in microseconds
        throttlePwm = micros() - throttlePulseStart;

        if (throttlePwmStartIndex < 10) {
          throttlePwmStart[throttlePwmStartIndex] = throttlePwm;
          throttlePwmStartIndex++;

          // CRITICAL NOTE: If the RC throttle is not centered when it is turned on
          // then when it is turned off it will return a non-centered result.
          // !!!!! IMPORTANT !!!!! This means that when the RC remote is turned off in this
          // case and the car is still it will drive in that direction with the child having
          // no control via the joystick.
          if (throttlePwm < 1400 || throttlePwm > 1600) {
            badControlStart = true;
          }
        }

        // reset for the next pulse
        throttleSignalHigh = false;
      }
    }
    
    void getBadStartData(char *buffer) {
      //sprintf(buffer, "%i %i %i %i %i %i %i %i %i %i", throttleStart[0], throttleStart[1], throttleStart[2], throttleStart[3], throttleStart[4], throttleStart[5], throttleStart[6], throttleStart[7], throttleStart[8], throttleStart[9]);
      buffer = "Test";
    }

    
    void getStatus(char * status) {
      sprintf(status, "[RemoteControl] throttleRaw:%lu throttleScaled:%i steeringRaw:%lu steeringScaled:%i isActive:%s Bad Start:%s Has Centered: %s",
        throttlePwm,
        throttleScaled,
        steeringPwm,
        steeringScaled,
        isActive() ? "true" : "false",
        badControlStart ? "true" : "false",
        hasCentered ? "true" : "false");
    }  
};

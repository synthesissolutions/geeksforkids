#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);

#define BUTTON_A  9
#define BUTTON_B  6
#define BUTTON_C  5

#define PIN_JOYSTICK_STEERING 17
#define PIN_JOYSTICK_THROTTLE 16
#define PIN_RC_STEERING       11
#define PIN_RC_THROTTLE       10
#define PIN_SOUND_1           7
#define PIN_SOUND_2           8

int throttle = 0;
int steering = 0;

int rcThrottle = 0;
int rcSteering = 0;

bool isAnalog = true;
bool showRc = false;

int joystickSteeringPwm = 0;
bool joystickSteeringSignalHigh = false;
int joystickSteeringPulseStart = 0;

int joystickThrottlePwm = 0;
bool joystickThrottleSignalHigh = false;
int joystickThrottlePulseStart = 0;

int rcSteeringPwm = 0;
bool rcSteeringSignalHigh = false;
int rcSteeringPulseStart = 0;

int rcThrottlePwm = 0;
bool rcThrottleSignalHigh = false;
int rcThrottlePulseStart = 0;

void setup() {
  Serial.begin(115200);
  
  display.begin(0x3C, true); // Address 0x3C default
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  display.setRotation(1);

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  pinMode(PIN_SOUND_1, INPUT_PULLUP);
  pinMode(PIN_SOUND_2, INPUT_PULLUP);

  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.print("A - Analog (default)");
  display.setCursor(0, 15);
  display.print("B - PWM");
  display.setCursor(0, 30);
  display.print("C - Show RC");
  
  display.display();

  delay(3000);

  display.clearDisplay();
    
  // text display tests
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.print("Throttle");
  display.setCursor(0, 15);
  display.print("Steering");

  display.setCursor(0, 30);
  display.print("Sound 1");
  display.setCursor(0, 45);
  display.print("Sound 2");

  display.setCursor(110, 0);
  display.print("RC");
  display.setCursor(110, 15);
  display.print("RC");

  display.display();

  attachInterrupt(digitalPinToInterrupt(PIN_JOYSTICK_STEERING), &joystickSteeringIRQHandler, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_JOYSTICK_THROTTLE), &joystickThrottleIRQHandler, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_RC_STEERING), &rcSteeringIRQHandler, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_RC_THROTTLE), &rcThrottleIRQHandler, CHANGE);   
}

void loop() {
  if(!digitalRead(BUTTON_A)) {
    isAnalog = true;
  }
  if(!digitalRead(BUTTON_B)) {
    isAnalog = false;
  }
  if(!digitalRead(BUTTON_C)) { 
    showRc = true;
  }

  display.fillRect(53, 0, 53, 60, SH110X_BLACK);

  if (isAnalog) {
    throttle = analogRead(PIN_JOYSTICK_THROTTLE);
    steering = analogRead(PIN_JOYSTICK_STEERING);
  } else {
    throttle = joystickThrottlePwm;
    steering = joystickSteeringPwm;    
  }

  display.setCursor(53, 0);
  display.print(throttle);

  display.setCursor(53, 15);
  display.print(steering);

  if (showRc) {
    display.setCursor(83, 0);
    display.print(rcThrottlePwm);
  
    display.setCursor(83, 15);
    display.print(rcSteeringPwm);  
  }

  if (!digitalRead(PIN_SOUND_1)) {
    display.setCursor(53, 30);
    display.print("On");
  } else {
    display.setCursor(53, 30);
    display.print("Off");
  } 

  if (!digitalRead(PIN_SOUND_2)) {
    display.setCursor(53, 45);
    display.print("On");
  } else {
    display.setCursor(53, 45);
    display.print("Off");
  }

  display.display();
  delay(100);
}

void joystickSteeringIRQHandler() {
  if(digitalRead(PIN_JOYSTICK_STEERING) == 1){
    if (!joystickSteeringSignalHigh) {
      // rising edge of the PWM signal
      // record when the pulse started
      joystickSteeringPulseStart = micros();
      joystickSteeringSignalHigh = true;
    }
  } else if (joystickSteeringSignalHigh) {
    // falling edge of the PWM signal
    // record the duty cycle in microseconds
    joystickSteeringPwm = micros() - joystickSteeringPulseStart;

    // reset for the next pulse
    joystickSteeringSignalHigh = false;
  }
}

void joystickThrottleIRQHandler() {
  if(digitalRead(PIN_JOYSTICK_THROTTLE) == 1){
    if (!joystickThrottleSignalHigh) {
      // rising edge of the PWM signal
      // record when the pulse started
      joystickThrottlePulseStart = micros();
      joystickThrottleSignalHigh = true;
    }
  } else if (joystickThrottleSignalHigh) {
    // falling edge of the PWM signal
    // record the duty cycle in microseconds
    joystickThrottlePwm = micros() - joystickThrottlePulseStart;

    // reset for the next pulse
    joystickThrottleSignalHigh = false;
  }
}

void rcSteeringIRQHandler() {
  if(digitalRead(PIN_RC_STEERING) == 1){
    if (!rcSteeringSignalHigh) {
      // rising edge of the PWM signal
      // record when the pulse started
      rcSteeringPulseStart = micros();
      rcSteeringSignalHigh = true;
    }
  } else if (rcSteeringSignalHigh) {
    // falling edge of the PWM signal
    // record the duty cycle in microseconds
    rcSteeringPwm = micros() - rcSteeringPulseStart;

    // reset for the next pulse
    rcSteeringSignalHigh = false;
  }
}

void rcThrottleIRQHandler() {
  if(digitalRead(PIN_RC_THROTTLE) == 1){
    if (!rcThrottleSignalHigh) {
      // rising edge of the PWM signal
      // record when the pulse started
      rcThrottlePulseStart = micros();
      rcThrottleSignalHigh = true;
    }
  } else if (rcThrottleSignalHigh) {
    // falling edge of the PWM signal
    // record the duty cycle in microseconds
    rcThrottlePwm = micros() - rcThrottlePulseStart;

    // reset for the next pulse
    rcThrottleSignalHigh = false;
  }
}

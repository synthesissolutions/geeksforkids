#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define TFT_CS        7
#define TFT_RST       40 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC        39
#define TFT_BACKLIGHT 45

#define BUTTON_A  5
#define BUTTON_B  6

#define PIN_JOYSTICK_STEERING A3
#define PIN_JOYSTICK_THROTTLE A1
#define PIN_RC_STEERING       12
#define PIN_RC_THROTTLE       13
#define PIN_SOUND_1           A4
#define PIN_SOUND_2           A0
#define PIN_ACTIVE_SWITCH     A2

Adafruit_ST7789 display = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

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

  // Pin 45 is the backlight pin, set to 1 to get full brightness - uses PWM signal for other brightness levels?
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, 1);

  display.init(135, 240);
  display.setRotation(1);
  
  display.fillScreen(ST77XX_BLACK);
  delay(1000);

  display.setRotation(1);

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);

  pinMode(PIN_SOUND_1, INPUT_PULLUP);
  pinMode(PIN_SOUND_2, INPUT_PULLUP);

  pinMode(PIN_ACTIVE_SWITCH, INPUT_PULLDOWN);

  display.setTextSize(2);
  display.setTextColor(ST77XX_WHITE);
  display.setCursor(0, 0);
  display.print("A - Analog (default)");
  display.setCursor(0, 30);
  display.print("B - PWM");
  display.setCursor(0, 60);
  display.print("C - Show RC");

  delay(3000);

  display.fillScreen(ST77XX_BLACK);

  // text display tests
  display.setTextSize(2);
  display.setTextColor(ST77XX_WHITE);
  display.setCursor(0, 0);
  display.print("Throttle");
  display.setCursor(0, 28);
  display.print("Steering");

  display.setCursor(0, 56);
  display.print("Sound 1");
  display.setCursor(0, 84);
  display.print("Sound 2");

  display.setCursor(0, 112);
  display.print("Active");

  display.setCursor(180, 0);
  display.print("RC");
  display.setCursor(180, 28);
  display.print("RC");

  attachInterrupt(digitalPinToInterrupt(PIN_JOYSTICK_STEERING), &joystickSteeringIRQHandler, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_JOYSTICK_THROTTLE), &joystickThrottleIRQHandler, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_RC_STEERING), &rcSteeringIRQHandler, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_RC_THROTTLE), &rcThrottleIRQHandler, CHANGE);   
}

void loop() {
  if(!digitalRead(BUTTON_A)) {
    Serial.println("Button A Pressed");
    isAnalog = true;
  }
  if(!digitalRead(BUTTON_B)) {
    Serial.println("Button B Pressed");
    isAnalog = false;
  }

  display.fillRect(106, 0, 106, 130, ST77XX_BLACK);

  if (isAnalog) {
    throttle = analogRead(PIN_JOYSTICK_THROTTLE);
    steering = analogRead(PIN_JOYSTICK_STEERING);

    throttle = map(throttle, 0, 4095, 0, 1023);
    steering = map(steering, 0, 4095, 0, 1023);
  } else {
    throttle = joystickThrottlePwm;
    steering = joystickSteeringPwm;    
  }

  display.setCursor(106, 0);
  display.print(throttle);

  display.setCursor(106, 28);
  display.print(steering);

  if (showRc) {
    display.setCursor(83, 0);
    display.print(rcThrottlePwm);
  
    display.setCursor(83, 28);
    display.print(rcSteeringPwm);  
  }

  if (!digitalRead(PIN_SOUND_1)) {
    display.setCursor(106, 56);
    display.print("On");
  } else {
    display.setCursor(106, 56);
    display.print("Off");
  } 

  if (!digitalRead(PIN_SOUND_2)) {
    display.setCursor(106, 84);
    display.print("On");
  } else {
    display.setCursor(106, 84);
    display.print("Off");
  }

  if (digitalRead(PIN_ACTIVE_SWITCH)) {
    display.setCursor(106, 112);
    display.print("On");
  } else {
    display.setCursor(106, 112);
    display.print("Off");
  }

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
      showRc = true;
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

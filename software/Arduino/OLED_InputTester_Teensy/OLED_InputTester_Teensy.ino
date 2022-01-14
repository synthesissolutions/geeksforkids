#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

Adafruit_SH110X display = Adafruit_SH110X(64, 128, &Wire);

// OLED FeatherWing buttons map to different pins depending on board:
#if defined(ESP8266)
  #define BUTTON_A  0
  #define BUTTON_B 16
  #define BUTTON_C  2
#elif defined(ESP32)
  #define BUTTON_A 15
  #define BUTTON_B 32
  #define BUTTON_C 14
#elif defined(ARDUINO_STM32_FEATHER)
  #define BUTTON_A PA15
  #define BUTTON_B PC7
  #define BUTTON_C PC5
#elif defined(TEENSYDUINO)
  #define BUTTON_A  4
  #define BUTTON_B  3
  #define BUTTON_C  8
#elif defined(ARDUINO_NRF52832_FEATHER)
  #define BUTTON_A 31
  #define BUTTON_B 30
  #define BUTTON_C 27
#else // 32u4, M0, M4, nrf52840 and 328p
  #define BUTTON_A  9
  #define BUTTON_B  6
  #define BUTTON_C  5
#endif

int throttle = 0;
int steering = 0;

int rcThrottle = 0;
int rcSteering = 0;

void setup() {
  Serial.begin(115200);

  Serial.println("128x64 OLED FeatherWing test");
  display.begin(0x3C, true); // Address 0x3C default

  Serial.println("OLED begun");
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  display.setRotation(1);
  Serial.println("Button test");

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);

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

  display.display(); // actually display all of the above
}

void loop() {
  if(!digitalRead(BUTTON_A)) {
    display.print("a");
  }
  if(!digitalRead(BUTTON_B)) {
    display.print("b");
  }
  if(!digitalRead(BUTTON_C)) { 
    display.print("c");
  }


  display.fillRect(60, 0, 50, 60, SH110X_BLACK);
  throttle = analogRead(A2);
  steering = analogRead(A3);
  display.setCursor(60, 0);
  display.print(throttle);

  display.setCursor(60, 15);
  display.print(steering);

  rcSteering = analogRead(A4);
  rcThrottle = analogRead(A5);
  display.setCursor(90, 0);
  display.print(rcThrottle);

  display.setCursor(90, 15);
  display.print(rcSteering);

  if (!digitalRead(7)) {
    display.setCursor(60, 30);
    display.print("On");
  } else {
    display.setCursor(60, 30);
    display.print("Off");
  }

  if (!digitalRead(8)) {
    display.setCursor(60, 45);
    display.print("On");
  } else {
    display.setCursor(60, 45);
    display.print("Off");
  }

  display.display();
  delay(100);
}

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

//  The overall fire brightness
//  (this can affect both color levels and power consumption)
int brightness = 250;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

Adafruit_NeoPixel wingStrip = Adafruit_NeoPixel(30, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel boosterStrip = Adafruit_NeoPixel(24, 5, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.
// For the ultimate NeoPixel guide, check out:
// https://learn.adafruit.com/adafruit-neopixel-uberguide/overview

void setup() {
  wingStrip.begin();
  wingStrip.setBrightness(brightness);
  wingStrip.show(); // Initialize all pixels to 'off'

  boosterStrip.begin();
  boosterStrip.setBrightness(brightness);
  boosterStrip.show(); // Initialize all pixels to 'off'
}

void fireAnimation(Adafruit_NeoPixel *strip, int brightness) {
  //  Regular (orange) flame:
  int r = 226, g = 50, b = 0;

  //  Purple flame:
  //  int r = 158, g = 8, b = 148;

  //  Green flame:
  //int r = 74, g = 150, b = 12;

  //  Flicker, based on our initial RGB values
  for(int i=0; i<strip->numPixels(); i++) {
    int flicker = random(0,75);
    int r1 = r-flicker;
    int g1 = g-flicker;
    int b1 = b-flicker;
    int newBrightness = brightness - flicker;
    strip->setBrightness(newBrightness);
    if(g1<0) g1=0;
    if(r1<0) r1=0;
    if(b1<0) b1=0;
    strip->setPixelColor(i, r1, g1, b1);
  }
  
  strip->show();
}

int wingAnimation(Adafruit_NeoPixel *strip, int animationStep, bool tipOn) {
  int wingPixelCount = strip->numPixels() / 2;
  for (int j = 0; j < wingPixelCount - 1; j++) {
    if (j == animationStep) {
      strip->setPixelColor(j, 0, 0, 255);
    } else if (j == animationStep - 1) {
      strip->setPixelColor(j, 0, 0, 150);
    } else if (j == animationStep - 2) {
      strip->setPixelColor(j, 0, 0, 50);
    } else {
      strip->setPixelColor(j, 0, 0, 0);
    }
  }

  for (int j = wingPixelCount; j < strip->numPixels() - 1; j++) {
    if (j - wingPixelCount == animationStep) {
      strip->setPixelColor(j, 0, 0, 255);
    } else if (j - wingPixelCount == animationStep - 1) {
      strip->setPixelColor(j, 0, 0, 150);
    } else if (j - wingPixelCount == animationStep - 2) {
      strip->setPixelColor(j, 0, 0, 50);
    } else {
      strip->setPixelColor(j, 0, 0, 0);
    }
  }
  if (tipOn) {
    strip->setPixelColor(wingPixelCount - 1, 255, 0, 0);      
    strip->setPixelColor(strip->numPixels() - 1, 0, 0, 0);            
  } else {
    strip->setPixelColor(wingPixelCount - 1, 0, 0, 0);      
    strip->setPixelColor(strip->numPixels() - 1, 0, 255, 0);            
  }
  
  strip->show();

  if (animationStep < wingPixelCount) {
    return animationStep + 1;
  } else {
    return 0;
  }
}

int wingAnimationStep = 0;
bool wingTipOn = true;
int wingTipCount = 0;

void loop() {
  if (wingTipCount >= 5) {
    wingTipCount = 0;
    wingTipOn = !wingTipOn;
  } else {
    wingTipCount++;
  }
  
  wingAnimationStep = wingAnimation(&wingStrip, wingAnimationStep, wingTipOn);
  fireAnimation(&boosterStrip, 200);
  
  delay (100);
}

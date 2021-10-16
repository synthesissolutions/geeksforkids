#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

//  The overall fire brightness
//  (this can affect both color levels and power consumption)
int brightness = 250;
int frontAnimationStep = 0;
int rearAnimationStep = 0;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

Adafruit_NeoPixel rearStrip = Adafruit_NeoPixel(15, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel frontStrip = Adafruit_NeoPixel(39, 6, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.
// For the ultimate NeoPixel guide, check out:
// https://learn.adafruit.com/adafruit-neopixel-uberguide/overview

void setup() {
  rearStrip.begin();
  rearStrip.setBrightness(brightness);
  rearStrip.show(); // Initialize all pixels to 'off'

  frontStrip.begin();
  frontStrip.setBrightness(brightness);
  frontStrip.show(); // Initialize all pixels to 'off'

  //delay(200);
  //boosterInitialize(&boosterStrip, 240);
  //delay(100);
}

int rearAnimation1(Adafruit_NeoPixel *strip, int brightness, int animationStep) {
  for(int i=0; i< strip->numPixels(); i++) {
    strip->setPixelColor(i, 0, 0, 255);      
  }
  
  strip->show();

  return 0;
}

int rearAnimation2(Adafruit_NeoPixel *strip, int brightness, int animationStep) {
  for(int i=0; i< strip->numPixels(); i++) {
    strip->setPixelColor(i, 255, 0, 0);
  }
  
  strip->show();
  
  return 0;
}

int rearAnimation3(Adafruit_NeoPixel *strip, int brightness, int animationStep) {
  if (animationStep < 4) {
    for(int i=0; i< strip->numPixels(); i++) {
      if (i < strip->numPixels() / 2) {
        strip->setPixelColor(i, 255, 0, 0);        
      } else {
        strip->setPixelColor(i, 0, 0, 255);
      }
    }    
  } else {
    for(int i=0; i< strip->numPixels(); i++) {
      if (i < strip->numPixels() / 2) {
        strip->setPixelColor(i, 0, 0, 255);
      } else {
        strip->setPixelColor(i, 255, 0, 0);        
      }
    }        
  }
  
  strip->show();

  if (animationStep < 8) {
    return animationStep + 1;
  } else {
    return 0;
  }
}

int frontAnimation1(Adafruit_NeoPixel *strip, int animationStep) {
  int numPixels = strip->numPixels();
  for (int j = 0; j < numPixels; j++) {
    if (j < numPixels / 2) {
      strip->setPixelColor(j, 255, 0, 0);      
    } else {
      strip->setPixelColor(j, 0, 0, 255);      
    }
  }
  
  strip->show();

  if (animationStep < strip->numPixels()) {
    return animationStep + 1;
  } else {
    return 0;
  }
}

int frontAnimation2(Adafruit_NeoPixel *strip, int animationStep) {  
  int numPixels = strip->numPixels();

  if (animationStep < 4) {
    for (int j = 0; j < numPixels; j++) {
      if (j < numPixels / 2) {
        strip->setPixelColor(j, 255, 0, 0);      
      } else {
        strip->setPixelColor(j, 0, 0, 255);      
      }
    }    
  } else {
    for (int j = 0; j < numPixels; j++) {
      if (j < numPixels / 2) {
        strip->setPixelColor(j, 0, 0, 255);      
      } else {
        strip->setPixelColor(j, 255, 0, 0);      
      }
    }        
  }

  strip->show();

  if (animationStep < 8) {
    return animationStep + 1;
  } else {
    return 0;
  }
}

int frontAnimation3(Adafruit_NeoPixel *strip, int animationStep) {  
  int numPixels = strip->numPixels();

  for (int j = 0; j < (numPixels / 2); j++) {
    if (j == animationStep) {
      strip->setPixelColor(j, 0, 0, 255);
      strip->setPixelColor(numPixels - j - 1, 255, 0, 0);
    } else if (j == animationStep - 1) {
      strip->setPixelColor(j, 0, 0, 150);
      strip->setPixelColor(numPixels - j - 1, 150, 0, 0);
    } else if (j == animationStep - 2) {
      strip->setPixelColor(j, 0, 0, 50);
      strip->setPixelColor(numPixels - j - 1, 50, 0, 0);
    } else {
      strip->setPixelColor(j, 0, 0, 0);
      strip->setPixelColor(numPixels - j - 1, 0, 0, 0);
    }
  }

  strip->show();

  if (animationStep < numPixels / 2) {
    return animationStep + 1;
  } else {
    return 0;
  }
}

int loopCount = 0;

void loop() {
  if (loopCount < 100) {
    frontAnimationStep = frontAnimation3(&frontStrip, frontAnimationStep);
    rearAnimationStep = rearAnimation3(&rearStrip, 200, rearAnimationStep);
  } else if (loopCount < 200) {
    frontAnimationStep = frontAnimation2(&frontStrip, frontAnimationStep);    
    rearAnimationStep = rearAnimation2(&rearStrip, 200, rearAnimationStep);
  } else {
    frontAnimationStep = frontAnimation1(&frontStrip, frontAnimationStep);    
    rearAnimationStep = rearAnimation1(&rearStrip, 200, rearAnimationStep);
  }
  
  delay (100);
  if (loopCount < 300) {
    loopCount++;    
  } else {
    loopCount = 0;
  }
}

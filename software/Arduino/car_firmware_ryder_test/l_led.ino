/**
 * Led Class
 * 
 * This class provides an interface to the 3 NeoPixels and 2 External LED strips
 */

#include <Adafruit_NeoPixel.h>

#define NUMPIXELS     3
#define ERROR_PIXEL   0
#define STATUS_PIXEL  1
#define POWER_PIXEL   2

Adafruit_NeoPixel pixels(NUMPIXELS, PIN_INDICATOR_LED_DIN, NEO_GRB + NEO_KHZ800);

class Led {
  private:
  
  public:
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).
    Led() {
    }

    /*
     * init - initialize the joystick instance with the pins for x and y axes
     */
    void init() {
      pixels.begin();
      pixels.clear();
    }

    void setErrorPixel(uint8_t r, uint8_t g, uint8_t b) {
      pixels.setPixelColor(ERROR_PIXEL, pixels.Color(r, g, b));
    }

    void clearErrorPixel() {
      pixels.setPixelColor(ERROR_PIXEL, pixels.Color(0, 0, 0));
    }

    void setStatusPixel(uint8_t r, uint8_t g, uint8_t b) {
      pixels.setPixelColor(STATUS_PIXEL, pixels.Color(r, g, b));
    }

    void clearStatusPixel() {
      pixels.setPixelColor(STATUS_PIXEL, pixels.Color(0, 0, 0));
    }

    void setPowerPixel(uint8_t r, uint8_t g, uint8_t b) {
      pixels.setPixelColor(POWER_PIXEL, pixels.Color(r, g, b));
    }

    void clearPowerPixel() {
      pixels.setPixelColor(POWER_PIXEL, pixels.Color(0, 0, 0));
    }

    void showPixels() {
      pixels.show();
    }
};

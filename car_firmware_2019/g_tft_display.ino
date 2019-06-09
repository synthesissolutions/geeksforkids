#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

/**
 * TFTDisplay Class
 * 
 * This class serves to be the interface to the ILI9341 TFT Display
 */

class TFTDisplay {
  private:

    Adafruit_ILI9341 tft = Adafruit_ILI9341(PIN_TFT_CS, PIN_TFT_DC, PIN_TFT_MOSI, PIN_TFT_CLK, PIN_TFT_RST, PIN_TFT_MISO);;

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    TFTDisplay() {  
    }

    /*
     * init - initialize the TFT Display
     */
    void init(int cs, int dc, int mosi, int clock, int reset, int miso) {
      tft.begin();
      tft.setRotation(1);
    }

    /*
     * Display functions for the TFT Display
     */
    void clearScreenBlack() {
      fillScreen(ILI9341_BLACK);
    }

    void fillScreen(int color) {
        tft.fillScreen(color);
        yield();
    }

    void setCursor(int x, int y) {
      tft.setCursor(x, y);
    }

    void print(int textSize, int textColor, String text) {
        tft.setTextColor(textColor);
        tft.setTextSize(textSize);
        tft.print(text);
    }
    
    void println(int textSize, int textColor, String text) {
        tft.setTextColor(textColor);
        tft.setTextSize(textSize);
        tft.println(text);
    }

    String getStatus() {
      String ret = String("[TFT] ");
      
      uint8_t x = tft.readcommand8(ILI9341_RDMODE);
      ret.concat(String("Display Power Mode: 0x"));ret.concat(String(x, HEX));

      x = tft.readcommand8(ILI9341_RDMADCTL);
      ret.concat(String(" MADCTL Mode: 0x"));ret.concat(String(x, HEX));

      x = tft.readcommand8(ILI9341_RDPIXFMT);
      ret.concat(String(" Pixel Format: 0x"));ret.concat(String(x, HEX));

      x = tft.readcommand8(ILI9341_RDIMGFMT);
      ret.concat(String(" Image Format: 0x"));ret.concat(String(x, HEX));

      x = tft.readcommand8(ILI9341_RDSELFDIAG);
      ret.concat(String(" Self Diagnostic: 0x"));ret.concat(String(x, HEX)); 

      return ret;
    }
};

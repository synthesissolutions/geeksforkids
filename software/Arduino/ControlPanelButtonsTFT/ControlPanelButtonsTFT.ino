#include <Wire.h>
#include <SPI.h>
#include <PCA9557.h>

// Arduino IDE Settings need to compile properly
// Partition Scheme: Huge App
// PSRAM: OPI PSRAM

/*******************************************************************************
   Config the display panel and touch panel in gfx_conf.h
 ******************************************************************************/
#include "gfx_conf.h"
#include "TAMC_GT911.h"

#define TOUCH_GT911
#define TOUCH_GT911_SCL 20//20
#define TOUCH_GT911_SDA 19//19
#define TOUCH_GT911_INT -1//-1
#define TOUCH_GT911_RST -1//38
#define TOUCH_GT911_ROTATION ROTATION_NORMAL
#define TOUCH_MAP_X1 800//480
#define TOUCH_MAP_X2 0
#define TOUCH_MAP_Y1 480//272
#define TOUCH_MAP_Y2 0

// The touch event is not constant. So we need
// a delay to check for additional non-sequential touch events
#define RELEASE_DELAY 40
#define SERIAL_MESSAGE_DELAY 10

TAMC_GT911 tp = TAMC_GT911(TOUCH_GT911_SDA, TOUCH_GT911_SCL, TOUCH_GT911_INT, TOUCH_GT911_RST, max(TOUCH_MAP_X1, TOUCH_MAP_X2), max(TOUCH_MAP_Y1, TOUCH_MAP_Y2));

int touch_last_x = 0, touch_last_y = 0;

PCA9557 Out;

bool leftPressed = false;
long lastLeftPressed = 0;
bool rightPressed = false;
long lastRightPressed = 0;
bool goPressed = false;
long lastGoPressed = 0;
bool sound1Pressed = false;
long lastSound1Pressed = 0;
bool sound2Pressed = false;
long lastSound2Pressed = 0;

long lastSerialMessageSent = 0;

void setup()
{
  Serial.begin(9600);

  Wire.begin(TOUCH_GT911_SDA, TOUCH_GT911_SCL);
  tp.begin();
  tp.setRotation(TOUCH_GT911_ROTATION);
  
  Out.reset();
  Out.setMode(IO_OUTPUT);
  Out.setState(IO0, IO_LOW);
  Out.setState(IO1, IO_LOW);
  delay(20);
  Out.setState(IO0, IO_HIGH);
  delay(100);
  Out.setMode(IO1, IO_INPUT);

  //Display Prepare
  tft.begin();
  tft.fillScreen(TFT_BLACK);
  delay(100);

  tft.fillCircle(400, 100, 215, TFT_GREEN);
  tft.fillCircle(0, 420, 220, TFT_BLUE);
  tft.fillCircle(800, 420, 220, TFT_MAGENTA);
  tft.fillCircle(0, 0, 105, TFT_ORANGE);
  tft.fillCircle(800, 0, 105, TFT_SILVER);
}

void loop()
{
  tp.read();
  if (tp.isTouched) {
    touch_last_x = map(tp.points[0].x, TOUCH_MAP_X1, TOUCH_MAP_X2, 0, TOUCH_MAP_X1 - 1);
    touch_last_y = map(tp.points[0].y, TOUCH_MAP_Y1, TOUCH_MAP_Y2, 0, TOUCH_MAP_Y1 - 1);

    //tft.fillCircle(touch_last_x, touch_last_y, 10, TFT_WHITE);

    //Serial.print(touch_last_x);
    //Serial.print(" ");
    //Serial.println(touch_last_y);

    if ((touch_last_x < 620 && touch_last_x > 185) && touch_last_y < 325) {
      lastGoPressed = millis();
      if (!goPressed) {
        goPressed = true;
        
        tft.fillCircle(400, 100, 215, TFT_WHITE);
      }
    }

    if (touch_last_x < 210 && touch_last_y > 210) {
      lastLeftPressed = millis();
      if (!leftPressed) {
        leftPressed = true;
        
        tft.fillCircle(0, 420, 220, TFT_WHITE);
      }
    }

    if (touch_last_x > 590 && touch_last_y > 210) {
      lastRightPressed = millis();
      if (!rightPressed) {
        rightPressed = true;
        
        tft.fillCircle(800, 420, 220, TFT_WHITE);
      }
    }

    if (touch_last_x < 105 && touch_last_y < 115) {
      lastSound1Pressed = millis();
      if (!sound1Pressed) {
        sound1Pressed = true;
        
        tft.fillCircle(0, 0, 105, TFT_WHITE);
      }
    }

    if (touch_last_x > 695 && touch_last_y < 115) {
      lastSound2Pressed = millis();
      if (!sound2Pressed) {
        sound2Pressed = true;
        
        tft.fillCircle(800, 0, 105, TFT_WHITE);
      }      
    }
  } else {
    if (goPressed && (millis() - lastGoPressed) > RELEASE_DELAY) {
        goPressed = false;
       
          tft.fillCircle(400, 100, 215, TFT_GREEN);
    }

    if (leftPressed && (millis() - lastLeftPressed) > RELEASE_DELAY) {
        leftPressed = false;
       
        tft.fillCircle(0, 420, 220, TFT_BLUE);
    }

    if (rightPressed && (millis() - lastRightPressed) > RELEASE_DELAY) {
        rightPressed = false;
       
        tft.fillCircle(800, 420, 220, TFT_MAGENTA);
    }

    if (sound1Pressed && (millis() - lastSound1Pressed) > RELEASE_DELAY) {
        sound1Pressed = false;
       
        tft.fillCircle(0, 0, 105, TFT_ORANGE);
    }

    if (sound2Pressed && (millis() - lastSound2Pressed) > RELEASE_DELAY) {
        sound2Pressed = false;
       
        tft.fillCircle(800, 0, 105, TFT_SILVER);
    }

    touch_last_x = 0;
    touch_last_y = 0;
  }

  if (millis() - lastSerialMessageSent > SERIAL_MESSAGE_DELAY) {
    if (goPressed) {
      Serial.println("1");
    } else if (leftPressed) {
      Serial.println("2");
    } else if (rightPressed) {
      Serial.println("3");
    } else if (sound1Pressed) {
      Serial.println("4");
    } else if (sound2Pressed) {
      Serial.println("5");
    } else {
      Serial.println("0");
    }

    lastSerialMessageSent = millis();
  }
}

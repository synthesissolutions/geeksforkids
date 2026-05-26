#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h> 

#define BUF_LEN 8

#define X_DEF 512
#define Y_DEF 512
#define BTN_DEF 0

class Joystick {
  public:
    Joystick(int xAxisPin, int yAxisPin, int btnPin);
    void begin(void);
    void read(void);
    int x;
    int y;
    int b;

  private:
    int xAxis;
    int yAxis;
    int btn;
    int xBuf[BUF_LEN] = {X_DEF};
    int yBuf[BUF_LEN] = {Y_DEF};
    int bBuf[BUF_LEN] = {BTN_DEF};
};

#endif

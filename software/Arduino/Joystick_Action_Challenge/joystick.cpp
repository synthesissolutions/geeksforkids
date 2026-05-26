
#include "joystick.h"

Joystick::Joystick(int xAxisPin, int yAxisPin, int btnPin) {
  //x and y axes are analog, btn digital
  xAxis = xAxisPin;
  yAxis = yAxisPin;
  btn = btnPin;
  
}

void Joystick::begin() {
  pinMode(btn, INPUT);
}

void Joystick::read() {
  int xRaw = analogRead(xAxis);
  int yRaw = analogRead(yAxis);
  int bRaw = !digitalRead(btn); //button is active low

  int xSum = 0;
  int ySum = 0;
  int bSum = 0;

  //fill shift buffers
  for (int i = BUF_LEN - 1; i >= 0; i--) {
    if (i == 0) {
      xBuf[i] = xRaw;
      yBuf[i] = yRaw;
      bBuf[i] = bRaw;
    } else {
    xBuf[i] = xBuf[i-1];
    yBuf[i] = yBuf[i-1];
    bBuf[i] = bBuf[i-1];
    }
    xSum += xBuf[i];
    ySum += yBuf[i];
    bSum += bBuf[i];
  }

  //average x and y axes
  x = xSum / BUF_LEN;
  y = ySum / BUF_LEN;

  //debounce button (only reads high if all entries in buffer are high)
  b = bSum == BUF_LEN;
}

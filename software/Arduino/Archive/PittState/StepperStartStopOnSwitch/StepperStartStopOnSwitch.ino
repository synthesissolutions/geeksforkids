// ConstantSpeed.pde
// -*- mode: C++ -*-
//
// Shows how to run AccelStepper in the simplest,
// fixed speed mode with no accelerations
/// \author  Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2009 Mike McCauley
// $Id: ConstantSpeed.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

AccelStepper stepper = AccelStepper(AccelStepper::DRIVER, 6, 4); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5

boolean isRunning = false;
int minDelay = 250;
unsigned long lastAction = 0;

void setup()
{
  Serial.begin(115200);
  while (! Serial) delay(10);

  Serial.println("Start AccelStepper Test");
  
  pinMode(A0, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);

  digitalWrite(3, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(7, HIGH);

   stepper.setEnablePin(2);
   stepper.setMaxSpeed(1000);
   stepper.enableOutputs();
   stepper.setPinsInverted();
   stepper.setSpeed(1000);
}

void loop()
{
  if (millis() - minDelay > lastAction) {
    if (isRunning && !digitalRead(A0)) {
      // we are running but the switch was closed so we need to stop
      Serial.println("Stop running");
      lastAction = millis();
      isRunning = false;
      stepper.stop();
    } else if (!isRunning && !digitalRead(A0)) {
      // we are not running and the switch was closed so we need to start
      Serial.println("Start running");
      lastAction = millis();
      isRunning = true;
      stepper.setSpeed(1000);
    }
  } else {
    // do nothing wait a bit long for input to avoid bouncing
  }

  if (isRunning) {
    stepper.runSpeed();
  }
}

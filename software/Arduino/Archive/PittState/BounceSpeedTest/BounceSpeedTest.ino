// Bounce.pde
// -*- mode: C++ -*-
//
// Make a single stepper bounce from one limit to another
//
// Copyright (C) 2012 Mike McCauley
// $Id: Random.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

#define PULSE_PIN     4
#define DIR_PIN       3
#define ENABLE_PIN    2

#define STEPS_PER_ROTATION        400
#define MOVEMENT_RANGE_DEGREES    90.0
#define SPEED                     50

int rangeSteps = (MOVEMENT_RANGE_DEGREES / 360.0) * STEPS_PER_ROTATION;
int maxPosition = rangeSteps / 2;
int minPostion = -maxPosition;
int currentSpeed = SPEED;
int currentTarget = maxPosition;

AccelStepper stepper = AccelStepper(AccelStepper::DRIVER, PULSE_PIN, DIR_PIN);  

void setup()
{  
  // Change these to suit your stepper if you want
  stepper.setMaxSpeed(SPEED);
  stepper.setSpeed(currentSpeed);
}

void loop()
{
    long currentPosition = stepper.currentPosition();

    if (currentPosition == currentTarget) {
      stepper.stop();

      delay(1000);
      currentSpeed = -currentSpeed;
      stepper.setSpeed(currentSpeed);
      currentTarget = -currentTarget;
    }

    stepper.runSpeed();
}

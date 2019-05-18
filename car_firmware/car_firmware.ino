#define PIN_RC_STEERING            3         // INPUT -- steering
#define PIN_RC_THROTTLE            2         // INPUT -- throttle
#define PIN_ESC_STEERING           10        // OUTPUT
#define PIN_ESC_THROTTLE           9         // OUTPUT
#define USE_JOYSTICK_STEERING      false
#define PIN_JOYSTICK_STEERING      A0        // INPUT
#define USE_JOYSTICK_THROTTLE      false
#define PIN_JOYSTICK_THROTTLE      A1        // INPUT
#define PIN_LINACT_STEERING        A2        // INPUT: read for linear actuator position
#define USE_GOVERNOR               false
#define PIN_GOVERNOR               A3
#define USE_LEFT                   true
#define PIN_LEFT                   5
#define USE_FWD                    true
#define PIN_FWD                    6
#define USE_RIGHT                  true
#define PIN_RIGHT                  7
#define USE_REVERSE                true
#define PIN_REVERSE                8
#define LINACT_CALIBRATE           false
#define PIN_LINACT_ENABLE          true      // do we use the linear actuator position information?
#define LINACT_MAX                 710
#define LINACT_MIN                 250
#define OVERRIDE_THRESHOLD         100        // the window around resting which the parental controls must be out of in order to override the car controls
#define VELOCITY_INCR              0.35       // this sets the rate at which changes can be made to the PWM output signal -- higher the setting, faster the change
#define OVERRIDE_TIMEOUT           4000     // in millis
unsigned long RC_THROTTLE_GOVERNOR = 0;         // if USE_GOVERNOR = FALSE, this value will be permanently subtracted from top speed (fwd/rev)

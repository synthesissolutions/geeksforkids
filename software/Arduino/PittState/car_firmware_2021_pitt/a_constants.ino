/**
 * CONSTANTS
 * 
 * These values are used throughout the code, but are static and should never be changed at runtime.  
 * 
 * All constants should be either #define or const 
 * 
 */

/*****************************************************************************************
 *  Loger update time and baud rate.  Make sure the rate is set correctly in your serial monitor!
 *  
 *  NOTE turn off logging by setting LOGGER_UPDATE_TIME to 0
 ***************************************************************************************** 
 */

const String        RELEASE_VERSION         = "22.1 Alpha Pitt State";

const int           LOGGER_UPDATE_TIME      = 100;     // How long between updates to the monitor, in milliseconds
const unsigned int  SERIAL_BAUD_RATE        = 57600;     // Baud rate for the serial monitor.  Make sure you set this correctly!
const int           LOGGER_LINE_LENGTH      = 300;
const int           LOGGER_LINE_COUNT       = 20;


/*****************************************************************************************
 * Tuning constants
 ***************************************************************************************** 
 */
// The delay for the main loop.  We really don't want it running at the full CPU speed.
const int           LOOP_DELAY_MILLIS       = 10;   // 10ms delay = ~ 100 Hz.  Plenty fast.

// Joystick parms - these are based on the range 0-1023
// These values should never really be used but are set as a fallback
// the real values should be read from the configuration file
const int           JOYSTICK_X_AXIS_CENTER           = 512;
const int           JOYSTICK_X_AXIS_MIN              = 0;
const int           JOYSTICK_X_AXIS_MAX              = 1020;
const int           JOYSTICK_Y_AXIS_CENTER           = 512;
const int           JOYSTICK_Y_AXIS_MIN              = 0;
const int           JOYSTICK_Y_AXIS_MAX              = 1020;

// Joystick parms - these are in scaled units (-100 to 100)
const int           JOYSTICK_X_AXIS_DEADZONE_LOW     = -15;
const int           JOYSTICK_X_AXIS_DEADZONE_HIGH    = 15;
const int           JOYSTICK_Y_AXIS_DEADZONE_LOW     = -15;
const int           JOYSTICK_Y_AXIS_DEADZONE_HIGH    = 15;

// Joystick parms - get the direction correct
// These values should never really be used but are set as a fallback
// the real values should be read from the configuration file
const boolean       JOYSTICK_INVERT_X_AXIS  = true;
const boolean       JOYSTICK_INVERT_Y_AXIS  = false;

// Throttle parms ... tunes the throttle changes and updates
const unsigned long THROTTLE_UPDATE_MILLIS  = 10;         // 10 = ~ 100Hz.  How often the throttle position is updated.
const float         THROTTLE_CHANGE_RATE    = 200.0;      // Units are scaledUnits/sec.  100.0 means that we can go from full forward to full reverse in 0.5 second. 
const int           THROTTLE_PWM_MIN        = 0;          // Throttle PWM is handled with analogWrite which expects a value from 0 to 255, 0 = stopped, 255 = full speed
const int           THROTTLE_PWM_MAX        = 254;

// Min/Max Speed Configuration
const int           SPEED_CONFIGURATION_MIN_SPEED = 15;   // The min/max settings here control what the min/max speed percentages controlled by the speed potentiometer
const int           SPEED_CONFIGURATION_MAX_SPEED = 100;

// Steering parms ... controls the steering changes
const int           STEERING_MIN            = 25;        // tuned to maximum wheel turn amount
const int           STEERING_CENTER         = 50;
const int           STEERING_MAX            = 75;        // tuned to maximum wheel turn amount
const int           STEERING_STOP_DELTA     = 5;          // How close to target before stopping so we don't oscillate between 2 numbers.  IN SCALED UNITS: -100 to 100
const int           STEERING_START_DELTA    = 10;          // How close to target before starting so we don't oscillate between 2 numbers   IN SCALED UNITS: -100 to 100
const int           STEERING_SPEED          = 240;        // PWM Value from 0 - 254 with 254 = max speed

// Remote control PWM parms ... probably best to leave these alone!
const int           STEERING_RC_MIN         = 1000;
const int           STEERING_RC_CENTER      = 1500;
const int           STEERING_RC_MAX         = 2000;
const int           THROTTLE_RC_MIN         = 1200;
const int           THROTTLE_RC_CENTER      = 1500;
const int           THROTTLE_RC_MAX         = 2000;
const int           RC_LIMIT                = 2500;

// Remote control parm ... tuning
const int           RC_OVERRIDE_TIMEOUT     = 3000;     // The time required for the parent RC input to be at idle before returning control back to the kid, in millis
const int           RC_STEERING_DEADZONE_LOW = -10;     // scaled units
const int           RC_STEERING_DEADZONE_HIGH = 10;     // scaled units
const int           RC_THROTTLE_DEADZONE_LOW = -10;     // scaled units
const int           RC_THROTTLE_DEADZONE_HIGH = 10;     // scaled units 


/*****************************************************************************************
 * pin assignments
 ***************************************************************************************** 
 */
//   ... joystick
const int           PIN_JOYSTICK_STEERING         = A3;
const int           PIN_JOYSTICK_THROTTLE         = A2;

//   ... throttle ... aka the controller for the car's drive motor   
const int           PIN_BRAKE_DIRECTION           = 3;  // Channel 1 on motor controller
const int           PIN_BRAKE_PWM                 = 2;
const int           PIN_THROTTLE_DIRECTION_RIGHT  = 5; // Channel 2 on motor controller
const int           PIN_THROTTLE_PWM_RIGHT        = 4;

const int           PIN_MAX_SPEED                 = A0;

//   ... steering ... aka the controller for the car's steering servo
const int           PIN_STEERING_DIRECTION        = 7;
const int           PIN_STEERING_PWM              = 6;
const int           PIN_STEERING_POSITION         = A1;

//   ... RC ... aka the parent remote control inputs
const int           PIN_RC_STEERING               = 11;   
const int           PIN_RC_THROTTLE               = 10;     

//   ... Configuration Button
const int           PIN_ENABLE_CONFIGURATION_BUTTON   = 9;

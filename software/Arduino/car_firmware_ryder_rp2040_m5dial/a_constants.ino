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

#define             RELEASE_VERSION         "c26.05.1 Alpha"

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

// Joystick parms - these are based on the range 0-1023 for analog controls
//                  200 to 800 for PWM controls
// These values should never really be used but are set as a fallback
// the real values should be read from the configuration file
const int           JOYSTICK_X_AXIS_CENTER           = 500;
const int           JOYSTICK_X_AXIS_MIN              = 200;
const int           JOYSTICK_X_AXIS_MAX              = 800;
const int           JOYSTICK_Y_AXIS_CENTER           = 500;
const int           JOYSTICK_Y_AXIS_MIN              = 200;
const int           JOYSTICK_Y_AXIS_MAX              = 800;

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
const int           THROTTLE_PWM_MAX        = 180;

// Min/Max Speed Configuration
const int           SPEED_CONFIGURATION_MIN_SPEED = 15;   // The min/max settings here control what the min/max speed percentages controlled by the speed potentiometer
const int           SPEED_CONFIGURATION_MAX_SPEED = 100;

// Steering parms ... controls the steering changes
const int           STEERING_MIN            = 25;        // tuned to maximum wheel turn amount
const int           STEERING_CENTER         = 50;
const int           STEERING_MAX            = 75;        // tuned to maximum wheel turn amount
const int           STEERING_STOP_DELTA     = 5;          // How close to target before stopping so we don't oscillate between 2 numbers.  IN SCALED UNITS: -100 to 100
const int           STEERING_START_DELTA    = 10;          // How close to target before starting so we don't oscillate between 2 numbers   IN SCALED UNITS: -100 to 100
const int           STEERING_SPEED          = 100;        // PWM Value from 0 - 254 with 254 = max speed

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

// Battery Voltage Divider
const float         DIVIDER_ONE_VOLT          = 29.9;     // 1v == analog read from voltage divider of 30 out of 1023 from ADC

// I2C Addresses
#define             M5DIAL_I2C_ADDRESS  0x55
//#define             ATTINY_SPEED_CONTROL_I2C_ADDRESS  0x54
//Add I2C Addresses for new devices
#define             GPIO_EXPANDER_I2C_ADDRESS  0x58
#define             TEMP_SENSOR_I2C_ADDRESS  0x49
#define             AUDIO_DAC_I2C_ADDRESS  0x4C

/*****************************************************************************************
 * pin assignments
 ***************************************************************************************** 
 */
//Joystick NEW
const int           PIN_JOYSTICK_STEERING         = 1; //DRIVE_PWM_STEERING
const int           PIN_JOYSTICK_THROTTLE         = 3; //DRIVE_PWM_THROTTLE
#define             PIN_ACTIVE_SWITCH             23  //DRIVE_ACTIVE_SW

// throttle old
//const int           PIN_THROTTLE_DIRECTION_LEFT   = 3;  // Channel 1 on motor controller
//const int           PIN_THROTTLE_PWM_LEFT         = 2;
//const int           PIN_THROTTLE_DIRECTION_RIGHT  = 5; // Channel 2 on motor controller
//const int           PIN_THROTTLE_PWM_RIGHT        = 4;

// throttle NEW
const int           PIN_THROTTLE_DIRECTION_FRONT   = 8; //FRONT_MOTOR_DIR
const int           PIN_THROTTLE_PWM_FRONT         = 10; //FRONT_MOTOR_PWM
const int           PIN_THROTTLE_DIRECTION_REAR  = 4; //REAR_MOTOR_DIR
const int           PIN_THROTTLE_PWM_REAR        = 6; //REAR_MOTOR_PWM

// I2C Old
//#define             PIN_ATTINY_I2C_SDA                    14
//#define             PIN_ATTINY_I2C_SCL                    15

// I2C NEW
#define             PIN_M5DIAL_I2C_SDA                    14 //M5_SDA
#define             PIN_M5DIAL_I2C_SCL                    15 //M5_SCL
#define             PIN_I2C_SDA                           20 //I2C_SDA 
#define             PIN_I2C_SCL                           21 //I2C_SCL

// steering NEW
const int           PIN_STEERING_DIRECTION        = 0; //STEERING_MOTOR_DIR
const int           PIN_STEERING_PWM              = 2; //STERRING_MOTOR_PWM
const int           PIN_STEERING_POSITION         = A1;

// sound NEW
#define             DRIVE_SOUND_A                    22
#define             DRIVE_SOUND_B                    24

// Reverse Switch old --New moved to GPIO EXPANDER
//#define             PIN_REVERSE_SWITCH             18

// RC ... aka the parent remote control inputs NEW
//const int           PIN_RC_STEERING            = 7; //REMOTE_PWM_STEERING
//const int           PIN_RC_THROTTLE            = 5; //REMOTE_PWM_THROTTLE
//const int           PIN_RC_CLOSE_OUT           = 9; //REMOTE_PWM_CLOSE_OUT
//const int           PIN_RC_EXTRA               = 11; //REMOTE_PWM_THROTTLE
// Because of layout issue on PCB, adjusting PIN assignment for RC
const int           PIN_RC_STEERING            = 11; //REMOTE_PWM_STEERING
const int           PIN_RC_THROTTLE            = 9; //REMOTE_PWM_THROTTLE

// GPIO EXPANDER
#define PIN_GPIO_EXPANDER_INT   12 //GPIO_EXPANDER_INT
#define PIN_GPIO_EXPANDER_RST   13 //GPIO_EXPANDER_RST

//AUDIO DAC
#define             PIN_DAC_I2S_BCK          16 //DAC_I2S_BCK
#define             PIN_DAC_I2S_LRCK         17 //DAC_I2S_LRCK
#define             PIN_DAC_I2S_DIN          18 //DAC_I2S_BCK

//INDICATOR LED PIN
#define             PIN_INDICATOR_LED_DIN    19 //LED_DIN

// Battery Voltage Divider
#define             PIN_BATTERY_VOLTAGER_DIVIDER  A2

// PCB Revision Pin
#define             PIN_REVISION_DIVIDER          A3

//SPARE RP2040 PINS
#define             PIN_RP2040_SPARE_1       25 //RP2040_SPARE1
#define             PIN_RP2040_SPARE_2       A0 //RP2040_SPARE2 (Also GPIO26) 

/*****************************************************************************************
 * pin assignments GPIO EXPANDER
 ***************************************************************************************** 
 */
#define             PIN_GPIO_EXP_SW_REVERSE          0 //SW_REVERSE
#define             PIN_GPIO_EXP_SW_FORWARD          1 //SW_FORWORD
#define             PIN_GPIO_EXP_SW_HIGH_LOW         2 //H/L
#define             PIN_GPIO_EXP_SW_ACTION_TRIG2     3 //ACTION_CHALLENGE_TRIG2
#define             PIN_GPIO_EXP_SW_ACTION_TRIG1     4 //ACTION_CHALLENGE_TRIG1
#define             PIN_GPIO_EXP_MOTOR_FAULT         5 //MOTOR_FAULT
#define             PIN_GPIO_EXP_MOTOR_CHOPPING      6 //MOTOR_CHOPPING
#define             PIN_GPIO_EXP_TEMP_ALERT          7 //TEMP_ALRT
#define             PIN_GPIO_EXP_MOTOR_SLEEP         8 //MOTOR_SLEEP
#define             PIN_GPIO_EXP_SPARE               9 //GPIO_EXPANDER_SPARE
#define             PIN_GPIO_EXP_DAC_MUTE            10 //DAC_MUTE
#define             PIN_GPIO_EXP_AMP_SD              11 //AMP_SD
#define             PIN_GPIO_EXP_LOAD_SWITCH_A       12 //LS_A_CTRL
#define             PIN_GPIO_EXP_LOAD_SWITCH_B       13 //LS_A_CTRL
#define             PIN_GPIO_EXP_LOAD_SWITCH_C       14 //LS_A_CTRL
#define             PIN_GPIO_EXP_LOAD_SWITCH_D       15 //LS_A_CTRL

 

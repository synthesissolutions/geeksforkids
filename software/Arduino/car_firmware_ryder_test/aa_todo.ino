
 /*
  * TODO:  Previous code had a "runaway" safety where if the same rc input was detected for too long (something like 2000 samples or 40 seconds) it would
  *         assume the rc input was faulty and ignore it until some kind of change was detected.  Should that still be done?  If so, the best place for
  *         that logic is probably in the isActive code for the remote control.
  *         
  *        The previous code also had an array to keep track of the pwm samples.  I think was was in anticipation of either averaging or doing some
  *         kind of sampling.  That code has not been repeated here.  We need to verify that is OK, and something hasn't been missed.
  */

/*

- add file for Neopixels
  - set pwr neopixel on startup
  - set stat neopixel when car is moving
  - set error neopixel to yellow if no drive system is connected
  - add the ability to show multiple error conditions - changing color each second to cycle through error conditions
- add file and code to deal with setting/reading values from GPIO expander
- figure out sound files/code ...
- enable all power outputs
- set motor sleep at appropriate times?
- read H/L speed from dash and provide getter
- read Forward/Reverse from dash and provide getter
- trigger sounds for sounds A & B from drive system
- trigger sounds from action challenge 1 and 2

 */

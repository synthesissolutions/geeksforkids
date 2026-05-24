
 /*
  * TODO:  Previous code had a "runaway" safety where if the same rc input was detected for too long (something like 2000 samples or 40 seconds) it would
  *         assume the rc input was faulty and ignore it until some kind of change was detected.  Should that still be done?  If so, the best place for
  *         that logic is probably in the isActive code for the remote control.
  *         
  *        The previous code also had an array to keep track of the pwm samples.  I think was was in anticipation of either averaging or doing some
  *         kind of sampling.  That code has not been repeated here.  We need to verify that is OK, and something hasn't been missed.
  */

/*

- set error neopixel to yellow if no drive system is connected
- add the ability to show multiple error conditions - changing color each second to cycle through error conditions - not urgent
- trigger sounds from action challenge 1 and 2 - done? need to verify
- figure out why sound buttons are trigger two sounds
- figure out why the RC is locking out the child drive system permanently
- add configuration to define usage of the forward/reverse/park switch
- update m5dial code to support forward/reverse/park switch configuration
- add back in brake when stopped
- reduce the harsh braking affect while slowing down
- set max speed to 75% power for throttle
- update sound files
- add notes to explain the Arduino Tools menu configuration needed to build, plus versions of all libraries used
- figure out why the SoundProcessing status isn't printing properly - not urgent

 */

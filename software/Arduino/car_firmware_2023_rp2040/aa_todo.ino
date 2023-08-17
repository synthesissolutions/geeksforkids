
 /*
  * TODO:  Previous code had a "runaway" safety where if the same rc input was detected for too long (something like 2000 samples or 40 seconds) it would
  *         assume the rc input was faulty and ignore it until some kind of change was detected.  Should that still be done?  If so, the best place for
  *         that logic is probably in the isActive code for the remote control.
  *         
  *        The previous code also had an array to keep track of the pwm samples.  I think was was in anticipation of either averaging or doing some
  *         kind of sampling.  That code has not been repeated here.  We need to verify that is OK, and something hasn't been missed.
  */

/*

implement check for active pin pulled high
read max speed potentiometer on ATTiny1616
implement I2C on ATTiny to provide max speed when requested

add in options for
  - throttle accelleration rate
  

 */

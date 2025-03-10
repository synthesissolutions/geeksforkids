/**
 * GeeksForKids Car Firmware - 2023
 * 
 * This software is under some licence - maybe MIT?... should be spelled out here.  
 * 
 * 
 * -------------------------------------------------------------
 * 
 * File Orgnaization
 * -----------------
 * 
 * For ease of compatibilty over time, the structure of these files assumes that we're uding the standard 
 * Arduino IDE and compiler.  As such, all of the files in this directory will invisibily put together prior
 * to compilation in the following order:
 * 
 *    A. This file (the file where the name matches the directory name).  THIS FILE IS REQUIRED BY THE ARDUINO IDE
 *    B. All other files, in alphabetical order.
 *    
 *  Based on these rules, all of the actual "code" is contained in the individual files.  The division of the
 *  files and the associated names follow the following rules:
 *  
 *    1. This file (the one that matches the directory name) should contain NO CODE.  It contains license and 
 *         README information only
 *    2. All file names will follow the pattern of "a-filename.ino", where "a" is the compile order, and "filename" 
 *         is a meaningful filename for the code contained
 *    3. "filename" is set to either match the class that it contains, or a functional use.
 *    4. files should remain organized logically ... please avoid undue mixing of code into existing files where
 *         there is no logical connection.
 *    5. The final file in the compile list is called "z_setup_loop".  This is where arduino defined setup and
 *         loop functions are actually defined.  Please don't try and put those anywhere else - otherwise you're likely
 *         to cause compile errors.
 */

/**
   GeeksForKids Car Firmware - 2023

   This software is under some licence - maybe MIT?... should be spelled out here.


   -------------------------------------------------------------

   Arduino Configuration
   ---------------------

   Tested with the following versions
   
   1. Arduino IDE v. 1.8.19
   2. RP2040 Board Manager Earle Philhower III v. 4.5.1
   3. Adafruit NeoPixel Library v. 1.12.3
   4. Adafruit AW9523 GPIO Expander Library v. 1.0.5
   5. Sparkfun TMP102 Temperature Sensor Library v. 1.1.2
   6. Background Audio by Earle Philhower III Library v.1.3.2
   7. Adafruit PCM51xx DAC Library v. 1.0.0


   Tools Menu Configuration
   ------------------------
   
   1. Board: Generic RP2040 - from the RP2040 Board Manager in #2 above.
   2. Unless otherwise menntioned, keep default configuration
   3. Flash Size 16mb - Sketch: 4mb File System: 12mb
   4. Boot Stage 2: W25Q128JV QSPI /4


   Audio File System
   -----------------
   
   1. Download and install the LittleFS plugin to create the filesystem https://github.com/earlephilhower/arduino-pico-littlefs-plugin
   2. Select Pico LittleFS Data Upload from the Tools menu
      This will create the 12mb file system using the files in the Data folder for this Arduino sketch.
      This could take several minutes.
   3. You do not need to recreate the filesystem unless you modify the data folder. You do NOT need to recreate the filesystem if you are
      just updating the Arduino code and deploying to the device unless you accidentally upload the code with the wrong Flash Size settings.


   File Orgnaization
   -----------------

   For ease of compatibilty over time, the structure of these files assumes that we're uding the standard
   Arduino IDE and compiler.  As such, all of the files in this directory will invisibily put together prior
   to compilation in the following order:

      A. This file (the file where the name matches the directory name).  THIS FILE IS REQUIRED BY THE ARDUINO IDE
      B. All other files, in alphabetical order.

    Based on these rules, all of the actual "code" is contained in the individual files.  The division of the
    files and the associated names follow the following rules:

      1. This file (the one that matches the directory name) should contain NO CODE.  It contains license and
           README information only
      2. All file names will follow the pattern of "a-filename.ino", where "a" is the compile order, and "filename"
           is a meaningful filename for the code contained
      3. "filename" is set to either match the class that it contains, or a functional use.
      4. files should remain organized logically ... please avoid undue mixing of code into existing files where
           there is no logical connection.
      5. The final file in the compile list is called "z_setup_loop".  This is where arduino defined setup and
           loop functions are actually defined.  Please don't try and put those anywhere else - otherwise you're likely
           to cause compile errors.
*/


#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include "Wire.h"

DFRobotDFPlayerMini myDFPlayer;

//Input Pins 
const byte noPins = 2;  //Number of pins we are using used for looping through inPins[].
const byte inPins[] = {3,11}; // {PA7,PC1} physical {5,13}
const byte busyPin = 5;  //PB4 physical 7
const byte volPin = 15; //PA1 physical 18
const byte speedPin = 16; //PA3 physical 19

//Input Tracking
byte p[] = {1,1};
byte pOld[] = {1,1};
byte folderSounds[] = {0,0};
byte isBusy = 1;
int volRead = 512; //10 bit int 0-1023
int speedRead = 512; //10 bit int 0-1023

//Outputs Tracking
int volOut = 15; //DFRobot takes 0-30.
int speedOut = 128; //Sent over i2c to Main board convention will be to send 0-255.

void setup() {
  // A delay is required to give the DFRobot Mini MP3 player time to boot up
  delay(100);
  
  // configure pins for input
  for(int i = 0; i < noPins; i++){
    pinMode(inPins[i], INPUT_PULLUP);
  }

  //Configure busy pin
  pinMode(busyPin, INPUT_PULLUP);
  
  Serial.begin(9600);

  if (!myDFPlayer.begin(Serial)) { 
    while(true);
  }
  
  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
  
  //----Set volume----
  myDFPlayer.volume(30);  //Set volume value (0~30).

  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);

  //----Set device we use SD as default----
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

  SetFolderFileCounts();

  //i2c commands for sending speed values.
  Wire.onRequest(SendSpeedReading);   
  Wire.begin(0x54);
}

void loop() {
  ReadInputs();
  SetOutputs();
}


//Loop through the pins and read any button presses.
void ReadInputs(){
  for(int i = 0; i < noPins; i++){
    p[i]=digitalRead(inPins[i]);
  }
  isBusy = digitalRead(busyPin); //busy when busy Pin is Low
  volRead = analogRead(volPin);
  speedRead = analogRead(speedPin);
}

//Trigger sounds based on inputs
void SetOutputs(){
  for(int i = 0; i < noPins; i++){
    if (p[i] == 0 && p[i] != pOld[i]){ //if the value of the pin changed play the sound.
      PlaySound(i+1, random(1,folderSounds[i]+1));
    } 
  } 
  SetOldp(); //Sets current pin values as old.

  volOut = map(volRead,1023,0,0,30); //Map vol pot read to DF Robot range.
  myDFPlayer.volume(volOut); //Set DF Robot volume
  
  speedOut = map(speedRead,0,1023,0,255); //Map speed pot to output.
  //i2c command....
  
}

//Used for simple "Debounce" keeps track of the value last pressed
void SetOldp(){
  for(int i = 0; i < noPins; i++){
    pOld[i] = p[i];
  }
}

//Checks if a sounds is playing then plays a sound folder values 1-99 sound values 1-255
void PlaySound(byte folder, byte sound){
  
  if (isBusy){ //logic is reversed for isBusy 
    myDFPlayer.playFolder(folder, sound);
  }
}

//Reads SD card file counds and saves values into folderSounds array. Runs once during setup.
void SetFolderFileCounts(){
  byte count = 0;
  for(int i = 0; i < noPins; i++){
    count = myDFPlayer.readFileCountsInFolder(i+1);
    folderSounds[i]=count;
  }
}

void SendSpeedReading(){  
  Wire.write((uint8_t) speedOut);
}

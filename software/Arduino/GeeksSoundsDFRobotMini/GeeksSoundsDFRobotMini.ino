 
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include "Wire.h"

DFRobotDFPlayerMini myDFPlayer;

//Input Pins 
const byte noPins = 4;  //Number of pins we are using used for looping through inPins[].
const byte inPins[] = {3,11,1,2}; // {PA7,PC1,PA5,PA6} physical {5,13,6,7}
const byte busyPin = 5;  //PB4 physical 10

//Input Tracking
byte p[] = {1,1,1,1};
byte pOld[] = {1,1,1,1};
byte folderSounds[] = {0,0,0,0};
byte isBusy = 1;
int volume = 35;

//Outputs Tracking
int volOut = 15; //DFRobot takes 0-30.

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
  myDFPlayer.volume(volOut);  //Set volume value (0~30).

  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);

  //----Set device we use SD as default----
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

  SetFolderFileCounts();

  //i2c commands for sending speed values.
  Wire.onReceive(SetVolume);   
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
}

//Trigger sounds based on inputs
void SetOutputs(){
  for(int i = 0; i < noPins; i++){
    if (p[i] == 0 && p[i] != pOld[i]){ //if the value of the pin changed play the sound.
      PlaySound(i+1, random(1,folderSounds[i]+1));
    } 
  } 
  SetOldp(); //Sets current pin values as old.

  volOut = map(volume,0,100,0,30); //Map vol pot read to DF Robot range.
  myDFPlayer.volume(volOut); //Set DF Robot volume
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

void SetVolume(){
  volume = Wire.read();
}

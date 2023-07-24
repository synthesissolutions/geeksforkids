
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

DFRobotDFPlayerMini myDFPlayer;

//Input Pins 
const byte noPins = 2;
const byte inPins[] = {6,7};
const byte busyPin = 10;

//Input Tracking
byte p[] = {1,1};
byte pOld[] = {1,1};
byte folderSounds[] = {0,0};
byte isBusy = 1;

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
  myDFPlayer.volume(15);  //Set volume value (0~30).

  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);

  //----Set device we use SD as default----
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);

  SetFolderFileCounts();
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
    if (p[i] == 0 && p[i] != pOld[i]){
      PlaySound(i+1, random(1,folderSounds[i]+1));
    } 
  }
 
  SetOldp();
}

//Used for simple "Debounce" keeps track of the value last pressed
void SetOldp(){
  for(int i = 0; i < noPins; i++){
    pOld[i] = p[i];
  }
}

//Checks if a sounds is playing then plays a sound folder values 1-99 sound values 1-255
void PlaySound(byte folder, byte sound){
  if (isBusy){
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

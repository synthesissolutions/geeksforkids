
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

DFRobotDFPlayerMini myDFPlayer;

//Uncomment DEBUG to use Serial2 for DFRobot and Serial to debug
//#define DEBUG
//Uncomment ATTINY to use only Serial for DFRobot
#define ATTINY

//Input Pins 
const byte noPins = 2;
#ifdef DEBUG
const byte inPins[] = {11,12};
const byte busyPin = 10;
#endif
#ifdef ATTINY
const byte inPins[] = {6,7};
const byte busyPin = 10;
#endif

//Input Tracking
byte p[] = {1,1};
byte pOld[] = {1,1};
byte folderSounds[] = {0,0};
byte isBusy = 1;

void setup() {

  // configure pins for input
  for(int i = 0; i < noPins; i++){
    pinMode(inPins[i], INPUT_PULLUP);
  }

  //Configure busy pin
  pinMode(busyPin, INPUT_PULLUP);
  
  #ifdef ATTINY
  Serial.begin(9600);

  if (!myDFPlayer.begin(Serial)) { 
    while(true);
  }
  #endif
  
  #ifdef DEBUG
  Serial2.begin(9600);
  Serial.begin(115200);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(Serial2)) { 
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  #endif
  
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
      #ifdef DEBUG
      Serial.print(F("Button Pressed: "));
      Serial.println(i);
      #endif
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
    #ifdef DEBUG
    Serial.print(F("Playing Folder: "));
    Serial.print(folder);
    Serial.print(F(" Sound: "));
    Serial.println(sound);
    #endif

    myDFPlayer.playFolder(folder, sound);
  }
  #ifdef DEBUG
  else{
    Serial.println(F("BUSY"));
  }
  #endif
}

//Reads SD card file counds and saves values into folderSounds array. Runs once during setup.
void SetFolderFileCounts(){
  byte count = 0;
  for(int i = 0; i < noPins; i++){
    count = myDFPlayer.readFileCountsInFolder(i+1);
    folderSounds[i]=count;
    
  #ifdef DEBUG
  Serial.print(F("Folder: "));
  Serial.print(i+1);
  Serial.print(F(" Count: "));
  Serial.println(count);
  #endif
  }
}

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Adafruit_AW9523.h>

Adafruit_AW9523 aw;
//SoftwareSerial mySoftwareSerial(0, 1); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

#define BUSY_PIN    5  //PB4 physical 10
#define VOLUME_PIN  15 //PA2 physical 1

#define BUTTON_1_PIN     14   // PA1
#define BUTTON_2_PIN     0    // PA4
#define BUTTON_3_PIN     1    // PA5
#define BUTTON_4_PIN     4    // PB5
#define BUTTON_5_PIN     10   // PC0

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
byte folderSounds[] = {0,0,0,0};

int volumeRead = 0;
int volumeOut = 30;

void setup()
{
  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);
  pinMode(BUTTON_3_PIN, INPUT_PULLUP);
  pinMode(BUTTON_4_PIN, INPUT_PULLUP);
  pinMode(BUTTON_5_PIN, INPUT_PULLUP);

  pinMode(BUSY_PIN, INPUT_PULLUP);
  
  Serial.begin(9600); // Used to talk to the DFRobot MP3 Player 

  if (! aw.begin(0x58)) {
    //Serial.println("AW9523 not found? Check wiring!");
    while (1) delay(10);  // halt forever
  }

  //Serial.println("AW9523 found!");
  for (int i = 1; i < 6; i++)
  {
    aw.pinMode(i, OUTPUT);
    aw.digitalWrite(i, 0); // the LEDs turn off with 1 (true) and on with 0 (false)
  }

  aw.digitalWrite(1, HIGH);
  
  delay(1000);

  aw.digitalWrite(1, LOW);
  //Serial.println();
  //Serial.println(F("DFRobot DFPlayer Mini Demo"));
  //Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(Serial)) {  //Use softwareSerial to communicate with mp3.
    //Serial.println(F("Unable to begin:"));
    //Serial.println(F("1.Please recheck the connection!"));
    //Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  } 
  //Serial.println(F("DFPlayer Mini online."));
  
  delay(250);

  SetFolderFileCounts();

  myDFPlayer.volume(volumeOut);  //Set volume value. From 0 to 30
}

void loop()
{
  static unsigned long timer = millis();

  aw.digitalWrite(1, !buttonPressed(BUTTON_1_PIN));
  aw.digitalWrite(2, !buttonPressed(BUTTON_2_PIN));
  aw.digitalWrite(3, !buttonPressed(BUTTON_3_PIN));
  aw.digitalWrite(4, !buttonPressed(BUTTON_4_PIN));
  aw.digitalWrite(5, !buttonPressed(BUTTON_5_PIN));

  volumeRead = analogRead(VOLUME_PIN);
  volumeOut = map(volumeRead, 1023, 0, 0, 30); //Map vol pot read to DF Robot range.
  myDFPlayer.volume(volumeOut); //Set DF Robot volume
  
  if (!mp3Playing() && buttonPressed(BUTTON_1_PIN))
  {
    long randomSoundNumber = random(1, folderSounds[1] + 1);
    myDFPlayer.playFolder(1, randomSoundNumber);
  }

  //delay(10);
}

//Reads SD card file counds and saves values into folderSounds array. Runs once during setup.
void SetFolderFileCounts(){
  byte count = 0;
  for(int i = 0; i < 3; i++){
    count = myDFPlayer.readFileCountsInFolder(i+1);
    folderSounds[i]=count;
  }
}
bool mp3Playing()
{
  return !digitalRead(BUSY_PIN); //busy when busy Pin is Low
}

bool buttonPressed(int pin)
{
  // Will go LOW if pressed
  if (!digitalRead(pin)) 
  {
    return true;
    //Serial.println("Button Pressed");
    //if (millis() - lastDebounceTime > debounceDelay)
    //{
      //lastDebounceTime = millis();
      //return true;
    //}
  }
  
  return false;
}

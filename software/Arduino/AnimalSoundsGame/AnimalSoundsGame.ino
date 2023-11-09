#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Adafruit_AW9523.h>

Adafruit_AW9523 aw;
SoftwareSerial mySoftwareSerial(0, 1); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

#define BUTTON_1_PIN     14   // PA1
#define BUTTON_2_PIN     0    // PA4
#define BUTTON_3_PIN     1    // PA5
#define BUTTON_4_PIN     4    // PB5
#define BUTTON_5_PIN     10   // PC0

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long fileCount = 0;
unsigned long folder1FileCount = 0;

void setup()
{
  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);
  pinMode(BUTTON_3_PIN, INPUT_PULLUP);
  pinMode(BUTTON_4_PIN, INPUT_PULLUP);
  pinMode(BUTTON_5_PIN, INPUT_PULLUP);

  mySoftwareSerial.begin(9600); // Used to talk to the DFRobot MP3 Player
  Serial.begin(115200);

  if (! aw.begin(0x58)) {
    Serial.println("AW9523 not found? Check wiring!");
    while (1) delay(10);  // halt forever
  }

  Serial.println("AW9523 found!");
  for (int i = 1; i < 6; i++)
  {
    aw.pinMode(i, OUTPUT);
    aw.digitalWrite(i, 0); // the LEDs turn off with 1 (true) and on with 0 (false)
  }
    
  delay(1000);
  
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  } 
  Serial.println(F("DFPlayer Mini online."));
  
  delay(1000);
  
  Serial.print("File Count: ");
  fileCount = myDFPlayer.readFileCounts();
  Serial.println(fileCount);

  folder1FileCount = myDFPlayer.readFileCountsInFolder(1);
  Serial.print("Folder 1 Count: ");
  Serial.println(folder1FileCount);

  Serial.print("Folder 2 Count: ");
  Serial.println(myDFPlayer.readFileCountsInFolder(2));

  myDFPlayer.volume(10);  //Set volume value. From 0 to 30
}

void loop()
{
  static unsigned long timer = millis();

  aw.digitalWrite(1, !buttonPressed(BUTTON_1_PIN));
  aw.digitalWrite(2, !buttonPressed(BUTTON_2_PIN));
  aw.digitalWrite(3, !buttonPressed(BUTTON_3_PIN));
  aw.digitalWrite(4, !buttonPressed(BUTTON_4_PIN));
  aw.digitalWrite(5, !buttonPressed(BUTTON_5_PIN));

  if (!mp3Playing() && buttonPressed(BUTTON_1_PIN))
  {
    long randomSoundNumber = random(1, folder1FileCount + 1);
    Serial.print("Play Sound: ");
    Serial.println(randomSoundNumber);
    myDFPlayer.playFolder(1, randomSoundNumber);
    //myDFPlayer.playMp3Folder(1);
  }

  //delay(10);
}

bool mp3Playing()
{
  return false;
  //return myDFPlayer.readState() == 513;
}

bool buttonPressed(int pin)
{
  // Will go LOW if pressed
  if (!digitalRead(pin)) 
  {
    Serial.println("Button Pressed");
    if (millis() - lastDebounceTime > debounceDelay)
    {
      lastDebounceTime = millis();
      return true;
    }
  }
  
  return false;
}

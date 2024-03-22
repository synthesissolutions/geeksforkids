#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

DFRobotDFPlayerMini myDFPlayer;

#define BUTTON_COUNT  5
#define SOUND_FOLDER_COUNT  5

#define BUSY_PIN      5  //PB4 physical 10
#define VOLUME_PIN    15 //PA2 physical 1

#define BUTTON_1_PIN     0     // PA4  - Red
#define BUTTON_2_PIN     16    // PA3  - Blue
#define BUTTON_3_PIN     3     // PA7  - Yellow
#define BUTTON_4_PIN     2     // PA6  - White
#define BUTTON_5_PIN     1     // PA5  - Green

#define LED_1_PIN     15    // PA2  - Red
#define LED_2_PIN     14    // PA1  - Blue
#define LED_3_PIN     4     // PB5  - Yellow
#define LED_4_PIN     13    // PC3  - White
#define LED_5_PIN     12    // PC2  - Green

#define RANDOM_SEED_PIN   16  // PC2 - Unconnected

#define ANIMAL_SOUNDS_FOLDER    1
#define ANIMAL_NAMES_FOLDER     2
#define SPARKLE_SOUNDS_FOLDER   3
#define GOOD_JOB_SOUNDS_FOLDER  4
#define TRY_AGAIN_SOUNDS_FOLDER 5

#define SOUND_DELAY_MS    250

int buttonPins[] = {BUTTON_1_PIN, BUTTON_2_PIN, BUTTON_3_PIN, BUTTON_4_PIN, BUTTON_5_PIN};
int ledPins[] = {LED_1_PIN, LED_2_PIN, LED_3_PIN, LED_4_PIN, LED_5_PIN};

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
byte folderSounds[] = {0,0,0,0,0};

int volumeRead = 0;
int volumeOut = 30;

int currentAnimal = -1;
int currentButton = -1;
int incorrectGuessCount = 0;

// Keep track of the previous sound played or button selected for the game
// then make sure we don't use the same sound or button twice in a row
int lastButton = -1;
int lastAnimalSound = -1;
int lastGoodJobSound = 1;
int lastTryAgainSound = -1;

void setup()
{
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(RANDOM_SEED_PIN));
  
  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);
  pinMode(BUTTON_3_PIN, INPUT_PULLUP);
  pinMode(BUTTON_4_PIN, INPUT_PULLUP);
  pinMode(BUTTON_5_PIN, INPUT_PULLUP);

  pinMode(LED_1_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  pinMode(LED_3_PIN, OUTPUT);
  pinMode(LED_4_PIN, OUTPUT);
  pinMode(LED_5_PIN, OUTPUT);

  pinMode(BUSY_PIN, INPUT_PULLUP);
  
  Serial.begin(9600); // Used to talk to the DFRobot MP3 Player 

  // Delay for a short period to make sure the DF Robot MP3 Player board is ready
  delay(250);
  
  if (!myDFPlayer.begin(Serial)) 
  {
    while(true){
      delay(0);
    }
  } 
  
  delay(250);

  setFolderFileCounts();
  setVolumeFromPot();

  startupAnimation();
}

void loop()
{
  setVolumeFromPot();
  
  // Game Play
  // Play Start Sound?
  // Play Start Light Animation
  // Flash Single Button light while animal sound plays
  // Check for button press
    // If incorrect button is pressed
    //  light the button being pressed 
    //  play a sounds from the inccorect sound folder
    //  things like "boing"
    //  after X incorrect guesses, replay the animation and sound for the proper animal
    // If the correct button is pressed
    //  flash the light for the button pressed
    //  play a sound of the animal name/sound (roar for a lion, etc.)
    //  play a sound from the "good job" folder with a variety of positive sayings
    //  start the game over again

  if (currentAnimal < 0 || currentButton < 0)
  {
    // Start a new game
    incorrectGuessCount = 0;
    
    // wait until the current sound finishes
    while (mp3Playing())
    {
      delay(10);
      setVolumeFromPot();
    }

    turnOffAllButtons();
    
    // Start a new game
    do
    {
      currentButton = random(1, BUTTON_COUNT + 1);
    } while (currentButton == lastButton);
    
    lastButton = currentButton;
    
    do
    {
      currentAnimal = random(1, folderSounds[ANIMAL_SOUNDS_FOLDER - 1] + 1);
    } while(currentAnimal == lastAnimalSound);
    // Keep randomizing until we get a new animal sound so we don't play the same sound twice

    lastAnimalSound = currentAnimal;
    
    // Play the anmial name sound
    myDFPlayer.playFolder(ANIMAL_SOUNDS_FOLDER, currentAnimal);
    // Flash the current button while the sound plays
    delay(SOUND_DELAY_MS);
    while (mp3Playing())
    {
      setVolumeFromPot();
      lightButton(currentButton, true);
      delay(100);
      lightButton(currentButton, false);
      delay(100);
    }
    for (int i = 0; i < 5; i++) {
      lightButton(currentButton, true);
      delay(100);
      lightButton(currentButton, false);
      delay(100);
    }
  }
  else
  {
    // The Game is Afoot!
    if (correctButtonPressed(currentButton))
    {
      // The correct button was pressed!

      lightButton(currentButton, true);
      playRightAnswerSound();
      delay(SOUND_DELAY_MS);
      while (mp3Playing())
      {
        setVolumeFromPot();
        turnOnAllButtons();
        //lightButton(currentButton, true);
        delay(100);
        turnOffAllButtons();
        //lightButton(currentButton, false);
        delay(100);
      }

      delay(1500);
      
      currentAnimal = -1;
      currentButton = -1;
    }
    else
    {
      // If incorrect button is pressed
      if (incorrectButtonPressed(currentButton))
      {
        incorrectGuessCount++;
        
        //  light the button being pressed
        int button = getFirstButtonPressed();
        lightButton(button, true);
        
        //  play a sounds from the inccorect sound folder
        //  things like "boing"        
        playWrongAnswerSound();
        delay(SOUND_DELAY_MS);
        while (mp3Playing())
        {
          setVolumeFromPot();
          delay(100);
        }
      
        turnOffAllButtons();
      }
      //  after X incorrect guesses, replay the animation and sound for the proper animal
    }
  }
}

void setVolumeFromPot()
{
  volumeRead = analogRead(VOLUME_PIN);
  volumeOut = map(volumeRead, 1023, 0, 0, 30); //Map vol pot read to DF Robot range.

  myDFPlayer.volume(volumeOut);  //Set volume value. From 0 to 30
}

void startupAnimation()
{
  playRandomSparkleSound();

  setVolumeFromPot();
  turnOnAllButtons();
  delay(100);
  turnOffAllButtons();
  delay(100);
  setVolumeFromPot();

  chase(2, 200);
  setVolumeFromPot();

  turnOffAllButtons();

  delay(750);
  lightButton(1, true);
  setVolumeFromPot();
  delay(50);
  lightButton(1, false);
  lightButton(2, true);
  setVolumeFromPot();
  delay(50);
  lightButton(2, false);
  lightButton(3, true);
  setVolumeFromPot();
  delay(50);
  lightButton(3, false);
  lightButton(4, true);
  setVolumeFromPot();
  delay(50);
  lightButton(4, false);
  lightButton(5, true);
  setVolumeFromPot();
  delay(50);
  lightButton(5, false);
  setVolumeFromPot();
  delay(200);

  while (mp3Playing())
  {
    delay(10);
    setVolumeFromPot();
  }
}

void turnOnAllButtons()
{
    for (int i = 1; i <= BUTTON_COUNT; i++)
  {
    lightButton(i, true);
  }
}

void turnOffAllButtons()
{
    for (int i = 1; i <= BUTTON_COUNT; i++)
  {
    lightButton(i, false);
  }
}

void lightButtons(bool button1, bool button2, bool button3, bool button4, bool button5)
{
  lightButton(1, button1);
  lightButton(2, button2);
  lightButton(3, button3);
  lightButton(4, button4);
  lightButton(5, button5);
}

void lightButton(int buttonNumber, bool isLit)
{
  digitalWrite(ledPins[buttonNumber], isLit);
}

void chase(int count, int delayMs)
{
  for (int i = 0; i < count; i++)
  {
    lightButtons(true, false, false, false, false);
    delay(delayMs);
    lightButtons(false, true, false, false, false);
    delay(delayMs);
    lightButtons(false, false, true, false, false);
    delay(delayMs);
    lightButtons(false, false, false, true, false);
    delay(delayMs);
    lightButtons(false, false, false, false, true);
    delay(delayMs);
    lightButtons(false, false, false, true, false);
    delay(delayMs);
    lightButtons(false, false, true, false, false);
    delay(delayMs);
    lightButtons(false, true, false, false, false);
    delay(delayMs);
    lightButtons(true, false, false, false, false);
    delay(delayMs);
  }
}

void pong(int count, int delayMs)
{
  for (int i = 0; i < count; i++)
  {
    lightButtons(true, false, false, false, true);
    delay(delayMs);
    lightButtons(false, true, false, true, false);
    delay(delayMs);
    lightButtons(false, false, true, false, false);
    delay(delayMs);
    lightButtons(false, true, false, true, false);
    delay(delayMs);
    lightButtons(true, false, false, false, true);
    delay(delayMs);
  }
}

void playRandomSparkleSound()
{
  long randomSoundNumber = random(1, getFolderCount(SPARKLE_SOUNDS_FOLDER) + 1);
  myDFPlayer.playFolder(SPARKLE_SOUNDS_FOLDER, randomSoundNumber);
}

void playWrongAnswerSound()
{
  int randomSoundNumber;
  
  do
  {
    randomSoundNumber = random(1, getFolderCount(TRY_AGAIN_SOUNDS_FOLDER) + 1);
  } while(randomSoundNumber == lastTryAgainSound);
  // Keep randomizing until we get a new right answer sound so we don't play the same sound twice

  lastTryAgainSound = randomSoundNumber;
  
  myDFPlayer.playFolder(TRY_AGAIN_SOUNDS_FOLDER, randomSoundNumber);
}

void playRightAnswerSound()
{
  int randomSoundNumber;
  
  do
  {
    randomSoundNumber = random(1, getFolderCount(GOOD_JOB_SOUNDS_FOLDER) + 1);
  } while(randomSoundNumber == lastGoodJobSound);
  // Keep randomizing until we get a new right answer sound so we don't play the same sound twice

  lastGoodJobSound = randomSoundNumber;
  
  myDFPlayer.playFolder(GOOD_JOB_SOUNDS_FOLDER, randomSoundNumber);
}

//Reads SD card file counds and saves values into folderSounds array. Runs once during setup.
void setFolderFileCounts()
{
  byte count = 0;
  for(int i = 0; i < SOUND_FOLDER_COUNT; i++){
    count = myDFPlayer.readFileCountsInFolder(i+1);
    folderSounds[i]=count;
  }
}

bool mp3Playing()
{
  return !digitalRead(BUSY_PIN); //busy when busy Pin is Low
}

int getFolderCount(int folder)
{
  return folderSounds[folder - 1];
}

int getFirstButtonPressed()
{
  for (int i = 0; i < BUTTON_COUNT; i++)
  {
    int pin = buttonPins[i];
    if (!digitalRead(pin))
    {
      // Button index is 1 to BUTTON_COUNT and not 0 to BUTTON_COUNT
      return i + 1;
    }
  }

  return -1;
}

bool incorrectButtonPressed(int buttonNumber)
{
  // buttonNumber uses an index of 1 to BUTTON_COUNT
  // need to adjust to use the 0 to BUTTON_COUNT - 1 array
  for (int i = 0; i < BUTTON_COUNT; i++)
  {
    if (i == buttonNumber - 1) continue;

    int pin = buttonPins[i];
    if (!digitalRead(pin))
    {
      return true;
    }
  }
    
  return false;
}

bool correctButtonPressed(int buttonNumber)
{
  int pin = buttonPins[buttonNumber - 1];
  
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
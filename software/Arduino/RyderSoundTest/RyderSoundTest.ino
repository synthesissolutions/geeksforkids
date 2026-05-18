//Using KB240 
//Flash Size 8MB (Sketch: 3MB, FS: 5MB)

//Simon Game was modified from https://projecthub.arduino.cc/Arduino_Scuola/a-simple-simon-says-game-6f7fef

#include "Arduino.h"

#include <BackgroundAudio.h>
#include <LittleFS.h>
#include <Adafruit_PCM51xx.h>
#include <I2S.h>

#define BCLK D16 // BITCLOCK
#define WS   D17 // LRCLOCK
#define DOUT D18 // DATA

I2S audio(OUTPUT, BCLK, DOUT);
BackgroundAudioMP3Class<RawDataBuffer<16 * 1024>> BMP(audio);
Adafruit_PCM51xx pcm;

// The file we're currently playing
File fsound;

// Read buffer that's better off not in the stack due to its size
uint8_t filebuff[512];

//Simplify startup animation and winning animation. Turn off Simon Game. 0=OFF 1=ON 
#define MINIMIZE_FLASHING 0

#define BUTTON_COUNT  4
#define SOUND_FOLDER_COUNT  6

#define VOLUME_PIN    A0

#define BUTTON_1_PIN     6    //   - Red
#define BUTTON_2_PIN     4    //   - Blue
#define BUTTON_3_PIN     2    //   - Yellow
#define BUTTON_4_PIN     18    //   - White
#define BUTTON_5_PIN     19    //   - Green

#define LED_1_PIN      5    //   - Red
#define LED_2_PIN      3    //   - Blue
#define LED_3_PIN      1    //   - Yellow
#define LED_4_PIN      29    //   - White
#define LED_5_PIN      20    //   - Green

#define GAME_SEL_PIN   27    //   Toggle Switch
#define GAME_DEACT_PIN 10    //   Turns off sounds and lights

#define RANDOM_SEED_PIN   A2  //  Unconnected

//Define values for each type of sounds being used in each folder 
#define ANIMAL_SOUNDS_FOLDER    1
#define ANIMAL_NAMES_FOLDER     2
#define SPARKLE_SOUNDS_FOLDER   3
#define GOOD_JOB_SOUNDS_FOLDER  4
#define TRY_AGAIN_SOUNDS_FOLDER 5
#define SIMON_SOUNDS_FOLDER     6

#define SOUND_DELAY_MS    250

int buttonPins[] = {BUTTON_1_PIN, BUTTON_2_PIN, BUTTON_3_PIN, BUTTON_5_PIN};
int ledPins[] = {LED_1_PIN, LED_2_PIN, LED_3_PIN,  LED_5_PIN};

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long previousMillisBlink = 0;    // Used for timing lights that need to blink while waiting for input
unsigned long previousMillisTimeout = 0;    // Used for checking for inactivity and turning the system off
const unsigned long timeoutDuration = 120000;
byte folderSounds[] = {0,0,0,0,0,0}; //Used to keep track of file counts in each folder
int folderVal = 0;
int fileCount = 0;
bool soundPlaying = false;

int currentAnimal = -1;
int currentButton = -1;
int incorrectGuessCount = 0;

// Keep track of the previous sound played or button selected for the game
// then make sure we don't use the same sound or button twice in a row
int lastButton = -1;
int lastAnimalSound = -1;
int lastGoodJobSound = 1;
int lastTryAgainSound = -1;

const int MAX_LEVEL = 100;
int sequence[MAX_LEVEL];
int your_sequence[MAX_LEVEL];
int level = 1;
int velocity = 1000;
 
//char soundPath[10] = "";  //String to hold the folder path to play a sound and pass the info between cores
//char soundFileName[20] = "";  //String to hold filter to pick a sound and pass the info between cores
char soundFullFilePath[40] = ""; //Full Path and filename.
bool soundRequest = false;

float volumeRead = 0.0;
float volumeOut = 512.0;

byte selectedGame = -1;

bool ledBlinkState = false; //Used at the beginning of simon game to allow input while blinking

//Setup for core playing the game
void setup(){
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(RANDOM_SEED_PIN));

  Serial.begin(115200);

  while (!Serial) delay(1);

  Wire.setSDA(20); // Set SDA to GP0
  Wire.setSCL(21); // Set SCL to GP1
  Wire.begin();   // Initialize I2C

  // I2C mode (default)
  if (!pcm.begin()) {
    Serial.println(F("Could not find PCM51xx, check wiring!"));
    while (1) delay(10);
  }

  Serial.println(F("PCM51xx initialized successfully!"));

  pcm.resetRegisters();
  Serial.println("PCM Registers have been reset");
  
  // Set I2S format to I2S
  Serial.println(F("Setting I2S format"));
  pcm.setI2SFormat(PCM51XX_I2S_FORMAT_I2S);
  
  // Read and display current format
  pcm51xx_i2s_format_t format = pcm.getI2SFormat();
  Serial.print(F("Current I2S format: "));
  switch (format) {
    case PCM51XX_I2S_FORMAT_I2S:
      Serial.println(F("I2S"));
      break;
    case PCM51XX_I2S_FORMAT_TDM:
      Serial.println(F("TDM/DSP"));
      break;
    case PCM51XX_I2S_FORMAT_RTJ:
      Serial.println(F("Right Justified"));
      break;
    case PCM51XX_I2S_FORMAT_LTJ:
      Serial.println(F("Left Justified"));
      break;
    default:
      Serial.println(F("Unknown"));
      break;
  }
  
  // Set I2S word length to 32-bit
  Serial.println(F("Setting I2S word length"));
  pcm.setI2SSize(PCM51XX_I2S_SIZE_16BIT);
  
  // Read and display current word length
  pcm51xx_i2s_size_t size = pcm.getI2SSize();
  Serial.print(F("Current I2S word length: "));
  switch (size) {
    case PCM51XX_I2S_SIZE_16BIT:
      Serial.println(F("16 bits"));
      break;
    case PCM51XX_I2S_SIZE_20BIT:
      Serial.println(F("20 bits"));
      break;
    case PCM51XX_I2S_SIZE_24BIT:
      Serial.println(F("24 bits"));
      break;
    case PCM51XX_I2S_SIZE_32BIT:
      Serial.println(F("32 bits"));
      break;
    default:
      Serial.println(F("Unknown"));
      break;
  }

  // Set error detection bits
  if (!pcm.ignoreFSDetect(true) || !pcm.ignoreBCKDetect(true) || !pcm.ignoreSCKDetect(true) || 
      !pcm.ignoreClockHalt(true) || !pcm.ignoreClockMissing(true) || !pcm.disableClockAutoset(false) || 
      !pcm.ignorePLLUnlock(true)) {
    Serial.println(F("Error detection failed to configure"));
  }
  
  // Enable PLL
  Serial.println(F("Enabling PLL"));
  pcm.enablePLL(true);
  
  // Check PLL status
  bool pllEnabled = pcm.isPLLEnabled();
  Serial.print(F("PLL enabled: "));
  Serial.println(pllEnabled ? F("Yes") : F("No"));
  
  // Set PLL reference to BCK
  Serial.println(F("Setting PLL reference"));
  pcm.setPLLReference(PCM51XX_PLL_REF_BCK);
  
  // Read and display current PLL reference
  pcm51xx_pll_ref_t pllRef = pcm.getPLLReference();
  Serial.print(F("Current PLL reference: "));
  switch (pllRef) {
    case PCM51XX_PLL_REF_SCK:
      Serial.println(F("SCK"));
      break;
    case PCM51XX_PLL_REF_BCK:
      Serial.println(F("BCK"));
      break;
    case PCM51XX_PLL_REF_GPIO:
      Serial.println(F("GPIO"));
      break;
    default:
      Serial.println(F("Unknown"));
      break;
  }

  if (pcm.isPLLLocked()) {
    Serial.println("PLL Is Locked");
  } else {
    Serial.println("**** PLL Is NOT Locked ****");
  }
  
  // Set DAC clock source to PLL
  Serial.println(F("Setting DAC source"));
  pcm.setDACSource(PCM51XX_DAC_CLK_PLL);
  
  // Read and display current DAC source
  pcm51xx_dac_clk_src_t dacSource = pcm.getDACSource();
  Serial.print(F("Current DAC source: "));
  switch (dacSource) {
    case PCM51XX_DAC_CLK_MASTER:
      Serial.println(F("Master clock (auto-select)"));
      break;
    case PCM51XX_DAC_CLK_PLL:
      Serial.println(F("PLL clock"));
      break;
    case PCM51XX_DAC_CLK_SCK:
      Serial.println(F("SCK clock"));
      break;
    case PCM51XX_DAC_CLK_BCK:
      Serial.println(F("BCK clock"));
      break;
    default:
      Serial.println(F("Unknown"));
      break;
  }  

  // Test auto mute (default turn off)
  Serial.println(F("Setting auto mute"));
  pcm.setAutoMute(false);
  
  // Read and display current auto mute status
  bool autoMuteEnabled = pcm.getAutoMute();
  Serial.print(F("Auto mute: "));
  Serial.println(autoMuteEnabled ? F("Enabled") : F("Disabled"));
  
  // Test mute (default do not mute)
  Serial.println(F("Setting mute"));
  pcm.mute(false);
  
  // Read and display current mute status
  bool muteEnabled = pcm.isMuted();
  Serial.print(F("Mute: "));
  Serial.println(muteEnabled ? F("Enabled") : F("Disabled"));

  // Check DSP boot status and power state
  Serial.print(F("DSP boot done: "));
  Serial.println(pcm.getDSPBootDone() ? F("Yes") : F("No"));
  
  pcm51xx_power_state_t powerState = pcm.getPowerState();
  Serial.print(F("Power state: "));
  switch (powerState) {
    case PCM51XX_POWER_POWERDOWN:
      Serial.println(F("Powerdown"));
      break;
    case PCM51XX_POWER_WAIT_CP_VALID:
      Serial.println(F("Wait for CP voltage valid"));
      break;
    case PCM51XX_POWER_CALIBRATION_1:
    case PCM51XX_POWER_CALIBRATION_2:
      Serial.println(F("Calibration"));
      break;
    case PCM51XX_POWER_VOLUME_RAMP_UP:
      Serial.println(F("Volume ramp up"));
      break;
    case PCM51XX_POWER_RUN_PLAYING:
      Serial.println(F("Run (Playing)"));
      break;
    case PCM51XX_POWER_LINE_SHORT:
      Serial.println(F("Line output short / Low impedance"));
      break;
    case PCM51XX_POWER_VOLUME_RAMP_DOWN:
      Serial.println(F("Volume ramp down"));
      break;
    case PCM51XX_POWER_STANDBY:
      Serial.println(F("Standby"));
      break;
    default:
      Serial.println(F("Unknown"));
      break;
  }
  
  // Check PLL lock status
  bool pllLocked = pcm.isPLLLocked();
  Serial.print(F("PLL locked: "));
  Serial.println(pllLocked ? F("Yes") : F("No"));
  
  // Set volume to -6dB on both channels
  Serial.println(F("Setting volume"));
  pcm.setVolumeDB(0, 0);
  
  // Read and display current volume
  float leftVol, rightVol;
  pcm.getVolumeDB(&leftVol, &rightVol);
  Serial.print(F("Current volume - Left: "));
  Serial.print(leftVol, 1);
  Serial.print(F("dB, Right: "));
  Serial.print(rightVol, 1);
  Serial.println(F("dB"));

  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);
  pinMode(BUTTON_3_PIN, INPUT_PULLUP);
  //pinMode(BUTTON_4_PIN, INPUT_PULLUP);
  pinMode(BUTTON_5_PIN, INPUT_PULLUP);
  
  pinMode(GAME_SEL_PIN, INPUT_PULLUP);
  pinMode(GAME_DEACT_PIN, INPUT_PULLUP);

  pinMode(LED_1_PIN, OUTPUT_12MA);
  pinMode(LED_2_PIN, OUTPUT_8MA);
  pinMode(LED_3_PIN, OUTPUT_8MA);
  pinMode(LED_4_PIN, OUTPUT_8MA);
  pinMode(LED_5_PIN, OUTPUT_8MA);

  //pinMode(BUSY_PIN, INPUT_PULLUP);

  Serial.println("C0: FS init start.");
  if (!LittleFS.begin()) {
    Serial.println("C0: FS init Error.");
    while (1) {
      delay(1000);
      Serial.println("C0: FS not found.");
      //rp2040.reboot();
    }
  }
  Serial.println("C0: FS init end.");

  setFolderFileCounts("/");
  setVolumeFromPot();
  
  printFolderCounts();
  //check the game selection pin so it isn't -1
  checkIfGameChanged();
  //Start Game deactivated
  //deactivateGame();
}

//Setup for Core playing sounds
void setup1(){
  
  //Serial.begin(115200);
  BMP.begin();
}

//Main loop for playing sounds
void loop1(){
  
  if(fsound){
    soundPlaying = true;
    setVolumeValue();
    playActiveSound();
  }else{
    soundPlaying = false;
  }

  if (soundRequest){
    soundRequest = false;
    Serial.println("C1: Sound Starting");
    setVolumeValue();
    loadSound(soundFullFilePath);
  }

  if (millis() % 9 == 0) {
    setVolumeFromPot();
    setVolumeValue();
  }
}

//Main loop for playing games
void loop(){
  setVolumeFromPot();
  setGameSelection();
}

//Sets which game is active 
void setGameSelection(){

  checkIfGameChanged();
  
  if (selectedGame==0){
    AnimalSoundsGame();
  }else{
    SimonGame();
  }
}

//Checks the digital game select pin to see if the game selection has changed and checks for timeout condition.
bool checkIfGameChanged(){
  byte currentGame = selectedGame;
  
  //Select Game based of Game Select PIN
  if (digitalRead(GAME_SEL_PIN)){
    selectedGame = 0; //Animal Sounds Game
  }else{
    selectedGame = 0; //Animal Sounds Game
    //selectedGame = 1; //Simon Game
  }

  //Only allow Animal Game if MINIMIZE_FLASHING is true
  if (MINIMIZE_FLASHING == 1){
    selectedGame = 0; //Animal Sounds Game
  }
  
  //Deactivate system if timeout has occured 
  if (hasTimeoutOccured()){
    //deactivateGame();
    //selectedGame = 2; //Deactivation
  }
  
  //Reset game variables if the game selection has changed
  if (currentGame != selectedGame){
    ResetGameVariables();
    return true;
  }else{
    return false;
  }
}

//Soft Shutdown of game when buttons have not been pressed for a while.
void deactivateGame(){
  fsound.close(); //Close any currently playing sound
  soundRequest = false; //Stop any current sound requests
  turnOffAllButtons(); //Turn off all lights
  ResetGameVariables(); //Reset game variables for when game starts back up.

  //Wait for game to turn back on
  while(!anyButtonPressed()){
    //delay(1000);
  }
  startupAnimation();
  updateTimeout();
}

//Set game variables to the inital state
void ResetGameVariables(){
  currentAnimal = -1;
  currentButton = -1;
  incorrectGuessCount = 0;
  lastButton = -1;
  lastAnimalSound = -1;
  lastGoodJobSound = 1;
  lastTryAgainSound = -1;
  level = 1;
  velocity = 1000;
  ledBlinkState = false;
  previousMillisBlink = 0;
  updateTimeout();
}

//Main execution of the Animal Sounds Game
void AnimalSoundsGame(){
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

  if (currentAnimal < 0 || currentButton < 0){
    // Start a new game
    incorrectGuessCount = 0;
    
    // wait until the current sound finishes
    if (mp3Playing()){
      delay(10);
      setVolumeFromPot();
    }
    
    turnOffAllButtons();
    
    // Start a new game
    do{
      currentButton = random(0, BUTTON_COUNT);
    } while (currentButton == lastButton);
    
    lastButton = currentButton;
    
    do{
      currentAnimal = random(1, folderSounds[ANIMAL_SOUNDS_FOLDER - 1] + 1);
    } while(currentAnimal == lastAnimalSound);
    // Keep randomizing until we get a new animal sound so we don't play the same sound twice

    lastAnimalSound = currentAnimal;
    
    // Play the anmial name sound
    playFolderSound(ANIMAL_SOUNDS_FOLDER, currentAnimal);
    
    
    // Flash the current button while the sound plays
    delay(SOUND_DELAY_MS);
    while (mp3Playing()){
      setVolumeFromPot();
      lightButton(currentButton, true);
      delay(100);
      if(MINIMIZE_FLASHING == 0){
	     lightButton(currentButton, false);
	  }
      delay(100);
    }
    for (int i = 0; i < 5; i++) {
      lightButton(currentButton, true);
      delay(100);
      if(MINIMIZE_FLASHING == 0){
         lightButton(currentButton, false);
	  }
      delay(100);
    }
    if(MINIMIZE_FLASHING == 1){
      lightButton(currentButton, false);
    }
  }else{
    // The Game is Afoot!
    if (correctButtonPressed(currentButton)){
      // The correct button was pressed!
      updateTimeout();

      lightButton(currentButton, true);
      playRightAnswerSound();
      delay(SOUND_DELAY_MS);
      while (mp3Playing()){
        setVolumeFromPot();
        turnOnAllButtons();
        if(MINIMIZE_FLASHING == 0){
           //lightButton(currentButton, true);
           delay(100);
           turnOffAllButtons();
           //lightButton(currentButton, false);
        }
        delay(100);
      }
      if (MINIMIZE_FLASHING == 1){
	    turnOffAllButtons();
	  }

      delay(1500);
      
      currentAnimal = -1;
      currentButton = -1;
    }else{
      // If incorrect button is pressed
      if (incorrectButtonPressed(currentButton)){
        updateTimeout();
        incorrectGuessCount++;
        
        //  light the button being pressed
        int button = getFirstButtonPressed();
        lightButton(button, true);
        
        //  play a sounds from the inccorect sound folder
        //  things like "boing"
        playWrongAnswerSound();
        delay(SOUND_DELAY_MS);
        while (mp3Playing()){
          setVolumeFromPot();
          delay(100);
        }
      
        turnOffAllButtons();
      }
      //  after X incorrect guesses, replay the animation and sound for the proper animal
    }
  }
}

//Main execution of the Simon game
void SimonGame(){
  if (level == 1){
    Serial.println("Level 1");
    generate_sequence(); //generate a sequence;
  }

  if (digitalRead(BUTTON_1_PIN) == LOW || level != 1){ //If start button is pressed or you're winning
    lightButton(0, false); //turn off light if still on from blinking
    delay(200);
    show_sequence(); //show the sequence
    get_sequence(); //wait for your sequence
  }else{
    //Blink first LED to indicate user needs to start the game.
    unsigned long currentMillisBlink = millis();
    if (currentMillisBlink - previousMillisBlink >= 500){
      previousMillisBlink = currentMillisBlink;
      ledBlinkState = !ledBlinkState;
      lightButton(0, ledBlinkState);
    }
  }
  checkIfGameChanged();
}

//Shows the current sequence of the Simon game based on level
void show_sequence() {

  turnOffAllButtons();

  for (int i = 0; i < level; i++) {
    
    digitalWrite(ledPins[sequence[i]], HIGH);
    playFolderSound(SIMON_SOUNDS_FOLDER, sequence[i]+1);
    delay(velocity);
    digitalWrite(ledPins[sequence[i]], LOW);
    delay(200);
    if (checkIfGameChanged()){
      break;
    }
  }
  checkIfGameChanged();
}

//Gets the sequence back from the user and compairs it to the generated sequence
void get_sequence() {
  int flag = 0; //this flag indicates if the sequence is correct
  bool skip = false; //If the game changes or timesout we need to skip playing the game

  for (int i = 0; i < level; i++) {
    flag = 0;
    if(skip){
      break;
    }else{
      skip = checkIfGameChanged();
    }
    while (flag == 0) {
      if(skip){
        break;
      }else{
        skip = checkIfGameChanged();
      }
      for (int j = 0; j < BUTTON_COUNT; j++){
        if(skip){
          break;
        }else{
          skip = checkIfGameChanged();
        }
        setVolumeFromPot();
        if (digitalRead(buttonPins[j])==LOW){
          digitalWrite(ledPins[j], HIGH);
          while(digitalRead(buttonPins[j])==LOW){
            //wait for button release before moving forward.
          }
          your_sequence[i] = j;
          Serial.print(j);
          flag = 1;
          delay(200);
          if (your_sequence[i] != sequence[i]){
            wrong_sequence();
            return;
          }
          playFolderSound(SIMON_SOUNDS_FOLDER, j+1);
          digitalWrite(ledPins[j], LOW);
        }
      }
    }
  }
  if (!skip){
    right_sequence();
  }
}

//Generate a sequence for a Simon Game
void generate_sequence() {
  randomSeed(millis());

  for (int i = 0; i < MAX_LEVEL; i++) {
    sequence[i] = random(0, BUTTON_COUNT);
  }
}

//Play the "Animation" and sound when a user selects an incorrect button while playing Simon Game
void wrong_sequence() {
  playFolderSound(SIMON_SOUNDS_FOLDER,6);
  for (int i = 0; i < 3; i++) {
    turnOnAllButtons();
    delay(250);
    turnOffAllButtons();
    delay(250);
  }
  level = 1;
  velocity = 1000;
  updateTimeout();
}

//Play the "Animation" and sound when a user selects a correct button while playing Simon Game
void right_sequence() {
  turnOffAllButtons();
  delay(250);
  playFolderSound(SIMON_SOUNDS_FOLDER,7);
  turnOnAllButtons();
  delay(500);
  turnOffAllButtons();
  delay(500);

  if (level < MAX_LEVEL){
    level++;
  }
  
  velocity = -173*pow((level-1),0.333)+1000; //increase difficulty, ramps down to 200ms from 1000ms
  updateTimeout();
}

//Takes in a FolderNumber and FileNumber builds a file path, sets soundRequest to true to let the other core know to play a sound.
void playFolderSound(int folderNumber, int fileNumber){
  //fileNumber = 3;
  
  char holder[5]; //String to hold the numbers we are converting to a string
  char path[10] = "/0";  //String to hold the folder path padding with 0 because all folders start with 0
  char filePart[10] = "";
  char fullFilePath[40] = "";  //String to hold full file name to pick a sound
  Dir root;
  File f;

  itoa(folderNumber,holder,10); //Convert the folder number to a string and store it in holder var
  strcat(path,holder); //Concat the path and newly converted folder string
  strcat(path,"/"); //Finish the path 

  //This will need to be changed if we ever have more than 99 sounds in a folder which is currently unlikely
  if (fileNumber < 10){
    strcat(filePart,"00"); //Padding with 00 for single digits
  }else{
    strcat(filePart,"0"); //Padding with 0 for values >9
  }

  itoa(fileNumber,holder,10); //Convert the file number to a string in and store it in holder
  strcat(filePart,holder); //Concat it to our currently 0 padded file number
  
  root = LittleFS.openDir(path);
  
  //Loop through all the files in a folder and compare to the filepart
  //to the first 3 characters of each file until we find a match
  while (root.next()) {
    f = root.openFile("r");
    
    if (!f) {
      break;
    }
    if (f.isFile()) {
      if (strncmp(filePart, f.name(), 3) == 0) { //Check to see if the first 3 characters match
        strcpy(fullFilePath, f.fullName());
        break;
      }
    }
    f.close();
  }
  
  if (fullFilePath != ""){
    strcpy(soundFullFilePath, fullFilePath);

    //Setting soundRequest to true to let second core know we are ready to play a sound.
    soundRequest = true;
  } 
}

//Reads a potentiometer to set the volume of the sounds
void setVolumeFromPot(){
  // Reading potentiometer value (range is 0 - 1023)
  volumeRead = static_cast<float>(analogRead(VOLUME_PIN));
  //force the low end of the pot to zero so that the sound can be fully turned off
  if (volumeRead < 5.0){
    volumeRead = 0;
  }
}

//Sets the volume for the sounds if the volume has changed update the 
void setVolumeValue(){
  if (volumeRead != volumeOut){
    volumeOut = volumeRead;
    BMP.setGain(volumeOut/1023.0);
  }
}

//Animation for the start up of the system
void startupAnimation(){
  playRandomSparkleSound();

  setVolumeFromPot();
  turnOnAllButtons();
  delay(100);
  if (MINIMIZE_FLASHING == 0){
    turnOffAllButtons();
    delay(100);

	chase(2, 200);
    setVolumeFromPot();
	  
	turnOffAllButtons();

	delay(750);
	lightButton(0, true);
	setVolumeFromPot();
	delay(50);
	lightButton(0, false);
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
	setVolumeFromPot();
	delay(200);
  }else{
    setVolumeFromPot();
    delay(150);
    setVolumeFromPot();
    delay(150);
    setVolumeFromPot();
    delay(150);
    turnOffAllButtons();
  }

  while (mp3Playing()){
    delay(10);
    setVolumeFromPot();
  }
}

//Turns On all the lights on all buttons
void turnOnAllButtons(){
  for (int i = 0; i < BUTTON_COUNT; i++){
    lightButton(i, true);
  }
}

//Turns off all the lights on all buttons
void turnOffAllButtons(){
  for (int i = 0; i < BUTTON_COUNT; i++){
    lightButton(i, false);
  }
}

//Light up all buttons based on bool passed in
void lightButtons(bool button1, bool button2, bool button3, bool button4, bool button5){
  lightButton(0, button1);
  lightButton(1, button2);
  lightButton(2, button3);
  lightButton(3, button4);
  lightButton(4, button5);
}

//Light up a specific a specific button (0-4) based on a bool
void lightButton(int buttonNumber, bool isLit){
  digitalWrite(ledPins[buttonNumber], isLit);
}

//Chase light animation count is for number loops delayMs is for delay time between each light
void chase(int count, int delayMs){
  for (int i = 0; i < count; i++){
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

//Pong Light animation count is for number loops delayMs is for delay time between each light
void pong(int count, int delayMs){
  for (int i = 0; i < count; i++){
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

//Plays a random "Sparkle" Sound 
void playRandomSparkleSound(){
  long randomSoundNumber = random(1, getFolderCount(SPARKLE_SOUNDS_FOLDER) + 1);
  playFolderSound(SPARKLE_SOUNDS_FOLDER, randomSoundNumber);
}

//Plays random "Wrong Answer" Sound keeps track of last sound to not repeat two in a row
void playWrongAnswerSound(){
  int randomSoundNumber;
  
  do{
    randomSoundNumber = random(1, getFolderCount(TRY_AGAIN_SOUNDS_FOLDER) + 1);
  } while(randomSoundNumber == lastTryAgainSound);
  // Keep randomizing until we get a new right answer sound so we don't play the same sound twice
  
  lastTryAgainSound = randomSoundNumber;
  
  playFolderSound(TRY_AGAIN_SOUNDS_FOLDER,randomSoundNumber);
}

//Plays random "Right Answer" Sound keeps track of last sound to not repeat two in a row
void playRightAnswerSound(){
  int randomSoundNumber;
  
  do{
    randomSoundNumber = random(1, getFolderCount(GOOD_JOB_SOUNDS_FOLDER) + 1);
  } while(randomSoundNumber == lastGoodJobSound);
  // Keep randomizing until we get a new right answer sound so we don't play the same sound twice

  lastGoodJobSound = randomSoundNumber;
  
  playFolderSound(GOOD_JOB_SOUNDS_FOLDER, randomSoundNumber);
}

//Continue Playing Active Sound adds more to the file buffer to contiue playing a sound run from loop1
void playActiveSound(){
  // Stuff the buffer with as much as it will take, only doing full sector reads for performance
  while (fsound && BMP.availableForWrite() > 512) {
    int len = fsound.read(filebuff, 512);
    BMP.write(filebuff, len);
    if (len != 512) {
      fsound.close(); // Short reads == EOF
    }
  }
}

//Open a file from the full path and start playing the sound
void loadSound(const char *fullpath){
  Serial.print("loadSound");
  Serial.print(fullpath);
  fsound = LittleFS.open(fullpath, "r");
  auto p = fsound.position();
  p = p & ~511; // Ensure on a sector boundary, MP3 will resync appropriately
  fsound.seek(p);

  playActiveSound();
}

//Reads litteFS Sounds and saves values into folderSounds array. Runs once during setup.
void setFolderFileCounts(const char *dirname){ 
  Serial.print("Scaning Directory: ");
  Serial.println(dirname);
  Dir root = LittleFS.openDir(dirname);
  File f;
  
  while (root.next()) {
    f = root.openFile("r");
    if (!f) {
      break;
    }
    if (f.isDirectory()) {
      if (fileCount != 0){
        folderSounds[folderVal]=fileCount;
      }
      folderVal = atoi(f.name())-1;  //Folder names should be a number in our application
      fileCount = 0;
      setFolderFileCounts(f.fullName());
    } else {
      fileCount++;
    }
    f.close();
  }
}

//Check to see if a file is actively playing.
bool mp3Playing(){
  if (BMP.done()){
    return false;
  }else{
    return true;
  }
  //return soundPlaying;
  //return !digitalRead(BUSY_PIN); //busy when busy Pin is Low
}

//Returns the nubmer of sounds stored in a folder 
int getFolderCount(int folder){
  return folderSounds[folder - 1];
}

//loops through the buttons and returns the fist button found that is pressed
int getFirstButtonPressed(){
  updateTimeout();

  for (int i = 0; i < BUTTON_COUNT; i++){
    int pin = buttonPins[i];
    if (!digitalRead(pin)){
      return i;
    }
  }

  return -1;
}

//Checks to see if button press is incorrect in Animal Sounds Game
bool incorrectButtonPressed(int buttonNumber){
  for (int i = 0; i < BUTTON_COUNT; i++)  {
    if (i == buttonNumber) continue;

    int pin = buttonPins[i];
    if (!digitalRead(pin)){
      return true;
    }
  }
    
  return false;
}

//Checks to see if button press is correct in Animal Sounds Game
bool correctButtonPressed(int buttonNumber){
  int pin = buttonPins[buttonNumber];
  
  // Will go LOW if pressed
  if (!digitalRead(pin)){
    Serial.println("Button Pressed");
    return true;
    //if (millis() - lastDebounceTime > debounceDelay)
    //{
      //lastDebounceTime = millis();
      //return true;
    //}
  }
  
  return false;
}

//Prints folder counts to the serial output for testing and troubleshooting
void printFolderCounts(){
  for(int i = 0; i < SOUND_FOLDER_COUNT; i++){
    Serial.print("index: ");Serial.print(i);Serial.print(" folder: ");Serial.print(i+1);Serial.print(" Value: ");Serial.println(folderSounds[i]);
  }
}

//Checks if the game timeout has occured to see if we need to soft shutdown the game
bool hasTimeoutOccured(){
  unsigned long currentMillisTimeout = millis();
  if (currentMillisTimeout - previousMillisTimeout >= timeoutDuration){
    return true;
  }else{
    return false;
  }
}

//Updates the Timeout Millis to the current time so Timeout doesn't occur
void updateTimeout(){
  unsigned long currentMillisTimeout = millis();
  previousMillisTimeout = currentMillisTimeout;
}

//Checks if any button has been pressed used to enable the game if soft shutdown has occured
bool anyButtonPressed(){
  bool buttonPressed = false;
  byte currentGame = selectedGame;

  for (int i = 0; i < BUTTON_COUNT; i++){
    if (digitalRead(buttonPins[i])==LOW){
      buttonPressed = true;
      break;
    }
  }
  if(!buttonPressed){
    if (digitalRead(GAME_SEL_PIN)){
      selectedGame = 0;
    }else{
      selectedGame = 1;
    }
    
    if (MINIMIZE_FLASHING == 1){
      selectedGame = 0;
    }
    
    if (currentGame != selectedGame){
      buttonPressed = true;
    }
  }

  return buttonPressed;
}

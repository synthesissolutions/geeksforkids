#include "Arduino.h"

#include <BackgroundAudio.h>
#include <LittleFS.h>
#include <I2S.h>

I2S audio(OUTPUT, 7, 9);  //i2s(OUTPUT, pBCLK, pDOUT);   pLRC (pBCLK+1)
BackgroundAudioMP3Class<RawDataBuffer<16 * 1024>> BMP(audio);

// The file we're currently playing
File fsound;

// Read buffer that's better off not in the stack due to its size
uint8_t filebuff[512];

#define BUTTON_COUNT  5
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

#define ANIMAL_SOUNDS_FOLDER    1
#define ANIMAL_NAMES_FOLDER     2
#define SPARKLE_SOUNDS_FOLDER   3
#define GOOD_JOB_SOUNDS_FOLDER  4
#define TRY_AGAIN_SOUNDS_FOLDER 5
#define SIMON_SOUNDS_FOLDER     6

#define SOUND_DELAY_MS    250

int buttonPins[] = {BUTTON_1_PIN, BUTTON_2_PIN, BUTTON_3_PIN, BUTTON_4_PIN, BUTTON_5_PIN};
int ledPins[] = {LED_1_PIN, LED_2_PIN, LED_3_PIN, LED_4_PIN, LED_5_PIN};

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long previousMillisBlink = 0;    // Used for timing lights that need to blink while waiting for input
unsigned long previousMillisTimeout = 0;    // Used for checking for inactivity and turning the system off
const unsigned long timeoutDuration = 120000;
byte folderSounds[] = {0,0,0,0,0,0};
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

void setup(){
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
  
  pinMode(GAME_SEL_PIN, INPUT_PULLUP);
  pinMode(GAME_DEACT_PIN, INPUT_PULLUP);

  pinMode(LED_1_PIN, OUTPUT_12MA);
  pinMode(LED_2_PIN, OUTPUT_8MA);
  pinMode(LED_3_PIN, OUTPUT_8MA);
  pinMode(LED_4_PIN, OUTPUT_8MA);
  pinMode(LED_5_PIN, OUTPUT_8MA);

  //pinMode(BUSY_PIN, INPUT_PULLUP);

  Serial.begin(115200);

  //while (!Serial) delay(1);
  
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
  deactivateGame();
}

void setup1(){
  
  //Serial.begin(115200);
  BMP.begin();
}

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
    //source.setPath(soundPath);
    //source.setFileFilter(soundFilter);
    Serial.println("C1: Sound Starting");
    setVolumeValue();
    loadSound(soundFullFilePath);
  }

  if (millis() % 9) {
    setVolumeFromPot();
    setVolumeValue();
  }
}

void loop(){
  setVolumeFromPot();
  setGameSelection();
}

void setGameSelection(){

  checkIfGameChanged();
  
  if (selectedGame==0){
    AnimalSoundsGame();
  }else{
    SimonGame();
  }
}

bool checkIfGameChanged(){
  byte currentGame = selectedGame;
  
  checkTimeout();
  
  if (digitalRead(GAME_SEL_PIN)){
    selectedGame = 0;
  }else{
    selectedGame = 1;
  }
  
  if (currentGame != selectedGame){
    ResetGameVariables();
    return true;
  }else{
    return false;
  }
}

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
      lightButton(currentButton, false);
      delay(100);
    }
    for (int i = 0; i < 5; i++) {
      lightButton(currentButton, true);
      delay(100);
      lightButton(currentButton, false);
      delay(100);
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
        //lightButton(currentButton, true);
        delay(100);
        turnOffAllButtons();
        //lightButton(currentButton, false);
        delay(100);
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

void SimonGame(){
  if (level == 1){
    //Serial.println("Level 1");
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

void get_sequence() {
  int flag = 0; //this flag indicates if the sequence is correct
  bool skip = false; //If the game changes or timesout we need to skip playing the game

  for (int i = 0; i < level; i++) {
    flag = 0;
    skip = checkIfGameChanged();
    if(skip){
      break;
    }
    while (flag == 0) {
      skip = checkIfGameChanged();
      if(skip){
        break;
      }
      for (int j = 0; j < BUTTON_COUNT; j++){
        skip = checkIfGameChanged();
        if(skip){
          break;
        }
        setVolumeFromPot();
        if (digitalRead(buttonPins[j])==LOW){
          digitalWrite(ledPins[j], HIGH);
          while(digitalRead(buttonPins[j])==LOW){
            //wait for button release before moving forward.
          }
          your_sequence[i] = j;
          //Serial.print(j);
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

void generate_sequence() {
  randomSeed(millis());

  for (int i = 0; i < MAX_LEVEL; i++) {
    sequence[i] = random(0, BUTTON_COUNT);
  }
}

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
  
  velocity -= 10; //increase difficulty
  updateTimeout();
}

void playFolderSound(int folderNumber, int fileNumber){
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
        Serial.print(" --Pass ");
        Serial.println(f.fullName());
        strcpy(fullFilePath, f.fullName());
        break;
      } else {
        Serial.println(" --Fail");
      }
    }
    f.close();
  }
  
  if (fullFilePath != ""){
    strcpy(soundFullFilePath, fullFilePath);
  
    Serial.print("C0: Requesting File: ");
    Serial.println(soundFullFilePath); 

    //Setting soundRequest to true to let second core know we are ready to play a sound.
    soundRequest = true;
  } 
}

void setVolumeFromPot(){
  // Reading potentiometer value (range is 0 - 1023)
  volumeRead = static_cast<float>(analogRead(VOLUME_PIN));
  if (volumeRead < 5.0){
    volumeRead = 0;
  }
}

void setVolumeValue(){
  if (volumeRead != volumeOut){
    volumeOut = volumeRead;
    BMP.setGain(volumeOut/1023.0);
  }
}

void startupAnimation(){
  playRandomSparkleSound();

  setVolumeFromPot();
  turnOnAllButtons();
  delay(100);
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

  while (mp3Playing()){
    delay(10);
    setVolumeFromPot();
  }
}

void turnOnAllButtons(){
  for (int i = 0; i < BUTTON_COUNT; i++){
    lightButton(i, true);
  }
}

void turnOffAllButtons(){
  for (int i = 0; i < BUTTON_COUNT; i++){
    lightButton(i, false);
  }
}

void lightButtons(bool button1, bool button2, bool button3, bool button4, bool button5){
  lightButton(0, button1);
  lightButton(1, button2);
  lightButton(2, button3);
  lightButton(3, button4);
  lightButton(4, button5);
}

void lightButton(int buttonNumber, bool isLit){
  digitalWrite(ledPins[buttonNumber], isLit);
}

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

void playRandomSparkleSound(){
  long randomSoundNumber = random(1, getFolderCount(SPARKLE_SOUNDS_FOLDER) + 1);
  //myDFPlayer.playFolder(SPARKLE_SOUNDS_FOLDER, randomSoundNumber);
  playFolderSound(SPARKLE_SOUNDS_FOLDER, randomSoundNumber);
}

void playWrongAnswerSound(){
  int randomSoundNumber;
  
  do{
    randomSoundNumber = random(1, getFolderCount(TRY_AGAIN_SOUNDS_FOLDER) + 1);
  } while(randomSoundNumber == lastTryAgainSound);
  // Keep randomizing until we get a new right answer sound so we don't play the same sound twice
  
  lastTryAgainSound = randomSoundNumber;
  
  //myDFPlayer.playFolder(TRY_AGAIN_SOUNDS_FOLDER, randomSoundNumber);
  playFolderSound(TRY_AGAIN_SOUNDS_FOLDER,randomSoundNumber);
}

void playRightAnswerSound(){
  int randomSoundNumber;
  
  do{
    randomSoundNumber = random(1, getFolderCount(GOOD_JOB_SOUNDS_FOLDER) + 1);
  } while(randomSoundNumber == lastGoodJobSound);
  // Keep randomizing until we get a new right answer sound so we don't play the same sound twice

  lastGoodJobSound = randomSoundNumber;
  
  //myDFPlayer.playFolder(GOOD_JOB_SOUNDS_FOLDER, randomSoundNumber);
  playFolderSound(GOOD_JOB_SOUNDS_FOLDER, randomSoundNumber);
}

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

void loadSound(const char *fullpath){
  //Serial.print("");
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

bool mp3Playing(){
  return soundPlaying;
  //return !digitalRead(BUSY_PIN); //busy when busy Pin is Low
}

int getFolderCount(int folder){
  return folderSounds[folder - 1];
}

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

bool correctButtonPressed(int buttonNumber){
  int pin = buttonPins[buttonNumber];
  
  // Will go LOW if pressed
  if (!digitalRead(pin)){
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

void printFolderCounts(){
  for(int i = 0; i < SOUND_FOLDER_COUNT; i++){
    Serial.print("index: ");Serial.print(i);Serial.print(" folder: ");Serial.print(i+1);Serial.print(" Value: ");Serial.println(folderSounds[i]);
  }
}

void checkTimeout(){
  unsigned long currentMillisTimeout = millis();
  if (currentMillisTimeout - previousMillisTimeout >= timeoutDuration){
    deactivateGame();
  }
}

void updateTimeout(){
  unsigned long currentMillisTimeout = millis();
  previousMillisTimeout = currentMillisTimeout;
}

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
    
    if (currentGame != selectedGame){
      buttonPressed = true;
    }
  }

  return buttonPressed;
}

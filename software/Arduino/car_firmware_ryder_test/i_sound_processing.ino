 /**
 * SoundProcessing Class
 * 
 * This class provides an interface to the 3 NeoPixels and 2 External LED strips
 */
#include "Arduino.h"

#include <BackgroundAudio.h>
#include <LittleFS.h>
#include <I2S.h>

I2S audio(OUTPUT, PIN_DAC_I2S_BCK, PIN_DAC_I2S_DIN);
BackgroundAudioMP3Class<RawDataBuffer<16 * 1024>> BMP(audio);

// The file we're currently playing
File fsound;

#define SOUND_BUTTON_A_FOLDER  1
#define SOUND_BUTTON_B_FOLDER  2
#define ACTION_TRIGGER_1_FOLDER  3
#define ACTION_TRIGGER_2_FOLDER  4

#define SOUND_FOLDER_COUNT  4

// Read buffer that's better off not in the stack due to its size
uint8_t filebuff[512];

class SoundProcessing {
  private:
    byte folderSounds[SOUND_FOLDER_COUNT] = {0,0,0,0}; //Used to keep track of file counts in each folder
    int folderVal = 0;
    int fileCount = 0;
    bool soundPlaying = false;
    char soundFullFilePath[40] = ""; //Full Path and filename.
    bool soundRequest = false;

    bool soundProcessingAvailable = false;

    
  
  public:
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).
    SoundProcessing() {
    }

    /*
     * init - initialize the joystick instance with the pins for x and y axes
     */
    void init() {

      BMP.begin();

      if (LittleFS.begin()) {
        soundProcessingAvailable = true;
      }

      while (!Serial) delay(1);
      setFolderFileCounts("/");
      printFolderCounts();
    }

    void processSoundRequests() {
      if(fsound){
        soundPlaying = true;
        playActiveSound();
      }else{
        soundPlaying = false;
      }
    
      if (soundRequest){
        soundRequest = false;
        Serial.println("C1: Sound Starting");
        loadSound(soundFullFilePath);
      }
    }

    //Returns the nubmer of sounds stored in a folder 
    int getFolderCount(int folder){
      return folderSounds[folder - 1];
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

    void playSoundButtonA() {
      playSound(SOUND_BUTTON_A_FOLDER);
    }

    void playSoundButtonB() {
      playSound(SOUND_BUTTON_A_FOLDER);
    }

    void playActionTrigger1() {
      playSound(ACTION_TRIGGER_1_FOLDER);
    }

    void playActionTrigger2() {
      playSound(ACTION_TRIGGER_2_FOLDER);
    }

    void playSound(int folderNumber) {
      if (soundProcessingAvailable) {
        Serial.print("folderNumber: ");
        Serial.println(folderNumber);
        Serial.print("getFolderCount: ");
        Serial.println(getFolderCount(folderNumber));
        long randomSoundNumber = random(1, getFolderCount(folderNumber) + 1);
        Serial.print("randomSoundNumber: ");
        Serial.println(randomSoundNumber);
        playFolderSound(folderNumber, randomSoundNumber);
      }
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

      Serial.print("path: ");
      Serial.println(path);
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

      Serial.print("fullFilePath: ");
      Serial.println(fullFilePath);
      
      if (fullFilePath != ""){
        strcpy(soundFullFilePath, fullFilePath);
    
        //Setting soundRequest to true to let second core know we are ready to play a sound.
        soundRequest = true;
      } 
    }

    //Open a file from the full path and start playing the sound
    void loadSound(const char *fullpath){
      Serial.print("loadSound fullpath: ");
      Serial.print(fullpath);
      fsound = LittleFS.open(fullpath, "r");
      auto p = fsound.position();
      p = p & ~511; // Ensure on a sector boundary, MP3 will resync appropriately
      fsound.seek(p);
    
      playActiveSound();
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

    //Prints folder counts to the serial output for testing and troubleshooting
    void printFolderCounts(){
      for(int i = 0; i < SOUND_FOLDER_COUNT; i++){
        Serial.print("index: ");Serial.print(i);Serial.print(" folder: ");Serial.print(i+1);Serial.print(" Value: ");Serial.println(folderSounds[i]);
      }
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

    void getStatus(char * status) {
      sprintf(status, "[Sound Processing] Avail: %s Playing: %s Request: %s",
        soundProcessingAvailable ? "Yes" : "*no*",
        soundPlaying ? "Yes" : "*no*",
        soundRequest ? "Yes" : "*no*");
    }
};

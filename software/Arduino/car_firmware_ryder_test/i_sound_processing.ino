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

#define SOUND_FOLDER_COUNT  6

// Read buffer that's better off not in the stack due to its size
uint8_t filebuff[512];

class SoundProcessing {
  private:
    byte folderSounds[SOUND_FOLDER_COUNT] = {0,0,0,0,0,0}; //Used to keep track of file counts in each folder
    int folderVal = 0;
    int fileCount = 0;
    bool soundPlaying = false;
    char soundFullFilePath[40] = ""; //Full Path and filename.
    bool soundRequest = false;
  
  public:
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).
    SoundProcessing() {
    }

    /*
     * init - initialize the joystick instance with the pins for x and y axes
     */
    void init() {

      BMP.begin();

    }
};

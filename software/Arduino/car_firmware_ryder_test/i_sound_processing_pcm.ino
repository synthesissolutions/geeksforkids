 /**
 * SoundProcessing Class
 * 
 * This class provides an interface to the 3 NeoPixels and 2 External LED strips
 */
#include <Adafruit_PCM51xx.h>

Adafruit_PCM51xx pcm;

class SoundProcessingPcm {
  private:
    bool pcmAvailable = false;
    bool pllEnabled = false;
    bool pllLocked = false;
    bool dspBootDone = false;
    int rawVolume = 0;
    float volumeDb = 0.0;
  
  public:
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).
    SoundProcessingPcm() {
    }

    /*
     * init - initialize the joystick instance with the pins for x and y axes
     */
    void init() {
      // I2C mode (default)
      if (pcm.begin()) {
        pcmAvailable = true;
      }
  
      if (pcmAvailable) {
        pcm.resetRegisters();
        pcm.setI2SFormat(PCM51XX_I2S_FORMAT_I2S);
        pcm.setI2SSize(PCM51XX_I2S_SIZE_16BIT);
        
        // Set error detection bits
        if (!pcm.ignoreFSDetect(true) || !pcm.ignoreBCKDetect(true) || !pcm.ignoreSCKDetect(true) || 
            !pcm.ignoreClockHalt(true) || !pcm.ignoreClockMissing(true) || !pcm.disableClockAutoset(false) || 
            !pcm.ignorePLLUnlock(true)) {
          //Serial.println(F("Error detection failed to configure"));
        }
        
        // Enable PLL
        pcm.enablePLL(true);
        
        // Check PLL status
        pllEnabled = pcm.isPLLEnabled();
  
        pcm.setPLLReference(PCM51XX_PLL_REF_BCK);
        pllLocked = pcm.isPLLLocked();
        pcm.setDACSource(PCM51XX_DAC_CLK_PLL);
        pcm.setAutoMute(false);
        pcm.mute(false);
        dspBootDone = pcm.getDSPBootDone();
        pcm.setVolumeDB(0, 0);
      }

    }

    // the volume recieved will be a number from 1 to 100
    // convert to log scale
    void setVolume(int volume) {
      //Serial.print(volume);
      rawVolume = volume;
      //Serial.print(" ");
      //Serial.print(rawVolume);
      int normalizedVolume = min(max(1, volume), 100);
      //Serial.print(" ");
      //Serial.print(normalizedVolume);
      float logVolume = log(normalizedVolume / 100.0) * 20.0;
      //Serial.print(" ");
      //Serial.println(logVolume);
      pcm.setVolumeDB(logVolume, logVolume);
      volumeDb = logVolume;
    }

    void getStatus(char * status) {
      sprintf(status, "[Sound Processing PCM] PCM Avail: %s PLL Enabled: %s PLL Locked: %s PLL Locked2: %s DSP Boot Done: %s Volume DB: %   f Raw Volume: %i",
        pcmAvailable ? "Yes" : "*no*",
        pllEnabled ? "Yes" : "*no*",
        pllLocked ? "Yes" : "*no*",
        dspBootDone ? "Yes" : "*no*",
        volumeDb,
        rawVolume);
    }
};

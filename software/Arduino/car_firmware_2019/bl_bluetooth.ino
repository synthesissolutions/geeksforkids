#include <ArduinoJson.h>

#include <AltSoftSerial.h>

// AltSoftSerial always uses these pins:
//
// Board          Transmit  Receive   PWM Unusable
// -----          --------  -------   ------------
// Teensy 3.0 & 3.1  21        20         22
// Teensy 2.0         9        10       (none)
// Teensy++ 2.0      25         4       26, 27
// Arduino Uno        9         8         10
// Arduino Leonardo   5        13       (none)
// Arduino Mega      46        48       44, 45
// Wiring-S           5         6          4
// Sanguino          13        14         12

AltSoftSerial altSerial;

/**
 * Bluetooth Class
 * 
 * This class serves to send and receive Bluetooth 4.0 BLE messages for saving and retrieving Configuration values.
 * This class is meant to be used with the Ionic Geeks Car Configuration app
 */

class Bluetooth {
  private:
    String rawCommand = "";
    boolean readingCommand = false;
    int enableBluetoothButtonPin;
    boolean isBluetoothEnabled = false;
    Eeprom *eeprom;
    
    StaticJsonDocument<1024> currentCommandJson;
  

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    Configuration() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init(int enableBluetoothButtonPin, Eeprom *e) {  
      this->enableBluetoothButtonPin = enableBluetoothButtonPin;
      eeprom = e;
      pinMode(enableBluetoothButtonPin, INPUT_PULLUP);
    }

    void initBluetooth() {
      Serial.println("");
      Serial.println("Bluetooth Initialized...");
      Serial.println("");
      altSerial.begin(9600);
    }

    /*
     * getters ... translate dip switch settings into car configuration
     */
    boolean isActive() {
      return isBluetoothEnabled;
    }


    void processEnableButton() {
      // Once Bluetooth is enabled it stays enabled until the car is turned off
      if (isBluetoothEnabled) return;

      // Logic is reversed since it is connected to ground when pushed.
      isBluetoothEnabled = !digitalRead(enableBluetoothButtonPin);
    }
    
    /*
     * Sample JSON Command
     {
      "Command": "Set",
      "maxSpeed": 75,
      "actuatorCenter": 600,
      .
      .
      .
     }
     */
    String processJsonCommand(String jsonCommand) {
      String returnVal = "";
    
      DeserializationError jsonError = deserializeJson(currentCommandJson, jsonCommand);
    
      if (jsonError) {
        Serial.print("JSON Error: ");
        Serial.println(jsonError.c_str());
    
        return jsonError.c_str();
      }
      
      Serial.println("JSON OK");
      String command = currentCommandJson["Command"];
      Serial.print("Command: ");
      Serial.println(command);
      if (command == "Get") {
        // TODO call method on EEprom to get JSON object
        serializeJson(eeprom->getCurrentSettingsAsJson(), returnVal);
      } else if (command == "Set") {
        returnVal = processSetCommand();
      } else if (command == "Reset") {
        returnVal = processResetCommand();  
      }
    
      return returnVal;
    }
    
    String processSetCommand() {
      // TODO call set method on the EEprom object
      for (int i = 0; i < NUMBER_OF_CONFIGURATION_ENTRIES; i++) {
        ConfigurationEntry entry = configurationEntries[i];
        if (currentCommandJson.containsKey(entry.name)) {
          if (entry.dataType == "Integer") {
            int value = currentCommandJson[entry.name];
            Serial.print("Setting Value For: ");
            Serial.print(entry.name);
            Serial.print("  value: ");
            Serial.print(value);
            eeprom->setIntegerSetting(entry.name, value);
            //EEPROM.put(entry.eeAddress, value);
            //currentSettingsJson[entry.name] = currentCommandJson[entry.name];
          } else if (entry.dataType == "Boolean") {
            Serial.print(entry.name);
            Serial.print(": ");
            boolean booleanValue = currentCommandJson[entry.name];
            Serial.println(booleanValue);
            eeprom->setBooleanSetting(entry.name, booleanValue);
            //if (currentCommandJson[entry.name]) {
              //EEPROM.put(entry.eeAddress, 1);
              //currentSettingsJson[entry.name] = true;
            //} else {
              //EEPROM.put(entry.eeAddress, 0);
              //currentSettingsJson[entry.name] = false;
            //}
          } else {
            // ignore for now
          }
        }
      }

      eeprom->saveConfiguration();
      
      return "{\"Success\": true}";
    }
    
    String processResetCommand() {
      eeprom->resetConfiguration();
      
      return "{\"Success\": true}";
    }

    void processBluetooth() {
      char c;
    
      if (Serial.available()) {
        c = Serial.read();
        altSerial.print(c);
      }
      if (altSerial.available()) {
        c = altSerial.read();
        Serial.print(c);
    
        if (c == '{') {
          // Start a new command
          // This isn't a great method because it doesn't allow for nested objects
          rawCommand = "{";
          readingCommand = true;
        } else if (c == '}') {
          // Complete a command
          rawCommand += "}";
          Serial.print("Raw Command: ");
          Serial.println(rawCommand);
    
          String results = processJsonCommand(rawCommand);
          
          Serial.println(results);
          altSerial.println(results);
          readingCommand = false;
        } else if (readingCommand) {
          rawCommand += c;
        }
      }
    }
    
    String getStatus() {
      String ret = String("[Bluetooth] ");
      ret.concat(String("Enabled: "));ret.concat(isBluetoothEnabled);
      
      return ret;
    }
};

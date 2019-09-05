#include <ArduinoJson.h>

#include <AltSoftSerial.h>
#include <EEPROM.h>

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

// This example code is in the public domain.

AltSoftSerial altSerial;

int blueLed = 29;
int redLed = 30;
boolean blue = false;
boolean red = false;

String rawCommand = "";
boolean readingCommand = false;

const unsigned int EE_ADDRESS = 0;
const int CURRENT_SETTINGS_VERSION = 1;

struct ConfigurationEntry {
  String name;
  unsigned int eeAddress;
  String dataType;
  boolean booleanValue;
  int intValue;
  String stringValue;
};

#define NUMBER_OF_CONFIGURATION_ENTRIES 13

ConfigurationEntry configurationEntries[] = {
  {"version", 0, "Integer", false, CURRENT_SETTINGS_VERSION, ""},
  {"maxSpeed", 4, "Integer", false, 50, ""},
  {"actuatorCenter", 8, "Integer", false, 512, ""},
  {"actuatorMin", 12, "Integer", false, 200, ""},
  {"actuatorMax", 16, "Integer", false, 800, ""},
  {"useJoystick", 20, "Boolean", true, 0, ""},
  {"invertJoystickX", 24, "Boolean", false, 0, ""},
  {"invertJoystickY", 28, "Boolean", false, 0, ""},
  {"useRc", 32, "Boolean", false, 1, ""},
  {"usePotGo", 36, "Boolean", false, 0, ""},
  {"steeringPotCenter", 40, "Integer", false, 512, ""},
  {"steeringPotMin", 44, "Integer", false, 300, ""},
  {"steeringPotMax", 48, "Integer", false, 700, ""}
};

StaticJsonDocument<1024> currentSettingsJson;
StaticJsonDocument<1024> currentCommandJson;
  
JsonDocument loadConfigurationSettingsAsJson() {
  int intValue;
  boolean booleanValue;
  
  for (int i = 0; i < NUMBER_OF_CONFIGURATION_ENTRIES; i++) {
    ConfigurationEntry entry = configurationEntries[i];
    if (entry.dataType == "Integer") {
      EEPROM.get(entry.eeAddress, intValue);
      currentSettingsJson[entry.name] = intValue;
    } else if (entry.dataType == "Boolean") {
      EEPROM.get(entry.eeAddress, booleanValue);
      currentSettingsJson[entry.name] = booleanValue;
    } else {
      // ignore for now
    }
  }
}

void lightLeds() {
  boolean blueLedOn = currentSettingsJson["useJoystick"];
  boolean redLedOn = currentSettingsJson["useRc"];

  digitalWrite(blueLed, blueLedOn);
  digitalWrite(redLed, redLedOn);
}

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(blueLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  loadConfigurationSettingsAsJson();
  
  Serial.begin(9600);
  altSerial.begin(9600);
  
  Serial.print("Version: ");
  int version = currentSettingsJson["version"];
  Serial.println(version);

  Serial.print("Max Speed: ");
  int maxSpeed = currentSettingsJson["maxSpeed"];
  Serial.println(maxSpeed);

  lightLeds();
}

void loop() {
  char c;

  if (Serial.available()) {
    c = Serial.read();
    altSerial.print(c);
  }
  if (altSerial.available()) {
    c = altSerial.read();
    //Serial.print(c);

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
    serializeJson(currentSettingsJson, returnVal);
  } else if (command == "Set") {
    returnVal = processSetCommand();
    lightLeds();
  } else if (command == "Reset") {
    returnVal = processResetCommand();
    lightLeds();
  } else if (command == "Clear") {
    for (unsigned int i = 0 ; i < EEPROM.length() ; i++)
      EEPROM.write(i, 0);

    returnVal = "EEPROM Cleared";
  } else if (command == "Blue") {
    blue = !blue;
    digitalWrite(blueLed, blue);
    returnVal = "Acknowledged Blue"; 
  } else if (command == "Red") {
    red = !red;
    digitalWrite(redLed, red);
    returnVal = "Acknowledged Red";    
  }

  return returnVal;
}

String processSetCommand() {
  for (int i = 0; i < NUMBER_OF_CONFIGURATION_ENTRIES; i++) {
    ConfigurationEntry entry = configurationEntries[i];
    if (currentCommandJson.containsKey(entry.name)) {
      if (entry.dataType == "Integer") {
        int value = currentCommandJson[entry.name];
        Serial.print("Setting Value For: ");
        Serial.print(entry.name);
        Serial.print("  value: ");
        Serial.print(value);
        EEPROM.put(entry.eeAddress, value);
        currentSettingsJson[entry.name] = currentCommandJson[entry.name];
      } else if (entry.dataType == "Boolean") {
        Serial.print(entry.name);
        Serial.print(": ");
        boolean booleanValue = currentCommandJson[entry.name];
        Serial.println(booleanValue);
        if (currentCommandJson[entry.name]) {
          EEPROM.put(entry.eeAddress, 1);
          currentSettingsJson[entry.name] = true;
        } else {
          EEPROM.put(entry.eeAddress, 0);
          currentSettingsJson[entry.name] = false;
        }
      } else {
        // ignore for now
      }
    }
  }
  
  return "{\"Success\": true}";
}

String processResetCommand() {
  for (int i = 0; i < NUMBER_OF_CONFIGURATION_ENTRIES; i++) {
    ConfigurationEntry entry = configurationEntries[i];
    if (entry.dataType == "Integer") {
      EEPROM.put(entry.eeAddress, entry.intValue);
      currentSettingsJson[entry.name] = entry.intValue;
    } else if (entry.dataType == "Boolean") {
      EEPROM.put(entry.eeAddress, entry.booleanValue);
      currentSettingsJson[entry.name] = entry.booleanValue;
    } else {
      // ignore for now
    }
  }
  
  return "{\"Success\": true}";
}

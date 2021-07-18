#include <bluefruit.h>

/**
 * Bluetooth Class
 * 
 * This class serves to send and receive Bluetooth 4.0 BLE messages for saving and retrieving Configuration values.
 * This class is meant to be used with the Ionic Geeks Car Configuration app
 */

// GUID for Service: d18dd040-9000-42db-abba-1e23f3dd1d67
const uint8_t UUID128_SERVICE_GEEK[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x00, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};

BLEService        geeksService = BLEService(UUID128_SERVICE_GEEK);
BLEDis bledis;    // DIS (Device Information Service) helper class instance

#define CHARACTERISTIC_COUNT  18

#define STEERING_MIN        0x01
#define STEERING_CENTER     0x02
#define STEERING_MAX        0x03
#define RC_ENABLE           0x04
#define RC_STEERING_MIN     0x05
#define RC_STEERING_CENTER  0x06
#define RC_STEERING_MAX     0x07
#define RC_THROTTLE_MIN     0x08
#define RC_THROTTLE_CENTER  0x09
#define RC_THROTTLE_MAX     0x0A
#define CHILD_INVERT_STEERING 0x0B
#define CHILD_INVERT_THROTTLE 0x0C
#define CHILD_STEERING_MIN    0x0D
#define CHILD_STEERING_CENTER 0x0E
#define CHILD_STEERING_MAX    0x0F
#define CHILD_THROTTLE_MIN    0x10
#define CHILD_THROTTLE_CENTER 0x11
#define CHILD_THROTTLE_MAX    0x12

// The BLECharacteristics must be defined as global variables
BLECharacteristic steeringMinCharacteristic = BLECharacteristic(STEERING_MIN);
BLECharacteristic steeringCenterCharacteristic = BLECharacteristic(STEERING_CENTER);
BLECharacteristic steeringMaxCharacteristic = BLECharacteristic(STEERING_MAX);
BLECharacteristic rcEnableCharacteristic = BLECharacteristic(RC_ENABLE);
BLECharacteristic rcSteeringMinCharacteristic = BLECharacteristic(RC_STEERING_MIN);
BLECharacteristic rcSteeringCenterCharacteristic = BLECharacteristic(RC_STEERING_CENTER);
BLECharacteristic rcSteeringMaxCharacteristic = BLECharacteristic(RC_STEERING_MAX);
BLECharacteristic rcThrottleMinCharacteristic = BLECharacteristic(RC_THROTTLE_MIN);
BLECharacteristic rcThrottleCenterCharacteristic = BLECharacteristic(RC_THROTTLE_CENTER);
BLECharacteristic rcThrottleMaxCharacteristic = BLECharacteristic(RC_THROTTLE_MAX);
BLECharacteristic childInvertSteeringCharacteristic = BLECharacteristic(CHILD_INVERT_STEERING);
BLECharacteristic childInvertThrottleCharacteristic = BLECharacteristic(CHILD_INVERT_THROTTLE);
BLECharacteristic childSteeringMinCharacteristic = BLECharacteristic(CHILD_STEERING_MIN);
BLECharacteristic childSteeringCenterCharacteristic = BLECharacteristic(CHILD_STEERING_CENTER);
BLECharacteristic childSteeringMaxCharacteristic = BLECharacteristic(CHILD_STEERING_MAX);
BLECharacteristic childThrottleMinCharacteristic = BLECharacteristic(CHILD_THROTTLE_MIN);
BLECharacteristic childThrottleCenterCharacteristic = BLECharacteristic(CHILD_THROTTLE_CENTER);
BLECharacteristic childThrottleMaxCharacteristic = BLECharacteristic(CHILD_THROTTLE_MAX);

struct ConfigurationEntry {
  uint8_t id;
  String dataType;
  BLECharacteristic *characteristic;
};

ConfigurationEntry configurationEntries[] = {
  {STEERING_MIN, "Integer", &steeringMinCharacteristic},    // in scaled units from -100 to 100
  {STEERING_CENTER, "Integer", &steeringCenterCharacteristic},   // in scaled units from -100 to 100
  {STEERING_MAX, "Integer", &steeringMaxCharacteristic},     // in scaled units from -100 to 100
  {RC_ENABLE, "Boolean", &rcEnableCharacteristic},
  {RC_STEERING_MIN, "Integer", &rcSteeringMinCharacteristic},
  {RC_STEERING_CENTER, "Integer", &rcSteeringCenterCharacteristic},
  {RC_STEERING_MAX, "Integer", &rcSteeringMaxCharacteristic},
  {RC_THROTTLE_MIN, "Integer", &rcThrottleMinCharacteristic},
  {RC_THROTTLE_CENTER, "Integer", &rcThrottleCenterCharacteristic},
  {RC_THROTTLE_MAX, "Integer", &rcThrottleMaxCharacteristic},
  {CHILD_INVERT_STEERING, "Boolean", &childInvertSteeringCharacteristic},
  {CHILD_INVERT_THROTTLE, "Boolean", &childInvertThrottleCharacteristic},
  {CHILD_STEERING_MIN, "Integer", &childSteeringMinCharacteristic},
  {CHILD_STEERING_CENTER, "Integer", &childSteeringCenterCharacteristic},
  {CHILD_STEERING_MAX, "Integer", &childSteeringMaxCharacteristic},
  {CHILD_THROTTLE_MIN, "Integer", &childThrottleMinCharacteristic},
  {CHILD_THROTTLE_CENTER, "Integer", &childThrottleCenterCharacteristic},
  {CHILD_THROTTLE_MAX, "Integer", &childThrottleMaxCharacteristic}
};

// TODO Make spi a member variable. To do this, we need to make the callback functions
// non-static.
Spi *blSpi;

class Bluetooth {
  private:
    String rawCommand = "";
    boolean readingCommand = false;
    int enableBluetoothButtonPin;
    boolean isBluetoothEnabled = false;

  public: 
    // Default constructor ... does nothing.  This allows us to delay setting the pins until we want to (via the init method).  
    Bluetooth() {  
    }

    /*
     * init - initialize the dip switch pins
     */
    void init(int enableBluetoothButtonPin, Spi *s) {  
      this->enableBluetoothButtonPin = enableBluetoothButtonPin;
      blSpi = s;
      pinMode(enableBluetoothButtonPin, INPUT_PULLUP);
    }

    void initBluetooth() {
      Serial.println("Bluetooth is enabled. Start advertising.");
      
      //Bluefruit.configUuid128Count(20);
      Bluefruit.begin();
      Bluefruit.setName("GeeksCar2021");
    
      // Set the connect/disconnect callback handlers
      Bluefruit.Periph.setConnectCallback(connect_callback);
      Bluefruit.Periph.setDisconnectCallback(disconnect_callback);
    
      // Configure and Start the Device Information Service
      bledis.setManufacturer("GeeksForKids");
      bledis.setModel("Geeks2021Car");
      bledis.begin();

      setupGeeksCarService();
    
      startAdvertising();
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

      isBluetoothEnabled = !digitalRead(enableBluetoothButtonPin);
    }
    
    void startAdvertising(void)
    {
      // Advertising packet
      Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
      Bluefruit.Advertising.addTxPower();
    
      Bluefruit.Advertising.addService(geeksService);
    
      // Include Name
      Bluefruit.Advertising.addName();
      Bluefruit.Advertising.restartOnDisconnect(true);
      Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
      Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
      Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds  
    }
    
    static void write_callback(uint16_t conn_hdl, BLECharacteristic* chr, uint8_t* data, uint16_t len)
    {
      int16_t valueInt16 = *((int16_t *)data);
      boolean valueBoolean = data[0] != 0;
    
      // The 2 byte UUID is incremeted for each characteristic from 1 to 255.
      uint16_t characteristicId;
      chr->uuid.get(&characteristicId);
    
      if (len == 2) {
        // Write the value back out so the BLE value gets inverted again
        // otherwise it is cached improperly and the next read by the client will have the wrong value
        chr->write16(invertByteOrderInt16(valueInt16));
      }
    
      ConfigurationEntry entry;
      for (int i = 0; i < CHARACTERISTIC_COUNT; i++) {
        entry = configurationEntries[i];
        boolean found = false;

        switch (characteristicId) {
          case STEERING_MIN:
            blSpi->currentSettings.actuatorMin = valueInt16;
            found = true;
            break;
          case STEERING_CENTER:
            blSpi->currentSettings.actuatorCenter = valueInt16;
            found = true;
            break;
          case STEERING_MAX:
            blSpi->currentSettings.actuatorMax = valueInt16;
            found = true;
            break;
          case RC_ENABLE:
            blSpi->currentSettings.useRc = valueBoolean;
            found = true;
            break;
          case RC_STEERING_MIN:
            blSpi->currentSettings.rcSteeringMin = valueInt16;
            found = true;
            break;
          case RC_STEERING_CENTER:
            blSpi->currentSettings.rcSteeringCenter = valueInt16;
            found = true;
            break;
          case RC_STEERING_MAX:
            blSpi->currentSettings.rcSteeringMax = valueInt16;
            found = true;
            break;
          case RC_THROTTLE_MIN:
            blSpi->currentSettings.rcThrottleMin = valueInt16;
            found = true;
            break;
          case RC_THROTTLE_CENTER:
            blSpi->currentSettings.rcThrottleCenter = valueInt16;
            found = true;
            break;
          case RC_THROTTLE_MAX:
            blSpi->currentSettings.rcThrottleMax = valueInt16;
            found = true;
            break;
          case CHILD_INVERT_STEERING:
            blSpi->currentSettings.invertJoystickX = valueBoolean;
            found = true;
            break;
          case CHILD_INVERT_THROTTLE:
            blSpi->currentSettings.invertJoystickY = valueBoolean;
            found = true;
            break;
          case CHILD_STEERING_MIN:
            blSpi->currentSettings.joystickSteeringMin = valueInt16;
            found = true;
            break;
          case CHILD_STEERING_CENTER:
            blSpi->currentSettings.joystickSteeringCenter = valueInt16;
            found = true;
            break;
          case CHILD_STEERING_MAX:
            blSpi->currentSettings.joystickSteeringMax = valueInt16;
            found = true;
            break;
          case CHILD_THROTTLE_MIN:
            blSpi->currentSettings.joystickThrottleMin = valueInt16;
            found = true;
            break;
          case CHILD_THROTTLE_CENTER:
            blSpi->currentSettings.joystickThrottleCenter = valueInt16;
            found = true;
            break;
          case CHILD_THROTTLE_MAX:
            blSpi->currentSettings.joystickThrottleMax = valueInt16;
            blSpi->saveToSpiFlash();
            found = true;
            break;
        }

        if (found) {
          break;
        }
      }
    }
    
    void setupGeeksCarService(void)
    {
      geeksService.begin();
    
      // Note: You must call .begin() on the BLEService before calling .begin() on
      // any characteristic(s) within that service definition.. Calling .begin() on
      // a BLECharacteristic will cause it to be added to the last BLEService that
      // was 'begin()'ed!
    
      ConfigurationEntry entry;
      for (int i = 0; i < CHARACTERISTIC_COUNT; i++) {
        entry = configurationEntries[i];
    
        entry.characteristic->setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
        entry.characteristic->setPermission(SECMODE_OPEN, SECMODE_OPEN);
        entry.characteristic->setWriteCallback(write_callback);
        entry.characteristic->setFixedLen(entry.dataType == "Boolean" ? 1 : 2);
        entry.characteristic->begin();

        switch (entry.id) {
          case STEERING_MIN:
            entry.characteristic->write16(invertByteOrderInt16(blSpi->currentSettings.actuatorMin));
            break;
          case STEERING_CENTER:
            entry.characteristic->write16(invertByteOrderInt16(blSpi->currentSettings.actuatorCenter));
            break;
          case STEERING_MAX:
            entry.characteristic->write16(invertByteOrderInt16(blSpi->currentSettings.actuatorMax));
            break;
          case RC_ENABLE:
            entry.characteristic->write8(blSpi->currentSettings.useRc);
            break;
          case RC_STEERING_MIN:
            entry.characteristic->write16(invertByteOrderInt16(blSpi->currentSettings.rcSteeringMin));
            break;
          case RC_STEERING_CENTER:
            entry.characteristic->write16(invertByteOrderInt16(blSpi->currentSettings.rcSteeringCenter));
            break;
          case RC_STEERING_MAX:
           entry.characteristic->write16(invertByteOrderInt16( blSpi->currentSettings.rcSteeringMax));
            break;
          case RC_THROTTLE_MIN:
            entry.characteristic->write16(invertByteOrderInt16(blSpi->currentSettings.rcThrottleMin));
            break;
          case RC_THROTTLE_CENTER:
            entry.characteristic->write16(invertByteOrderInt16(blSpi->currentSettings.rcThrottleCenter));
            break;
          case RC_THROTTLE_MAX:
            entry.characteristic->write16(invertByteOrderInt16(blSpi->currentSettings.rcThrottleMax));
            break;
          case CHILD_INVERT_STEERING:
            entry.characteristic->write8(blSpi->currentSettings.invertJoystickX);
            break;
          case CHILD_INVERT_THROTTLE:
            entry.characteristic->write8(blSpi->currentSettings.invertJoystickY);
            break;
          case CHILD_STEERING_MIN:
            entry.characteristic->write16(invertByteOrderInt16(blSpi->currentSettings.joystickSteeringMin));
            break;
          case CHILD_STEERING_CENTER:
            entry.characteristic->write16(invertByteOrderInt16(blSpi->currentSettings.joystickSteeringCenter));
            break;
          case CHILD_STEERING_MAX:
            entry.characteristic->write16(invertByteOrderInt16(blSpi->currentSettings.joystickSteeringMax));
            break;
          case CHILD_THROTTLE_MIN:
            entry.characteristic->write16(invertByteOrderInt16(blSpi->currentSettings.joystickThrottleMin));
            break;
          case CHILD_THROTTLE_CENTER:
            entry.characteristic->write16(invertByteOrderInt16(blSpi->currentSettings.joystickThrottleCenter));
            break;
          case CHILD_THROTTLE_MAX:
            entry.characteristic->write16(invertByteOrderInt16(blSpi->currentSettings.joystickThrottleMax));
            break;
        }
      }
    }
    
    static void connect_callback(uint16_t conn_handle)
    {
      // Get the reference to current connection
      BLEConnection* connection = Bluefruit.Connection(conn_handle);
    
      char central_name[32] = { 0 };
      connection->getPeerName(central_name, sizeof(central_name));
    
      Serial.print("Connected to ");
      Serial.println(central_name);
    }
    
    /**
     * Callback invoked when a connection is dropped
     * @param conn_handle connection where this event happens
     * @param reason is a BLE_HCI_STATUS_CODE which can be found in ble_hci.h
     */
    static void disconnect_callback(uint16_t conn_handle, uint8_t reason)
    {
      (void) conn_handle;
      (void) reason;
    
      Serial.print("Disconnected, reason = 0x"); Serial.println(reason, HEX);
      Serial.println("Advertising!");
    }
    
    static int16_t invertByteOrderInt16(int16_t value) {
      int16_t invertedValue;
      
      uint8_t *invertedBuffer = (uint8_t *)&invertedValue;
      uint8_t *tempReadBuffer = (uint8_t *)&value;
      
      invertedBuffer[0] = tempReadBuffer[1];
      invertedBuffer[1] = tempReadBuffer[0];
    
      return invertedValue;
    }

    void getStatus(char * status) {
      sprintf(status, "[Bluetooth] Enabled: %s", isBluetoothEnabled ? "true" : "false");
    }
};

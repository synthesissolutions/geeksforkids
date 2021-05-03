/*********************************************************************
 This is an example for our nRF52 based Bluefruit LE modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/
#include <bluefruit.h>

// GUID for Service: d18dd040-9000-42db-abba-1e23f3dd1d67
// GUIDs for Characteristics increment from 9001, 9002, etc.
const uint8_t UUID128_SERVICE_GEEK[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x00, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};

uint8_t UUID128_BASE_CHARACTERISTIC[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x00, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};

BLEService        geeksService = BLEService(UUID128_SERVICE_GEEK);
BLEDis bledis;    // DIS (Device Information Service) helper class instance

#define CHARACTERISTIC_COUNT  18

#define STEERING_MIN        1
#define STEERING_CENTER     2
#define STEERING_MAX        3
#define RC_ENABLE           4
#define RC_STEERING_MIN     5
#define RC_STEERING_CENTER  6
#define RC_STEERING_MAX     7
#define RC_THROTTLE_MIN     8
#define RC_THROTTLE_CENTER  9
#define RC_THROTTLE_MAX     10
#define CHILD_INVERT_STEERING 11
#define CHILD_INVERT_THROTTLE 12
#define CHILD_STEERING_MIN    13
#define CHILD_STEERING_CENTER 14
#define CHILD_STEERING_MAX    15
#define CHILD_THROTTLE_MIN    16
#define CHILD_THROTTLE_CENTER 17
#define CHILD_THROTTLE_MAX    18

BLECharacteristic steeringMinCharacteristic = BLECharacteristic(0x01);
BLECharacteristic steeringCenterCharacteristic = BLECharacteristic(0x02);
BLECharacteristic steeringMaxCharacteristic = BLECharacteristic(0x03);
BLECharacteristic rcEnableCharacteristic = BLECharacteristic(0x04);
BLECharacteristic rcSteeringMinCharacteristic = BLECharacteristic(0x05);
BLECharacteristic rcSteeringCenterCharacteristic = BLECharacteristic(0x06);
BLECharacteristic rcSteeringMaxCharacteristic = BLECharacteristic(0x07);
BLECharacteristic rcThrottleMinCharacteristic = BLECharacteristic(0x08);
BLECharacteristic rcThrottleCenterCharacteristic = BLECharacteristic(0x09);
BLECharacteristic rcThrottleMaxCharacteristic = BLECharacteristic(0x0A);
BLECharacteristic childInvertSteeringCharacteristic = BLECharacteristic(0x0B);
BLECharacteristic childInvertThrottleCharacteristic = BLECharacteristic(0x0C);
BLECharacteristic childSteeringMinCharacteristic = BLECharacteristic(0x0D);
BLECharacteristic childSteeringCenterCharacteristic = BLECharacteristic(0x0E);
BLECharacteristic childSteeringMaxCharacteristic = BLECharacteristic(0x0F);
BLECharacteristic childThrottleMinCharacteristic = BLECharacteristic(0x10);
BLECharacteristic childThrottleCenterCharacteristic = BLECharacteristic(0x11);
BLECharacteristic childThrottleMaxCharacteristic = BLECharacteristic(0x12);

struct ConfigurationEntry {
  uint8_t id;
  String dataType;
  boolean booleanValue;
  int intValue;
  BLECharacteristic *characteristic;
};

ConfigurationEntry configurationEntries[] = {
  {STEERING_MIN, "Integer", false, -50, &steeringMinCharacteristic},    // in scaled units from -100 to 100
  {STEERING_CENTER, "Integer", false, 0, &steeringCenterCharacteristic},   // in scaled units from -100 to 100
  {STEERING_MAX, "Integer", false, 50, &steeringMaxCharacteristic},     // in scaled units from -100 to 100
  {RC_ENABLE, "Boolean", true, 0, &rcEnableCharacteristic},
  {RC_STEERING_MIN, "Integer", false, 33, &rcSteeringMinCharacteristic},
  {RC_STEERING_CENTER, "Integer", false, 50, &rcSteeringCenterCharacteristic},
  {RC_STEERING_MAX, "Integer", false, 80, &rcSteeringMaxCharacteristic},
  {RC_THROTTLE_MIN, "Integer", false, 33, &rcThrottleMinCharacteristic},
  {RC_THROTTLE_CENTER, "Integer", false, 50, &rcThrottleCenterCharacteristic},
  {RC_THROTTLE_MAX, "Integer", false, 80, &rcThrottleMaxCharacteristic},
  {CHILD_INVERT_STEERING, "Boolean", false, 0, &childInvertSteeringCharacteristic},
  {CHILD_INVERT_THROTTLE, "Boolean", false, 0, &childInvertThrottleCharacteristic},
  {CHILD_STEERING_MIN, "Integer", false, 25, &childSteeringMinCharacteristic},
  {CHILD_STEERING_CENTER, "Integer", false, 512, &childSteeringCenterCharacteristic},
  {CHILD_STEERING_MAX, "Integer", false, 1000, &childSteeringMaxCharacteristic},
  {CHILD_THROTTLE_MIN, "Integer", false, 25, &childThrottleMinCharacteristic},
  {CHILD_THROTTLE_CENTER, "Integer", false, 512, &childThrottleCenterCharacteristic},
  {CHILD_THROTTLE_MAX, "Integer", false, 1000, &childThrottleMaxCharacteristic}
};

void setup()
{
  Serial.begin(115200);
  while ( !Serial ) delay(10);   // for nrf52840 with native usb

  Serial.println("Geeks Configuration Example");

  // Initialise the Bluefruit module
  Serial.println("Initialise the Bluefruit nRF52 module");
  Bluefruit.configUuid128Count(20);
  Bluefruit.begin();
  Bluefruit.setName("GeeksCar2021");

  // Set the connect/disconnect callback handlers
  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);

  // Configure and Start the Device Information Service
  Serial.println("Configuring the Device Information Service");
  bledis.setManufacturer("GeeksForKids");
  bledis.setModel("Geeks2021Car");
  bledis.begin();

  Serial.println("Configuring the Geeks Car Configuration Service");
  setupGeeksCarService();

  // Setup the advertising packet(s)
  Serial.println("Setting up the advertising payload(s)");
  startAdvertising();

  Serial.println("\nAdvertising");
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

void write_callback(uint16_t conn_hdl, BLECharacteristic* chr, uint8_t* data, uint16_t len)
{
  Serial.println("in write_callback");
  int16_t valueInt16 = *((int16_t *)data);
  boolean valueBoolean = data[0] != 0;

  // The 10th byte is incremeted for each characteristic from 1 to 255. The service has 0 in this byte.
  int8_t characteristicId = chr->uuid._uuid128[10];
  Serial.println("in write_callback");
  Serial.println(characteristicId);

  if (len == 2) {
    // Write the value back out so the BLE value gets inverted again
    // otherwise it is cached improperly and the next read by the client will have the wrong value
    chr->write16(invertByteOrderInt16(valueInt16));
    Serial.print("int16: ");
    Serial.println(valueInt16);
  }

  ConfigurationEntry entry;
  for (int i = 0; i < CHARACTERISTIC_COUNT; i++) {
    entry = configurationEntries[i];
    if (entry.id == characteristicId) {
      Serial.print("Found Entry for: ");
      Serial.println(characteristicId);
      if (entry.dataType == "Boolean") {
        entry.booleanValue = valueBoolean;
      } else if (entry.dataType == "Integer") {
        entry.intValue = valueInt16;
      }

      break;
    }
  }

  // TODO Save new values to storage
}

void setupGeeksCarService(void)
{
  geeksService.begin();

  // Note: You must call .begin() on the BLEService before calling .begin() on
  // any characteristic(s) within that service definition.. Calling .begin() on
  // a BLECharacteristic will cause it to be added to the last BLEService that
  // was 'begin()'ed!

/*
  steeringMinCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  steeringMinCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  steeringMinCharacteristic.setWriteCallback(write_callback);
  steeringMinCharacteristic.setFixedLen(2);
  steeringMinCharacteristic.begin();
  steeringMinCharacteristic.write16(invertByteOrderInt16(configurationEntries[0].intValue));
  steeringCenterCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  steeringCenterCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  steeringCenterCharacteristic.setWriteCallback(write_callback);
  steeringCenterCharacteristic.setFixedLen(2);
  steeringCenterCharacteristic.begin();
  steeringCenterCharacteristic.write16(invertByteOrderInt16(configurationEntries[1].intValue));
  steeringMaxCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  steeringMaxCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  steeringMaxCharacteristic.setWriteCallback(write_callback);
  steeringMaxCharacteristic.setFixedLen(2);
  steeringMaxCharacteristic.begin();
  steeringMaxCharacteristic.write16(invertByteOrderInt16(configurationEntries[2].intValue));
  rcEnableCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  rcEnableCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  rcEnableCharacteristic.setWriteCallback(write_callback);
  rcEnableCharacteristic.setFixedLen(1);
  rcEnableCharacteristic.begin();
  rcEnableCharacteristic.write8(configurationEntries[3].booleanValue);
  rcSteeringMinCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  rcSteeringMinCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  rcSteeringMinCharacteristic.setWriteCallback(write_callback);
  rcSteeringMinCharacteristic.setFixedLen(2);
  rcSteeringMinCharacteristic.begin();
  rcSteeringMinCharacteristic.write16(invertByteOrderInt16(configurationEntries[4].intValue));
  rcSteeringCenterCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  rcSteeringCenterCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  rcSteeringCenterCharacteristic.setWriteCallback(write_callback);
  rcSteeringCenterCharacteristic.setFixedLen(2);
  rcSteeringCenterCharacteristic.begin();
  rcSteeringCenterCharacteristic.write16(invertByteOrderInt16(configurationEntries[5].intValue));
  rcSteeringMaxCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  rcSteeringMaxCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  rcSteeringMaxCharacteristic.setWriteCallback(write_callback);
  rcSteeringMaxCharacteristic.setFixedLen(2);
  rcSteeringMaxCharacteristic.begin();
  rcSteeringMaxCharacteristic.write16(invertByteOrderInt16(configurationEntries[6].intValue));
  rcThrottleMinCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  rcThrottleMinCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  rcThrottleMinCharacteristic.setWriteCallback(write_callback);
  rcThrottleMinCharacteristic.setFixedLen(2);
  rcThrottleMinCharacteristic.begin();
  rcThrottleMinCharacteristic.write16(invertByteOrderInt16(configurationEntries[7].intValue));
  rcThrottleCenterCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  rcThrottleCenterCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  rcThrottleCenterCharacteristic.setWriteCallback(write_callback);
  rcThrottleCenterCharacteristic.setFixedLen(2);
  rcThrottleCenterCharacteristic.begin();
  rcThrottleCenterCharacteristic.write16(invertByteOrderInt16(configurationEntries[8].intValue));
  rcThrottleMaxCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  rcThrottleMaxCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  rcThrottleMaxCharacteristic.setWriteCallback(write_callback);
  rcThrottleMaxCharacteristic.setFixedLen(2);
  rcThrottleMaxCharacteristic.begin();
  rcThrottleMaxCharacteristic.write16(invertByteOrderInt16(configurationEntries[9].intValue));
  childInvertSteeringCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  childInvertSteeringCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  childInvertSteeringCharacteristic.setWriteCallback(write_callback);
  childInvertSteeringCharacteristic.setFixedLen(1);
  childInvertSteeringCharacteristic.begin();
  childInvertSteeringCharacteristic.write8(configurationEntries[10].booleanValue);
  childInvertThrottleCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  childInvertThrottleCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  childInvertThrottleCharacteristic.setWriteCallback(write_callback);
  childInvertThrottleCharacteristic.setFixedLen(1);
  childInvertThrottleCharacteristic.begin();
  childInvertThrottleCharacteristic.write8(configurationEntries[11].booleanValue);
  childSteeringMinCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  childSteeringMinCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  childSteeringMinCharacteristic.setWriteCallback(write_callback);
  childSteeringMinCharacteristic.setFixedLen(2);
  childSteeringMinCharacteristic.begin();
  childSteeringMinCharacteristic.write16(invertByteOrderInt16(configurationEntries[12].intValue));
  childSteeringCenterCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  childSteeringCenterCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  childSteeringCenterCharacteristic.setWriteCallback(write_callback);
  childSteeringCenterCharacteristic.setFixedLen(2);
  childSteeringCenterCharacteristic.begin();
  childSteeringCenterCharacteristic.write16(invertByteOrderInt16(configurationEntries[13].intValue));
  childSteeringMaxCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  childSteeringMaxCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  childSteeringMaxCharacteristic.setWriteCallback(write_callback);
  childSteeringMaxCharacteristic.setFixedLen(2);
  childSteeringMaxCharacteristic.begin();
  childSteeringMaxCharacteristic.write16(invertByteOrderInt16(configurationEntries[14].intValue));
  childThrottleMinCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  childThrottleMinCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  childThrottleMinCharacteristic.setWriteCallback(write_callback);
  childThrottleMinCharacteristic.setFixedLen(2);
  childThrottleMinCharacteristic.begin();
  childThrottleMinCharacteristic.write16(invertByteOrderInt16(configurationEntries[15].intValue));
  childThrottleCenterCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  childThrottleCenterCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  childThrottleCenterCharacteristic.setWriteCallback(write_callback);
  childThrottleCenterCharacteristic.setFixedLen(2);
  childThrottleCenterCharacteristic.begin();
  childThrottleCenterCharacteristic.write16(invertByteOrderInt16(configurationEntries[16].intValue));
  childThrottleMaxCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  childThrottleMaxCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  childThrottleMaxCharacteristic.setWriteCallback(write_callback);
  childThrottleMaxCharacteristic.setFixedLen(2);
  childThrottleMaxCharacteristic.begin();
  childThrottleMaxCharacteristic.write16(invertByteOrderInt16(configurationEntries[17].intValue));
  */

  ConfigurationEntry entry;
  for (int i = 0; i < CHARACTERISTIC_COUNT; i++) {
    entry = configurationEntries[i];

    UUID128_BASE_CHARACTERISTIC[10] = entry.id;
    //entry.characteristic = BLECharacteristic(UUID128_BASE_CHARACTERISTIC);
    entry.characteristic->setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
    entry.characteristic->setPermission(SECMODE_OPEN, SECMODE_OPEN);
    entry.characteristic->setWriteCallback(write_callback);
    entry.characteristic->setFixedLen(entry.dataType == "Boolean" ? 1 : 2);
    entry.characteristic->begin();

    if (entry.dataType == "Boolean") {
      entry.characteristic->write8(entry.booleanValue);
    } else if (entry.dataType == "Integer") {
      Serial.print("before: ");
      Serial.println(entry.intValue);
      entry.characteristic->write16(invertByteOrderInt16(entry.intValue));
      Serial.print("after: ");
      Serial.println(entry.intValue);
    }    
  }
}

void connect_callback(uint16_t conn_handle)
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
void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;

  Serial.print("Disconnected, reason = 0x"); Serial.println(reason, HEX);
  Serial.println("Advertising!");
}

int16_t invertByteOrderInt16(int16_t value) {
  int16_t invertedValue;
  
  uint8_t *invertedBuffer = (uint8_t *)&invertedValue;
  uint8_t *tempReadBuffer = (uint8_t *)&value;
  
  invertedBuffer[0] = tempReadBuffer[1];
  invertedBuffer[1] = tempReadBuffer[0];

  return invertedValue;
}

void loop()
{
  digitalToggle(LED_RED);
  
  if ( Bluefruit.connected() ) {
    // nothing to do here for now
  }

  // Only send update once per second
  delay(1000);
}

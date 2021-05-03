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

/*
const uint8_t UUID128_CHR_STEERING_MIN[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x01, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};

const uint8_t UUID128_CHR_STEERING_CENTER[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x02, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};

const uint8_t UUID128_CHR_STEERING_MAX[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x03, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};

const uint8_t UUID128_CHR_RC_ENABLE[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x04, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};

const uint8_t UUID128_CHR_RC_STEERING_MIN[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x05, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};

const uint8_t UUID128_CHR_RC_STEERING_CENTER[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x06, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};

const uint8_t UUID128_CHR_RC_STEERING_MAX[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x07, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};

const uint8_t UUID128_CHR_RC_THROTTLE_MIN[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x08, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};

const uint8_t UUID128_CHR_RC_THROTTLE_CENTER[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x09, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};

const uint8_t UUID128_CHR_RC_THROTTLE_MAX[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x0A, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};

const uint8_t UUID128_CHR_CHILD_INVERT_STEERING[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x0B, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};

const uint8_t UUID128_CHR_CHILD_INVERT_THROTTLE[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x0C, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};

const uint8_t UUID128_CHR_CHILD_STEERING_MIN[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x0D, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};

const uint8_t UUID128_CHR_CHILD_STEERING_CENTER[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x0E, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};

const uint8_t UUID128_CHR_CHILD_STEERING_MAX[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x0F, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};

const uint8_t UUID128_CHR_CHILD_THROTTLE_MIN[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x10, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};

const uint8_t UUID128_CHR_CHILD_THROTTLE_CENTER[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x11, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};

const uint8_t UUID128_CHR_CHILD_THROTTLE_MAX[16] =
{
    0x67, 0x1D, 0xDD, 0xF3, 0x23, 0x1E, 0xBA, 0xAB,
    0xDB, 0x42, 0x12, 0x90, 0x40, 0xD0, 0x8D, 0xD1
};
*/
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

struct ConfigurationEntry {
  uint8_t id;
  String dataType;
  boolean booleanValue;
  int intValue;
};

ConfigurationEntry configurationEntries[] = {
  {STEERING_MIN, "Integer", false, -50},    // in scaled units from -100 to 100
  {STEERING_CENTER, "Integer", false, 0},   // in scaled units from -100 to 100
  {STEERING_MAX, "Integer", false, 50},     // in scaled units from -100 to 100
  {RC_ENABLE, "Boolean", true, 0},
  {RC_STEERING_MIN, "Integer", false, 33},
  {RC_STEERING_CENTER, "Integer", false, 50},
  {RC_STEERING_MAX, "Integer", false, 80},
  {RC_THROTTLE_MIN, "Integer", false, 33},
  {RC_THROTTLE_CENTER, "Integer", false, 50},
  {RC_THROTTLE_MAX, "Integer", false, 80},
  {CHILD_INVERT_STEERING, "Boolean", false, 0},
  {CHILD_INVERT_THROTTLE, "Boolean", false, 0},
  {CHILD_STEERING_MIN, "Integer", false, 25},
  {CHILD_STEERING_CENTER, "Integer", false, 512},
  {CHILD_STEERING_MAX, "Integer", false, 1000},
  {CHILD_THROTTLE_MIN, "Integer", false, 25},
  {CHILD_THROTTLE_CENTER, "Integer", false, 512},
  {CHILD_THROTTLE_MAX, "Integer", false, 1000}
};

BLEService        geeksService = BLEService(UUID128_SERVICE_GEEK);

/*
BLECharacteristic steeringMinCharacteristic = BLECharacteristic(UUID128_CHR_STEERING_MIN);
BLECharacteristic steeringCenterCharacteristic = BLECharacteristic(UUID128_CHR_STEERING_CENTER);
BLECharacteristic steeringMaxCharacteristic = BLECharacteristic(UUID128_CHR_STEERING_MAX);
BLECharacteristic rcEnableCharacteristic = BLECharacteristic(UUID128_CHR_RC_ENABLE);
BLECharacteristic rcSteeringMinCharacteristic = BLECharacteristic(UUID128_CHR_RC_STEERING_MIN);
BLECharacteristic rcSteeringCenterCharacteristic = BLECharacteristic(UUID128_CHR_RC_STEERING_CENTER);
BLECharacteristic rcSteeringMaxCharacteristic = BLECharacteristic(UUID128_CHR_RC_STEERING_MAX);
BLECharacteristic rcThrottleMinCharacteristic = BLECharacteristic(UUID128_CHR_RC_THROTTLE_MIN);
BLECharacteristic rcThrottleCenterCharacteristic = BLECharacteristic(UUID128_CHR_RC_THROTTLE_CENTER);
BLECharacteristic rcThrottleMaxCharacteristic = BLECharacteristic(UUID128_CHR_RC_THROTTLE_MAX);
BLECharacteristic childInvertSteeringCharacteristic = BLECharacteristic(UUID128_CHR_CHILD_INVERT_STEERING);
BLECharacteristic childInvertThrottleCharacteristic = BLECharacteristic(UUID128_CHR_CHILD_INVERT_THROTTLE);
BLECharacteristic childSteeringMinCharacteristic = BLECharacteristic(UUID128_CHR_CHILD_STEERING_MIN);
BLECharacteristic childSteeringCenterCharacteristic = BLECharacteristic(UUID128_CHR_CHILD_STEERING_CENTER);
BLECharacteristic childSteeringMaxCharacteristic = BLECharacteristic(UUID128_CHR_CHILD_STEERING_MAX);
BLECharacteristic childThrottleMinCharacteristic = BLECharacteristic(UUID128_CHR_CHILD_THROTTLE_MIN);
BLECharacteristic childThrottleCenterCharacteristic = BLECharacteristic(UUID128_CHR_CHILD_THROTTLE_CENTER);
BLECharacteristic childThrottleMaxCharacteristic = BLECharacteristic(UUID128_CHR_CHILD_THROTTLE_MAX);
*/
BLEDis bledis;    // DIS (Device Information Service) helper class instance

/*
int16_t steeringMin = -50;
int16_t steeringCenter = 0;
int16_t steeringMax = 50;

int8_t rcEnable = false;
int16_t rcSteeringMin = 33;
int16_t rcSteeringCenter = 57;
int16_t rcSteeringMax = 80;
int16_t rcThrottleMin = 33;
int16_t rcThrottleCenter = 57;
int16_t rcThrottleMax = 80;

int8_t childInvertSteering = false;
int8_t childInvertThrottle = true;
int16_t childSteeringMin = 25;
int16_t childSteeringCenter = 512;
int16_t childSteeringMax = 1000;
int16_t childThrottleMin = 25;
int16_t childThrottleCenter = 512;
int16_t childThrottleMax = 1000;
*/
void setup()
{
  Serial.begin(115200);
  while ( !Serial ) delay(10);   // for nrf52840 with native usb

  Serial.println("Bluefruit52 HRM Example");
  Serial.println("-----------------------\n");

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

  // Include HRM Service UUID
  Bluefruit.Advertising.addService(geeksService);

  // Include Name
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds  
}

void setupGeeksCarService(void)
{
  geeksService.begin();

  // Note: You must call .begin() on the BLEService before calling .begin() on
  // any characteristic(s) within that service definition.. Calling .begin() on
  // a BLECharacteristic will cause it to be added to the last BLEService that
  // was 'begin()'ed!

  Serial.println("before loop");
  Serial.println(CHARACTERISTIC_COUNT);
  ConfigurationEntry entry;
  for (int i = 0; i < CHARACTERISTIC_COUNT; i++) {
    Serial.println("in loop");
    entry = configurationEntries[i];

    UUID128_BASE_CHARACTERISTIC[10] = entry.id;
    BLECharacteristic characteristic = BLECharacteristic(UUID128_BASE_CHARACTERISTIC);
    characteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
    characteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
    characteristic.setWriteCallback(write_callback);
    characteristic.setFixedLen(entry.dataType == "Boolean" ? 1 : 2);
    characteristic.begin();

    Serial.print("Begin for characteristic: ");
    Serial.println(entry.id);
    if (entry.dataType == "Boolean") {
      characteristic.write8(entry.booleanValue);
      Serial.print(" value: ");
      Serial.println(entry.booleanValue);
    } else if (entry.dataType == "Integer") {
      characteristic.write16(invertByteOrderInt16(entry.intValue));
      Serial.print(" value: ");
      Serial.println(entry.intValue);
    }
    
  }

/*
  steeringCenterCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  steeringCenterCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  steeringCenterCharacteristic.setWriteCallback(write_callback);
  steeringCenterCharacteristic.setFixedLen(2);
  steeringCenterCharacteristic.begin();
  steeringCenterCharacteristic.write16(invertByteOrderInt16(steeringCenter));

  steeringMaxCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  steeringMaxCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  steeringMaxCharacteristic.setWriteCallback(write_callback);
  steeringMaxCharacteristic.setFixedLen(2);
  steeringMaxCharacteristic.begin();
  steeringMaxCharacteristic.write16(invertByteOrderInt16(steeringMax));

  rcEnableCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  rcEnableCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  rcEnableCharacteristic.setWriteCallback(write_callback);
  rcEnableCharacteristic.setFixedLen(1);
  rcEnableCharacteristic.begin();
  rcEnableCharacteristic.write8(rcEnable);

  rcSteeringMinCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  rcSteeringMinCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  rcSteeringMinCharacteristic.setWriteCallback(write_callback);
  rcSteeringMinCharacteristic.setFixedLen(2);
  rcSteeringMinCharacteristic.begin();
  rcSteeringMinCharacteristic.write16(invertByteOrderInt16(rcSteeringMin));

  rcSteeringCenterCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  rcSteeringCenterCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  rcSteeringCenterCharacteristic.setWriteCallback(write_callback);
  rcSteeringCenterCharacteristic.setFixedLen(2);
  rcSteeringCenterCharacteristic.begin();
  rcSteeringCenterCharacteristic.write16(invertByteOrderInt16(rcSteeringCenter));

  rcSteeringMaxCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  rcSteeringMaxCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  rcSteeringMaxCharacteristic.setWriteCallback(write_callback);
  rcSteeringMaxCharacteristic.setFixedLen(2);
  rcSteeringMaxCharacteristic.begin();
  rcSteeringMaxCharacteristic.write16(invertByteOrderInt16(rcSteeringMax));

  rcThrottleMinCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  rcThrottleMinCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  rcThrottleMinCharacteristic.setWriteCallback(write_callback);
  rcThrottleMinCharacteristic.setFixedLen(2);
  rcThrottleMinCharacteristic.begin();
  rcThrottleMinCharacteristic.write16(invertByteOrderInt16(rcThrottleMin));

  rcThrottleCenterCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  rcThrottleCenterCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  rcThrottleCenterCharacteristic.setWriteCallback(write_callback);
  rcThrottleCenterCharacteristic.setFixedLen(2);
  rcThrottleCenterCharacteristic.begin();
  rcThrottleCenterCharacteristic.write16(invertByteOrderInt16(rcThrottleCenter));

  rcThrottleMaxCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  rcThrottleMaxCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  rcThrottleMaxCharacteristic.setWriteCallback(write_callback);
  rcThrottleMaxCharacteristic.setFixedLen(2);
  rcThrottleMaxCharacteristic.begin();
  rcThrottleMaxCharacteristic.write16(invertByteOrderInt16(rcThrottleMax));

  childInvertSteeringCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  childInvertSteeringCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  childInvertSteeringCharacteristic.setWriteCallback(write_callback);
  childInvertSteeringCharacteristic.setFixedLen(1);
  childInvertSteeringCharacteristic.begin();
  childInvertSteeringCharacteristic.write8(childInvertSteering);

  childInvertThrottleCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  childInvertThrottleCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  childInvertThrottleCharacteristic.setWriteCallback(write_callback);
  childInvertThrottleCharacteristic.setFixedLen(1);
  childInvertThrottleCharacteristic.begin();
  childInvertThrottleCharacteristic.write8(childInvertThrottle);

  childSteeringMinCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  childSteeringMinCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  childSteeringMinCharacteristic.setWriteCallback(write_callback);
  childSteeringMinCharacteristic.setFixedLen(2);
  childSteeringMinCharacteristic.begin();
  childSteeringMinCharacteristic.write16(invertByteOrderInt16(childSteeringMin));

  childSteeringCenterCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  childSteeringCenterCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  childSteeringCenterCharacteristic.setWriteCallback(write_callback);
  childSteeringCenterCharacteristic.setFixedLen(2);
  childSteeringCenterCharacteristic.begin();
  childSteeringCenterCharacteristic.write16(invertByteOrderInt16(childSteeringCenter));

  childSteeringMaxCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  childSteeringMaxCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  childSteeringMaxCharacteristic.setWriteCallback(write_callback);
  childSteeringMaxCharacteristic.setFixedLen(2);
  childSteeringMaxCharacteristic.begin();
  childSteeringMaxCharacteristic.write16(invertByteOrderInt16(childSteeringMax));

  childThrottleMinCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  childThrottleMinCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  childThrottleMinCharacteristic.setWriteCallback(write_callback);
  childThrottleMinCharacteristic.setFixedLen(2);
  childThrottleMinCharacteristic.begin();
  childThrottleMinCharacteristic.write16(invertByteOrderInt16(childThrottleMin));

  childThrottleCenterCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  childThrottleCenterCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  childThrottleCenterCharacteristic.setWriteCallback(write_callback);
  childThrottleCenterCharacteristic.setFixedLen(2);
  childThrottleCenterCharacteristic.begin();
  childThrottleCenterCharacteristic.write16(invertByteOrderInt16(childThrottleCenter));

  childThrottleMaxCharacteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE);
  childThrottleMaxCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
  childThrottleMaxCharacteristic.setWriteCallback(write_callback);
  childThrottleMaxCharacteristic.setFixedLen(2);
  childThrottleMaxCharacteristic.begin();
  childThrottleMaxCharacteristic.write16(invertByteOrderInt16(childThrottleMax));
*/
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

void write_callback(uint16_t conn_hdl, BLECharacteristic* chr, uint8_t* data, uint16_t len)
{

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
/*
  if (characteristicId == 1) {
    Serial.print("Saving steeringMin value: ");
    Serial.println(valueInt16);
    steeringMin = valueInt16;
  } else if (characteristicId == 2) {
    Serial.print("Saving steeringCenter value: ");
    Serial.println(valueInt16);
    steeringCenter = valueInt16;
  } else if (characteristicId == 3) {
    Serial.print("Saving steeringMax value: ");
    Serial.println(valueInt16);
    steeringMax = valueInt16;
  } else if (characteristicId == 4) {
    rcEnable = valueBoolean;
    Serial.print("Saving rcEnable value: ");
    Serial.println(valueBoolean);
  } else {
    Serial.println("Write failed. Characteristic not found!");
  }
*/
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

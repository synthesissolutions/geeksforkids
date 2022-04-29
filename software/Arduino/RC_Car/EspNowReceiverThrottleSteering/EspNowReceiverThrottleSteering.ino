#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h> 

#define THROTTLE_OUT_PIN  15
#define STEERING_OUT_PIN  14

#define STEERING_CENTER_DEAD_ZONE_DEGREES 2
#define STEERING_CENTER 90
#define STEERING_MIN  50
#define STEERING_MAX  130

#define THROTTLE_STOPPED_DEAD_ZONE_MILLIS 25
#define THROTTLE_STOPPED  1500
#define THROTTLE_MIN      1400
#define THROTTLE_MAX      1600

#define MAX_MESSAGE_DELAY_MILLIS  75

Servo steeringServo;  // create servo object to control a servo 
Servo throttleServo;

long lastMessageTimeMillis = 0;

int steeringPosition = STEERING_CENTER;    // "normal" servo controls with 90 in center
int throttleMicroseconds = THROTTLE_STOPPED;

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  int throttleScaled; // -100 = full reverse, 0 = stopped, 100 = full forward
  int steeringScaled; // -100 = full left, 0 = center, 100 = full right
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));

  throttleMicroseconds = map(myData.throttleScaled, -100, 100, THROTTLE_MIN, THROTTLE_MAX);
  steeringPosition = map(myData.steeringScaled, -100, 100, STEERING_MIN, STEERING_MAX);
  lastMessageTimeMillis = millis();
  
  /*
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Throttle: ");
  Serial.println(myData.throttleScaled);
  Serial.print("Steering: ");
  Serial.println(myData.steeringScaled);
  
  Serial.println();
  */
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  myData.throttleScaled = 0;
  myData.steeringScaled = 0;

  steeringServo.attach(STEERING_OUT_PIN);  // attaches the servo on pin 9 to the servo object 
  steeringServo.write(steeringPosition);
  throttleServo.attach(THROTTLE_OUT_PIN);  // attaches the servo on pin 9 to the servo object 
  throttleServo.writeMicroseconds(throttleMicroseconds);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  if (millis() - lastMessageTimeMillis > MAX_MESSAGE_DELAY_MILLIS) {
    steeringServo.write(STEERING_CENTER);
    throttleServo.writeMicroseconds(THROTTLE_STOPPED);
  } else {
    if (abs(steeringPosition - STEERING_CENTER) > STEERING_CENTER_DEAD_ZONE_DEGREES) {
      steeringServo.write(steeringPosition);
    } else {
      steeringServo.write(STEERING_CENTER);
    }
  
    if (abs(throttleMicroseconds - THROTTLE_STOPPED) > THROTTLE_STOPPED_DEAD_ZONE_MILLIS) {
      throttleServo.writeMicroseconds(throttleMicroseconds);
    } else {
      throttleServo.writeMicroseconds(THROTTLE_STOPPED);
    }  
  }

  /*
  Serial.print("Throttle: ");
  Serial.println(throttleMicroseconds);
  Serial.print("Steering: ");
  Serial.println(steeringPosition);
  Serial.println("");
  */
  
  delay(25);
}

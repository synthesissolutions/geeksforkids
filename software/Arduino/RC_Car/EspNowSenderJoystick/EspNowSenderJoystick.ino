#include <esp_now.h>
#include <WiFi.h>

#define THROTTLE_PIN  32
#define STEERING_PIN  33

#define THROTTLE_CENTER   1730
#define STEERING_CENTER   1745

// RECEIVER MAC Address 3C:71:BF:64:2F:7D
//uint8_t broadcastAddress[] = {0x3C, 0x71, 0xBF, 0x64, 0x2F, 0x7D};
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  int throttleScaled; // -100 = full reverse, 0 = stopped, 100 = full forward
  int steeringScaled; // -100 = full left, 0 = center, 100 = full right
} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);

  pinMode(THROTTLE_PIN, INPUT);
  pinMode(STEERING_PIN, INPUT);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {
  // Set values to send
  int rawThrottle = analogRead(THROTTLE_PIN);
  int rawSteering = analogRead(STEERING_PIN);

  if (rawThrottle >= THROTTLE_CENTER) {
    myData.throttleScaled = -map(rawThrottle, THROTTLE_CENTER, 4095, 0, 100);
  } else {
    myData.throttleScaled = -map(rawThrottle, 0, THROTTLE_CENTER, -100, 0);    
  }
  
  if (rawSteering >= STEERING_CENTER) {
    myData.steeringScaled = map(rawSteering, STEERING_CENTER, 4095, 0, 100);
  } else {
    myData.steeringScaled = map(rawSteering, 0, STEERING_CENTER, -100, 0);    
  }

  Serial.print("Throttle: ");
  Serial.print(rawThrottle);
  Serial.print(", ");
  Serial.print(myData.throttleScaled);
  Serial.print("  Steering: ");
  Serial.print(rawSteering);
  Serial.print(", ");
  Serial.println(myData.steeringScaled);
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(50);
}

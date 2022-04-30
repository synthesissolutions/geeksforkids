#include <esp_now.h>
#include <WiFi.h>

#define THROTTLE_PIN    32
#define STEERING_PIN    33
#define PWM_SWITCH_PIN  5

#define ANALOG_THROTTLE_CENTER   1730
#define ANALOG_STEERING_CENTER   1745

#define PWM_THROTTLE_CENTER   500
#define PWM_THROTTLE_LEFT     200
#define PWM_THROTTLE_RIGHT    800

#define PWM_STEERING_CENTER   500
#define PWM_STEERING_LEFT     200
#define PWM_STEERING_RIGHT    800

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

bool usePwmSignals;

// variables to track the PWM signals
unsigned long steeringPulseStart; // the timestamp in ms for the current PWM steering pulse
unsigned long steeringPwm = 0;    // the length of the last full PWM steering pulse in microseconds
boolean steeringSignalHigh = false; // flag indicating that the start of a PWM signal (rising edge) has occured
unsigned long throttlePulseStart; // the timestamp in ms for the current PWM throttle pulse
unsigned long throttlePwm = 0;    // the length of the last full PWM throttle pulse in microseconds
boolean throttleSignalHigh = false; // flag indicating that the start of a PWM signal (rising edge) has occured

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
  pinMode(PWM_SWITCH_PIN, INPUT_PULLUP);
  
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

  usePwmSignals = !digitalRead(PWM_SWITCH_PIN); // logic is reversed since internal pullup resistor is used

  if (usePwmSignals) {
    attachInterrupt(digitalPinToInterrupt(STEERING_PIN), &steeringIRQHandler, CHANGE); 
    attachInterrupt(digitalPinToInterrupt(THROTTLE_PIN), &throttleIRQHandler, CHANGE);  
  }
}
 
void loop() {
  if (usePwmSignals) {
    if (throttlePwm >= PWM_THROTTLE_CENTER) {
      myData.throttleScaled = -map(throttlePwm, PWM_THROTTLE_CENTER, PWM_THROTTLE_RIGHT, 0, 100);
    } else {
      myData.throttleScaled = -map(throttlePwm, PWM_THROTTLE_LEFT, PWM_THROTTLE_CENTER, -100, 0);    
    }
    
    if (steeringPwm >= PWM_STEERING_CENTER) {
      myData.steeringScaled = map(steeringPwm, PWM_STEERING_CENTER, PWM_STEERING_RIGHT, 0, 100);
    } else {
      myData.steeringScaled = map(steeringPwm, PWM_STEERING_LEFT, PWM_STEERING_CENTER, -100, 0);    
    }
  } else {
    // Set values to send
    int rawThrottle = analogRead(THROTTLE_PIN);
    int rawSteering = analogRead(STEERING_PIN);
  
    if (rawThrottle >= ANALOG_THROTTLE_CENTER) {
      myData.throttleScaled = -map(rawThrottle, ANALOG_THROTTLE_CENTER, 4095, 0, 100);
    } else {
      myData.throttleScaled = -map(rawThrottle, 0, ANALOG_THROTTLE_CENTER, -100, 0);    
    }
    
    if (rawSteering >= ANALOG_STEERING_CENTER) {
      myData.steeringScaled = map(rawSteering, ANALOG_STEERING_CENTER, 4095, 0, 100);
    } else {
      myData.steeringScaled = map(rawSteering, 0, ANALOG_STEERING_CENTER, -100, 0);    
    }
  
    Serial.print("Switch: ");
    Serial.print(digitalRead(PWM_SWITCH_PIN));
    Serial.print("   Throttle: ");
    Serial.print(rawThrottle);
    Serial.print(", ");
    Serial.print(myData.throttleScaled);
    Serial.print("  Steering: ");
    Serial.print(rawSteering);
    Serial.print(", ");
    Serial.println(myData.steeringScaled);
  }

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

void steeringIRQHandler() {
  if(digitalRead(STEERING_PIN) == 1){
    if (!steeringSignalHigh) {
      // rising edge of the PWM signal
      // record when the pulse started
      steeringPulseStart = micros();
      steeringSignalHigh = true;
    }
    
  } else if (steeringSignalHigh) {
    // falling edge of the PWM signal
    // record the duty cycle in microseconds
    steeringPwm = micros() - steeringPulseStart;

    // reset for the next pulse
    steeringSignalHigh = false;
  }
}
    
void throttleIRQHandler() {
  if(digitalRead(THROTTLE_PIN) == 1){
    if (!throttleSignalHigh) {
      // rising edge of the PWM signal
      // record when the pulse started
      throttlePulseStart = micros();
      throttleSignalHigh = true;
    }
  } else if (throttleSignalHigh) {
    // falling edge of the PWM signal
    // record the duty cycle in microseconds
    throttlePwm = micros() - throttlePulseStart;

    // reset for the next pulse
    throttleSignalHigh = false;
  }
}

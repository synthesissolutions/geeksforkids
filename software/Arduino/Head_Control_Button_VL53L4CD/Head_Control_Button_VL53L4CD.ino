#include <Arduino.h>
#include <Wire.h>
#include <vl53l4cd_class.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>
#include <Adafruit_NeoPixel.h>

#define PIN         0
#define NUMPIXELS   1
#define BUTTON_PIN  9

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Components.
VL53L4CD sensor_vl53l4cd_sat(&Wire, A1);


void setup()
{
  // Initialize serial for output.
  Serial.begin(115200);
  Serial.println("Starting...");

  pinMode(BUTTON_PIN, OUTPUT);
  
  pixels.begin();
  pixels.clear(); // Set all pixel colors to 'off'
  
  // Initialize I2C bus.
  Wire.begin();

  // Configure VL53L4CD satellite component.
  sensor_vl53l4cd_sat.begin();

  // Switch off VL53L4CD satellite component.
  sensor_vl53l4cd_sat.VL53L4CD_Off();

  //Initialize VL53L4CD satellite component.
  sensor_vl53l4cd_sat.InitSensor();

  // Program the highest possible TimingBudget, without enabling the
  // low power mode. This should give the best accuracy
  //sensor_vl53l4cd_sat.VL53L4CD_SetRangeTiming(200, 0);
  sensor_vl53l4cd_sat.VL53L4CD_SetRangeTiming(200, 0);

  // Start Measurements
  sensor_vl53l4cd_sat.VL53L4CD_StartRanging();
}

void loop()
{
  uint8_t NewDataReady = 0;
  VL53L4CD_Result_t results;
  uint8_t status;
  char report[64];

  do {
    status = sensor_vl53l4cd_sat.VL53L4CD_CheckForDataReady(&NewDataReady);
  } while (!NewDataReady);

  if ((!status) && (NewDataReady != 0)) {
    // (Mandatory) Clear HW interrupt to restart measurements
    sensor_vl53l4cd_sat.VL53L4CD_ClearInterrupt();

    // Read measured distance. RangeStatus = 0 means valid data
    sensor_vl53l4cd_sat.VL53L4CD_GetResult(&results);
    snprintf(report, sizeof(report), "Status = %3u, Distance = %5u mm, Signal = %6u kcps/spad\r\n",
             results.range_status,
             results.distance_mm,
             results.signal_per_spad_kcps);
    Serial.print(report);

    if (results.range_status == 0) {
      if (results.distance_mm >= 175 || results.distance_mm <= 10) {
        digitalWrite(BUTTON_PIN, HIGH);
        pixels.setPixelColor(0, pixels.Color(150, 0, 0));
      } else {
        digitalWrite(BUTTON_PIN, LOW);
        pixels.setPixelColor(0, pixels.Color(0, 150, 0));
      }    
    } else {
      digitalWrite(BUTTON_PIN, HIGH);
      pixels.setPixelColor(0, pixels.Color(150, 0, 0));
    }
  } else {
    digitalWrite(BUTTON_PIN, HIGH);
    pixels.setPixelColor(0, pixels.Color(150, 0, 0));
  }

  pixels.show();
}

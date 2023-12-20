// AqMonitor - Air quality monitor using a BME680 sensor, a 2.13" epaper display and an ESP32
// Job Meijer - December 2023

// Includes 
#include <Arduino.h>
#include "functions/iaqSensor.hpp"
#include "functions/epdisplay.hpp"

// Definitions
#define SERIAL_BAUDRATE 115200

// Variables
uint16_t dispUpdateInterval = 10;                     // Update display every 10 sensor measurement iterations
uint16_t dispUpdateCounter = dispUpdateInterval;      // counter for display update interval

// Objects
IaqSensor iaqSens;
EpDisplay epDisp;

// Init function
void setup() {  
  Serial.begin(SERIAL_BAUDRATE);
  
  !iaqSens.init();                  // Init IAQ sensor                  
  epDisp.init();                    // Init Epaper Display
}

void loop() {
  if (iaqSens.checkSensor()) {
    Serial.println(iaqSens.outputString);
    
    if (dispUpdateCounter == dispUpdateInterval) {
      epDisp.updateData(iaqSens.bsec.temperature, iaqSens.bsec.humidity, iaqSens.bsec.pressure, iaqSens.bsec.iaq, iaqSens.bsec.co2Equivalent, iaqSens.bsec.iaqAccuracy);
      //epDisp.setTemperature(iaqSens.bsec.temperature);
      //epDisp.setHumidity(iaqSens.bsec.humidity);
      dispUpdateCounter = 0;
      Serial.println("Updating display.");
    } else {
      dispUpdateCounter++;
      Serial.println("Updating display in " + String(dispUpdateInterval - dispUpdateCounter + 1) + " iterations.");
    }   
  }  
}




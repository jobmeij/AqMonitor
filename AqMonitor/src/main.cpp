// AqMonitor - Air quality monitor using a BME680 sensor, a 2.13" epaper display and an ESP32
// Job Meijer - December 2023

// Includes 
#include <Arduino.h>
#include "helpers/i2cScanner.hpp"
#include "functions/iaqSensor.hpp"
#include "functions/epdisplay.hpp"

// Definitions
#define SERIAL_BAUDRATE 115200

// 
IaqSensor iaqSens;
EpDisplay epDisp;

// Init function
void setup() {  
  Serial.begin(SERIAL_BAUDRATE);
  iaqSens.init();                   // Init BME680
  epDisp.init();                    // Init Epaper Display
}

void loop() {
  if (iaqSens.checkSensor()) {
    Serial.println(iaqSens.output);
  }

  //   // Update epaper once a minute 
  //   if (counter == 60) {
  //     // display.setPartialWindow(box_x, box_y, box_w, box_h);
  //     display.setPartialWindow(box_x, box_y, box_w, box_h);
  //     for (uint16_t i = 1; i <= 10; i++)
  //     {
  //       display.firstPage();
  //       do
  //       {
  //         display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
  //         uint16_t cursor_y = box_y + box_h - 6;
  //         display.setCursor(box_x, cursor_y);
  //         //display.print(value * i, 2);
  //         display.print("IAQ: " + String(iaqSensor.iaq, 0));
  //       }
  //       while (display.nextPage());
  //       delay(500);
  //     }


  //     if (false) {
  //       display.firstPage();
  //       do {
  //         display.print("IAQ: " + String(iaqSensor.iaq, 0));
  //       } while (display.nextPage());
  //     }      

  //     counter = 0; // reset
  //   } else{
  //     counter = counter + 1;
  //   }    
  // } else {
  //   checkIaqSensorStatus();
  // }
}




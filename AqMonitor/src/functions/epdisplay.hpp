#ifndef EPDISPLAY_H
#define EPDISPLAY_H

// Libraries
#include <Arduino.h>
#include <SPI.h>
#include <GxEPD2_BW.h>
#include <Adafruit_GFX.h>
#include <Adafruit_BusIO_Register.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// Definitions
#define ENABLE_GxEPD2_GFX 0     // base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
#define PIN_EPD_SCA 23
#define PIN_EPD_SCL 18
#define PIN_EPD_CS 5
#define PIN_EPD_DC 4
#define PIN_EPD_RES 2
#define PIN_EPD_BUSY 15

// NOTE display has 250x122 pixels (width x height)

// Class
class EpDisplay
{
    public:
        EpDisplay();
        bool init();
        
        void updateData(float temp, float humid, float press, float iaq, float co2, uint8_t iaqStatus);

        void printTextDoubleRow(String topText, String botText);
        void clearFullDisplay();

    private:
        uint16_t box_x = 0; //10;
        uint16_t box_y = 0; //15;
        uint16_t box_w = 250;
        uint16_t box_h = 20;        

        void setTemperature(float temp);
        void setHumidity(float hum);
        void setPressure(float press);
        void setIaq(float iaq);
        void setCo2(float co2);
        void setIaqStatus(uint8_t status);

        //void initPartialBoxes();
        void helloWorld(); 
        void helloFullScreenPartialMode();
        void showPartialUpdate();

        GxEPD2_BW<GxEPD2_213_BN, GxEPD2_213_BN::HEIGHT> display;    // DEPG0213BN 122x250, SSD1680, 2.13" EPD Module

};

#endif
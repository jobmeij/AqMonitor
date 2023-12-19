#ifndef EPDISPLAY_H
#define EPDISPLAY_H

// Libraries
#include <Arduino.h>
#include <GxEPD2_BW.h>
#include <Adafruit_GFX.h>
#include <Adafruit_BusIO_Register.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// Definitions
#define ENABLE_GxEPD2_GFX 1     // base class GxEPD2_GFX can be used to pass references or pointers to the display instance as parameter, uses ~1.2k more code
#define PIN_EPD_SCA 23
#define PIN_EPD_SCL 18
#define PIN_EPD_CS 16
#define PIN_EPD_DC 4
#define PIN_EPD_RES 2
#define PIN_EPD_BUSY 15


const char HelloWorld[] = "Hello World!";
const char HelloWeACtStudio[] = "Goodbye world.";


class EpDisplay
{
    public:
        EpDisplay();
        bool init();

    private: 
        void helloWorld(); 
        void helloFullScreenPartialMode();
        void showPartialUpdate();

        uint16_t box_x = 10;
        uint16_t box_y = 15;
        uint16_t box_w = 100;
        uint16_t box_h = 20;        

        GxEPD2_BW<GxEPD2_213_BN, GxEPD2_213_BN::HEIGHT> display;    // DEPG0213BN 122x250, SSD1680, 2.13" EPD Module

};

#endif
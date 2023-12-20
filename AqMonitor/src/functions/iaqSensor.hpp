#ifndef IAQSENSOR_H
#define IAQSENSOR_H

// Libraries
#include <Arduino.h>
#include <bsec.h>
#include <Wire.h>
#include "helpers/i2cScanner.hpp"

// Definitions
#define PIN_LED_BUILTIN 2
#define PIN_I2C_SDA 22
#define PIN_I2C_SCL 21

class IaqSensor
{
    public:
        IaqSensor();
        bool init();
        bool checkSensor();
        
        Bsec bsec;
        String outputString;

    private:
        I2CScanner i2cScan;

        void checkIaqSensorStatus();
        void errLeds();

};

#endif
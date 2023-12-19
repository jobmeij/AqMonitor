#ifndef IAQSENSOR_H
#define IAQSENSOR_H

// Libraries
#include <Arduino.h>
#include <bsec.h>
#include <Wire.h>

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

        String output;

    private:
        void checkIaqSensorStatus();
        void errLeds();

        Bsec iaqSensor;

};

#endif
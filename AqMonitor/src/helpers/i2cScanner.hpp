// I2C scanner class
// Job Meijer - December 2023

#ifndef I2C_SCANNER_H
#define I2C_SCANNER_H

#include <Arduino.h>
#include <Wire.h>

class I2CScanner {
public:
    I2CScanner(int pinSda, int pinScl);
    void scanI2c();

private:
    int SDA;
    int SCL;

};

#endif // I2C_SCANNER_H

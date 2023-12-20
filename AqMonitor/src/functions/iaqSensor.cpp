#include "iaqSensor.hpp"

IaqSensor::IaqSensor() : i2cScan(PIN_I2C_SDA, PIN_I2C_SCL) {
      
}

bool IaqSensor::init() 
{
    Serial.println("Initializing IAQ sensor...");
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
    i2cScan.scanI2c();
    bsec.begin(BME68X_I2C_ADDR_HIGH, Wire);         // HIGH = 0x77, LOW = 0x76 --> standard BME680 is HIGH address
    pinMode(PIN_LED_BUILTIN, OUTPUT);
    checkIaqSensorStatus();

    bsec_virtual_sensor_t sensorList[13] = {
        BSEC_OUTPUT_IAQ,
        BSEC_OUTPUT_STATIC_IAQ,
        BSEC_OUTPUT_CO2_EQUIVALENT,
        BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
        BSEC_OUTPUT_RAW_TEMPERATURE,
        BSEC_OUTPUT_RAW_PRESSURE,
        BSEC_OUTPUT_RAW_HUMIDITY,
        BSEC_OUTPUT_RAW_GAS,
        BSEC_OUTPUT_STABILIZATION_STATUS,
        BSEC_OUTPUT_RUN_IN_STATUS,
        BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
        BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
        BSEC_OUTPUT_GAS_PERCENTAGE
    };

    bsec.updateSubscription(sensorList, 13, BSEC_SAMPLE_RATE_LP);
    checkIaqSensorStatus();

    Serial.println("IAQ sensor initialized.");
    return true;
}

void IaqSensor::checkIaqSensorStatus()
{
  if (bsec.bsecStatus != BSEC_OK) {
    if (bsec.bsecStatus < BSEC_OK) {
      outputString = "BSEC error code : " + String(bsec.bsecStatus);
      Serial.println(outputString);
      for (;;)
        errLeds(); /* Halt in case of failure */
    } else {
      outputString = "BSEC warning code : " + String(bsec.bsecStatus);
      Serial.println(outputString);
    }
  }

  if (bsec.bme68xStatus != BME68X_OK) {
    if (bsec.bme68xStatus < BME68X_OK) {
      outputString = "BME680 error code : " + String(bsec.bme68xStatus);
      Serial.println(outputString);
      for (;;)
        errLeds(); /* Halt in case of failure */
    } else {
      outputString = "BME680 warning code : " + String(bsec.bme68xStatus);
      Serial.println(outputString);
    }
  }
}

void IaqSensor::errLeds()
{
  pinMode(PIN_LED_BUILTIN, OUTPUT);
  digitalWrite(PIN_LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(PIN_LED_BUILTIN, LOW);
  delay(100);
}

bool IaqSensor::checkSensor() {
    unsigned long time_trigger = millis();
    if (bsec.run()) { // If new data is available
        digitalWrite(PIN_LED_BUILTIN, HIGH);
        outputString = String(time_trigger);
        outputString += ", " + String(bsec.iaq);
        outputString += ", " + String(bsec.iaqAccuracy);
        outputString += ", " + String(bsec.staticIaq);
        outputString += ", " + String(bsec.co2Equivalent);
        outputString += ", " + String(bsec.breathVocEquivalent);
        outputString += ", " + String(bsec.rawTemperature);
        outputString += ", " + String(bsec.pressure);
        outputString += ", " + String(bsec.rawHumidity);
        outputString += ", " + String(bsec.gasResistance);
        outputString += ", " + String(bsec.stabStatus);
        outputString += ", " + String(bsec.runInStatus);
        outputString += ", " + String(bsec.temperature);
        outputString += ", " + String(bsec.humidity);
        outputString += ", " + String(bsec.gasPercentage);
        digitalWrite(PIN_LED_BUILTIN, LOW);
        return true;
    } else {
        return false;
    }
}


#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

// Question 2.1.1 : temperature (C et F) et humidite du BME680 en I2C (SDA 21, SCL 22)
#define PREFIX "[Binome 27 - VAZQUEZ & FEUYANG] "

Adafruit_BME680 bme;   // sans argument = mode I2C

void setup() {
  Serial.begin(115200);
  delay(1000);
  Wire.begin(21, 22);
  if (!bme.begin(0x77) && !bme.begin(0x76)) {
    Serial.println(PREFIX "BME680 introuvable, verifie le cablage !");
    while (1) { delay(100); }
  }
  Serial.println(PREFIX "BME680 detecte");

  bme.setTemperatureOversampling(BME680_OS_8X); // 8 mesures moyennees : plus precis, plus lent
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);   // lisse les variations brusques
  bme.setGasHeater(320, 150);                   // chauffe le capteur de gaz (gros consommateur)
}

void loop() {
  if (!bme.performReading()) {
    Serial.println(PREFIX "Erreur de lecture");
    return;
  }
  float tempC = bme.temperature;
  float tempF = tempC * 9.0 / 5.0 + 32.0;
  float hum   = bme.humidity;

  Serial.print(PREFIX "Temperature : ");
  Serial.print(tempC); Serial.print(" C / ");
  Serial.print(tempF); Serial.print(" F | Humidite : ");
  Serial.print(hum);   Serial.println(" %");
  delay(2000);
}

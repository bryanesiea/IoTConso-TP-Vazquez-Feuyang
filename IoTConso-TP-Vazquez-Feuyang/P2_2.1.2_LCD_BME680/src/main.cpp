#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"

// Question 2.1.2 (2) : temperature et humidite du BME680 sur l'ecran (meme bus I2C)
#define PREFIX "[Binome 27 - VAZQUEZ & FEUYANG] "

LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_BME680 bme;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();

  if (!bme.begin(0x77) && !bme.begin(0x76)) {
    Serial.println(PREFIX "BME680 introuvable !");
    lcd.print("Erreur BME680");
    while (1) { delay(100); }
  }
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(0, 0);   // capteur de gaz desactive : inutile ici, et c'est lui qui chauffe
}

void loop() {
  if (!bme.performReading()) {
    Serial.println(PREFIX "Erreur de lecture");
    return;
  }
  float t = bme.temperature;
  float h = bme.humidity;

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t, 1);
  lcd.print((char)223);      // symbole degre sur ce type d'ecran
  lcd.print("C   ");

  lcd.setCursor(0, 1);
  lcd.print("Hum : ");
  lcd.print(h, 1);
  lcd.print(" %   ");

  Serial.print(PREFIX "T = "); Serial.print(t);
  Serial.print(" C | H = "); Serial.print(h); Serial.println(" %");
  delay(2000);
}

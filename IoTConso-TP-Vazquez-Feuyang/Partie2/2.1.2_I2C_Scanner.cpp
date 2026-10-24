#include <Arduino.h>
#include <Wire.h>

// Scan du bus I2C : trouve l'adresse de chaque peripherique (ecran 0x27, BME680 0x77)
#define PREFIX "[Binome 27 - VAZQUEZ & FEUYANG] "

void setup() {
  Serial.begin(115200);
  delay(1000);
  Wire.begin(21, 22);
}

void loop() {
  Serial.println(PREFIX "Scan du bus I2C...");
  for (byte adresse = 1; adresse < 127; adresse++) {
    Wire.beginTransmission(adresse);
    if (Wire.endTransmission() == 0) {   // 0 = un appareil a repondu
      Serial.print(PREFIX "Appareil trouve a l'adresse 0x");
      Serial.println(adresse, HEX);
    }
  }
  delay(5000);
}

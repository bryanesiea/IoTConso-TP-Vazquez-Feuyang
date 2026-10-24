#include <Arduino.h>

// Question 3.2.4 : la LED suit le bouton, par scrutation (polling), sans delai
// Bouton entre 3V3 et GPIO27, resistance 10 kOhm de GPIO27 vers GND (pull-down)
#define LED_PIN 2
#define BTN_PIN 27

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);
  Serial.println("[Binome 27 - VAZQUEZ & FEUYANG] Bouton -> LED (polling)");
}

void loop() {
  digitalWrite(LED_PIN, digitalRead(BTN_PIN));
}

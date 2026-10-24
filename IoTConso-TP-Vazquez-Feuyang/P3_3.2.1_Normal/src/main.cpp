#include <Arduino.h>

// Question 3.2.1 : clignotement en mode normal (T_on = 50 x 27 = 1350 ms, periode 2000 ms)
#define PREFIX "[Binome 27 - VAZQUEZ & FEUYANG] "
#define LED_PIN 2      // LED integree a la carte
#define T_ON  1350     // ms
#define T_OFF 650      // ms

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  Serial.println(PREFIX "Mode normal");
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println(PREFIX "LED allumee");
  delay(T_ON);
  digitalWrite(LED_PIN, LOW);
  Serial.println(PREFIX "LED eteinte");
  delay(T_OFF);
}

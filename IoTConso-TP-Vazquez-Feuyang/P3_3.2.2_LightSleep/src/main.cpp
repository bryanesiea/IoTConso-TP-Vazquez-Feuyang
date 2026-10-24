#include <Arduino.h>
#include "esp_sleep.h"

// Question 3.2.2 : meme clignotement, light sleep pendant la phase eteinte (exemple du cours, diapo 43)
#define PREFIX "[Binome 27 - VAZQUEZ & FEUYANG] "
#define uS_TO_mS_FACTOR 1000ULL
#define LED_PIN 2
#define T_ON  1350
#define T_OFF 650

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  Serial.println(PREFIX "Mode light sleep");
  esp_sleep_enable_timer_wakeup(T_OFF * uS_TO_mS_FACTOR);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(T_ON);                 // carte active, LED allumee
  digitalWrite(LED_PIN, LOW);
  Serial.println(PREFIX "Dodo");
  Serial.flush();
  esp_light_sleep_start();     // carte endormie, LED eteinte
}

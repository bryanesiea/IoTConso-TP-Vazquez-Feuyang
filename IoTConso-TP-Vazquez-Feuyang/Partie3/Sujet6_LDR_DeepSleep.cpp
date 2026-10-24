#include <Arduino.h>
#include "esp_sleep.h"

// Sujet 6 : l'objet se reveille toutes les T_sleep = 7,75 s, lit la LDR et se rendort aussitot.
// Pas de Serial ni de LED : on mesure uniquement le cout d'un reveil + lecture LDR.
#define LDR_PIN 36                 // ADC1_CH0 : utilisable meme quand le Wi-Fi est actif
#define T_SLEEP_US 7750000ULL

RTC_DATA_ATTR int derniereValeurLDR = 0;   // en memoire RTC : survit au deep sleep

void setup() {
  derniereValeurLDR = analogRead(LDR_PIN);
  esp_sleep_enable_timer_wakeup(T_SLEEP_US);
  esp_deep_sleep_start();
}

void loop() {}

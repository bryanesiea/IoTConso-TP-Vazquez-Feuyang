#include <Arduino.h>
#include "esp_sleep.h"
#include "driver/gpio.h"

// Question 3.2.4 : meme montage, la carte dort en light sleep et se reveille quand le bouton change d'etat
#define LED_PIN 2
#define BTN_PIN 27

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);
  esp_sleep_enable_gpio_wakeup();
  Serial.println("[Binome 27 - VAZQUEZ & FEUYANG] Bouton -> LED (light sleep)");
  Serial.flush();
}

void loop() {
  int etat = digitalRead(BTN_PIN);
  digitalWrite(LED_PIN, etat);
  gpio_wakeup_enable((gpio_num_t)BTN_PIN, etat ? GPIO_INTR_LOW_LEVEL : GPIO_INTR_HIGH_LEVEL);
  esp_light_sleep_start();
}

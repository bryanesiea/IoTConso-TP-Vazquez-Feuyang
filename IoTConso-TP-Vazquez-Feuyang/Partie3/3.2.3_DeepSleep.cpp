#include <Arduino.h>
#include "esp_sleep.h"

// Question 3.2.3 : LED allumee T_on, puis deep sleep T_sleep = 1 + 0,25 x 27 = 7,75 s (exemple du cours, diapo 44)
#define PREFIX "[Binome 27 - VAZQUEZ & FEUYANG] "
#define LED_PIN 2
#define T_ON 1350
#define T_SLEEP_US 7750000ULL

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  Serial.println(PREFIX "Reveil");

  digitalWrite(LED_PIN, HIGH);
  delay(T_ON);
  digitalWrite(LED_PIN, LOW);

  Serial.println(PREFIX "Deep sleep pour 7,75 s");
  Serial.flush();
  esp_sleep_enable_timer_wakeup(T_SLEEP_US);
  esp_deep_sleep_start();    // au reveil, la carte repart du debut de setup()
}

void loop() {}

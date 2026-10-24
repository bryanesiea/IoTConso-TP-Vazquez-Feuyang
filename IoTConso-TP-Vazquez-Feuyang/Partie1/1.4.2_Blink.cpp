#include <Arduino.h>

// Question 1.4.2 (sortie) : LED allumee T_on = 50 x 27 = 1350 ms, eteinte le reste d'une periode de 2000 ms
// (code reecrit apres la seance, voir README)
#define PREFIX "[Binome 27 - VAZQUEZ & FEUYANG] "
#define LED_PIN 2
#define T_ON  1350
#define T_OFF 650

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println(PREFIX "LED allumee");
  delay(T_ON);
  digitalWrite(LED_PIN, LOW);
  Serial.println(PREFIX "LED eteinte");
  delay(T_OFF);
}

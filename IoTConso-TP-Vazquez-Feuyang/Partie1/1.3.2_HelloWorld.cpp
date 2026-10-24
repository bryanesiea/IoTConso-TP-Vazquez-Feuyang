#include <Arduino.h>

// Question 1.3.2 : afficher "Hello Arduino World!" toutes les 2 s, avec le prefixe du binome
// (code reecrit apres la seance, voir README)
#define PREFIX "[Binome 27 - VAZQUEZ & FEUYANG] "

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println(PREFIX "Hello Arduino World!");
  delay(2000);
}

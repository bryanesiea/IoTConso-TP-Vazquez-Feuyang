#include <Arduino.h>

// Question 1.5.2 : lire la LDR (pont diviseur avec une resistance de 10 kOhm) sur l'ADC,
// valeur entre 0 et 4095 affichee toutes les secondes.
// (code reecrit apres la seance, voir README)
#define PREFIX "[Binome 27 - VAZQUEZ & FEUYANG] "
#define LDR_PIN 36            // ADC1_CH0 (A0) : broche utilisee en partie 3

void setup() {
  Serial.begin(115200);
}

void loop() {
  int valeur = analogRead(LDR_PIN);
  Serial.print(PREFIX "LDR = ");
  Serial.println(valeur);
  delay(1000);
}

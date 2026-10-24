#include <Arduino.h>

// Question 1.4.2 (entree) : compter les appuis-relachements sans interruption (polling),
// et n'afficher le compteur que lorsqu'il change. Bouton entre GPIO4 et GND, pull-up interne.
// (code reecrit apres la seance, voir README)
#define PREFIX "[Binome 27 - VAZQUEZ & FEUYANG] "
#define BTN_PIN 4

int compteur = 0;
int etatPrecedent = HIGH;     // pull-up : HIGH = relache, LOW = appuye

void setup() {
  Serial.begin(115200);
  pinMode(BTN_PIN, INPUT_PULLUP);
}

void loop() {
  int etat = digitalRead(BTN_PIN);
  if (etatPrecedent == LOW && etat == HIGH) {   // on vient de relacher : un appui complet
    compteur++;
    Serial.print(PREFIX "Nombre d'appuis : ");
    Serial.println(compteur);
  }
  etatPrecedent = etat;
  delay(20);                  // anti-rebond simple
}

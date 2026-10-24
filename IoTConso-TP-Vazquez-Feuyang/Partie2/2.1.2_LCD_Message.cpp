#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Question 2.1.2 (1) : "Great IoT Tutorial!" sur la ligne 1 (defilement, 19 caracteres > 16),
// "Launched for Xs" sur la ligne 2
#define PREFIX "[Binome 27 - VAZQUEZ & FEUYANG] "

LiquidCrystal_I2C lcd(0x27, 16, 2);

String bande = "Great IoT Tutorial!    ";
int pos = 0;
unsigned long dernierDefilement = 0;
unsigned long derniereSeconde = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();
  Serial.println(PREFIX "Ecran LCD initialise");
}

void loop() {
  unsigned long maintenant = millis();

  if (maintenant - dernierDefilement >= 400) {
    dernierDefilement = maintenant;
    String doublee = bande + bande;
    lcd.setCursor(0, 0);
    lcd.print(doublee.substring(pos, pos + 16));
    pos = (pos + 1) % bande.length();
  }

  if (maintenant - derniereSeconde >= 1000) {
    derniereSeconde = maintenant;
    unsigned long secondes = maintenant / 1000;
    lcd.setCursor(0, 1);
    lcd.print("Launched for ");
    lcd.print(secondes);
    lcd.print("s   ");
    Serial.print(PREFIX "Launched for ");
    Serial.print(secondes);
    Serial.println("s");
  }
}

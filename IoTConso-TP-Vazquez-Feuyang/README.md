# IoT et consommation énergétique — TP (binôme 27)

Enzo VAZQUEZ & Bryan FEUYANG — ESIEA, octobre 2026

Paramètres : N = 27, T_on = 1350 ms sur 2000 ms, T_sleep = 7,75 s.
Carte : NodeMCU-32S (ESP32), PlatformIO, framework Arduino (configuration dans `platformio.ini`).

Un fichier par question. Pour tester un code, le copier dans `src/main.cpp`.
Les identifiants Wi-Fi, clés d'API et clés Adafruit IO sont remplacés par `XXX`.

**Remarque.** En séance, nous travaillions dans un seul projet en remplaçant le code à chaque question.
Les fichiers des parties 2 et 3 reprennent les versions utilisées en séance.
Ceux de la partie 1 ont été réécrits après coup, d'après nos captures, car les originaux n'ont pas été conservés
(sur les captures de la partie 1, le préfixe était encore « Enzo & Feuyang »).

| Fichier | Question | Broches |
|---|---|---|
| `Partie1/1.3.2_HelloWorld.cpp` | 1.3.2 — « Hello Arduino World! » toutes les 2 s | — |
| `Partie1/1.4.2_Blink.cpp` | 1.4.2 — clignotement T_on = 1350 ms | GPIO2 |
| `Partie1/1.4.2_Bouton_Compteur.cpp` | 1.4.2 — compteur d'appuis sans interruption | GPIO4 |
| `Partie1/1.5.2_LDR.cpp` | 1.5.2 — lecture de la LDR sur l'ADC | GPIO36 |
| `Partie2/2.1.1_BME680.cpp` | 2.1.1 — température (°C, °F) et humidité | GPIO21, GPIO22 |
| `Partie2/2.1.2_I2C_Scanner.cpp` | 2.1.2 — adresses du bus I2C | GPIO21, GPIO22 |
| `Partie2/2.1.2_LCD_Message.cpp` | 2.1.2 (1) — message sur deux lignes | GPIO21, GPIO22 |
| `Partie2/2.1.2_LCD_BME680.cpp` | 2.1.2 (2) — température et humidité sur l'écran | GPIO21, GPIO22 |
| `Partie2/2.2.1_Weatherstack.cpp` | 2.2.1 — API Weatherstack, lecture du JSON | — |
| `Partie2/2.3_AdafruitIO.cpp` | 2.3 — publication MQTT sur Adafruit IO | GPIO21, GPIO22, GPIO2 |
| `Partie3/3.2.1_Normal.cpp` | 3.2.1 — clignotement en mode normal | GPIO2 |
| `Partie3/3.2.2_LightSleep.cpp` | 3.2.2 — clignotement en light sleep | GPIO2 |
| `Partie3/3.2.3_DeepSleep.cpp` | 3.2.3 — clignotement en deep sleep (7,75 s) | GPIO2 |
| `Partie3/3.2.4_Bouton_Polling.cpp` | 3.2.4 — temps de réponse bouton → LED (polling) | GPIO27, GPIO2 |
| `Partie3/3.2.4_Bouton_LightSleep.cpp` | 3.2.4 — temps de réponse bouton → LED (light sleep) | GPIO27, GPIO2 |
| `Partie3/Sujet6_LDR_DeepSleep.cpp` | Sujet 6 — réveil, lecture LDR, deep sleep | GPIO36 |

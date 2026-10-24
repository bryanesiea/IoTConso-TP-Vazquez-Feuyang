#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Question 2.2.1 : ville, heure, temperature et vent via l'API Weatherstack
#define PREFIX "[Binome 27 - VAZQUEZ & FEUYANG] "

const char* WIFI_SSID = "XXX";
const char* WIFI_PASS = "XXX";
const char* API_KEY   = "XXX";      // cle Weatherstack retiree du depot
const char* VILLE     = "Paris";

unsigned long dernierAppel = 0;
const unsigned long INTERVALLE = 10UL * 60UL * 1000UL;  // 10 min : quota gratuit limite

void appelerMeteo() {
  // http et non https : le plan gratuit ne gere pas le https
  String url = String("http://api.weatherstack.com/current?access_key=") + API_KEY + "&query=" + VILLE;

  HTTPClient http;
  http.begin(url);
  int code = http.GET();
  if (code != 200) {
    Serial.print(PREFIX "Erreur HTTP : ");
    Serial.println(code);
    http.end();
    return;
  }
  String reponse = http.getString();
  http.end();

  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, reponse);
  if (err) {
    Serial.print(PREFIX "JSON invalide : ");
    Serial.println(err.c_str());
    return;
  }
  if (doc["success"] == false) {
    Serial.print(PREFIX "Erreur API : ");
    Serial.println(doc["error"]["info"].as<const char*>());
    return;
  }

  // On suit l'arborescence du JSON
  const char* nom   = doc["location"]["name"];
  const char* heure = doc["location"]["localtime"];
  int temperature   = doc["current"]["temperature"];
  int vent          = doc["current"]["wind_speed"];

  Serial.print(PREFIX "Ville : ");        Serial.println(nom);
  Serial.print(PREFIX "Heure locale : "); Serial.println(heure);
  Serial.print(PREFIX "Temperature : ");  Serial.print(temperature); Serial.println(" C");
  Serial.print(PREFIX "Vent : ");         Serial.print(vent);        Serial.println(" km/h");
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.print(PREFIX "Connexion a ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(PREFIX "...");
  }
  Serial.print(PREFIX "Connecte ! IP : ");
  Serial.println(WiFi.localIP());
  appelerMeteo();
  dernierAppel = millis();
}

void loop() {
  if (millis() - dernierAppel >= INTERVALLE) {
    dernierAppel = millis();
    appelerMeteo();
  }
}

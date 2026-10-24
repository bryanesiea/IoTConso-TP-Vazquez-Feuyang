#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

// Question 2.3 : publie la temperature du BME680 sur Adafruit IO (feed "temperature")
// et s'abonne au feed "led" pour piloter la LED. Base : exemple ESP32_Arduino_MQTT_PubSub de l'enseignant.
#define PREFIX "[Binome 27 - VAZQUEZ & FEUYANG] "

#define WLAN_SSID "XXX"
#define WLAN_PASS "XXX"
#define MQTT_SERVER "io.adafruit.com"
#define MQTT_SERVERPORT 1883
#define MQTT_USERNAME "XXX"
#define MQTT_KEY "XXX"

#define LED_PIN 2

Adafruit_BME680 bme;
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_USERNAME, MQTT_KEY);
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, MQTT_USERNAME "/feeds/temperature");
Adafruit_MQTT_Subscribe led = Adafruit_MQTT_Subscribe(&mqtt, MQTT_USERNAME "/feeds/led");
Adafruit_MQTT_Publish led_lastpub = Adafruit_MQTT_Publish(&mqtt, MQTT_USERNAME "/feeds/led/get");

void MQTT_connect();

// Appelee automatiquement quand un message arrive sur le feed "led"
void ledcallback(char *data, uint16_t len) {
  Serial.print(PREFIX "Callback led, valeur recue : ");
  Serial.println(data);
  digitalWrite(LED_PIN, strcmp(data, "ON") == 0 ? HIGH : LOW);
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println(PREFIX "Adafruit MQTT demo");
  pinMode(LED_PIN, OUTPUT);

  Wire.begin(21, 22);
  if (!bme.begin(0x77) && !bme.begin(0x76)) {
    Serial.println(PREFIX "BME680 introuvable !");
    Serial.flush();
    while (1) { delay(100); }   // delay : evite le reset par le watchdog
  }
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(0, 0);

  Serial.print(PREFIX "Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.setTxPower(WIFI_POWER_8_5dBm);   // limite les pics de courant (redemarrages observes)
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print(PREFIX "WiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  led.setCallback(ledcallback);
  mqtt.subscribe(&led);
  MQTT_connect();
  led_lastpub.publish("\0");   // demande la derniere valeur du feed led
}

void loop() {
  MQTT_connect();
  mqtt.processPackets(5000);   // traite les messages recus pendant 5 s

  if (bme.performReading()) {
    float t = bme.temperature;
    Serial.print(PREFIX "Envoi temperature ");
    Serial.print(t);
    Serial.print(" ... ");
    Serial.println(temperature.publish(t) ? "OK!" : "Failed");
  }
}

void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) return;
  Serial.println(PREFIX "Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {
    Serial.print(PREFIX);
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println(PREFIX "Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries == 0) {
      while (1);   // laisse volontairement le watchdog redemarrer la carte
    }
  }
  Serial.println(PREFIX "MQTT Connected!");
}

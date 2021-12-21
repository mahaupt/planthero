#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define HOSTNAME "plant2"
#define WIFI_SSID "AirLiam2"
#define WIFI_PW "#ng28top6.7111"

#define API_URL "https://api.telegram.org/bot/sendMessage"
#define CHATID ""

uint64_t getCurrentTime();

void initWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
  WiFi.setHostname(HOSTNAME);
  WiFi.setAutoReconnect(true);
  WiFi.begin(WIFI_SSID, WIFI_PW);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println("");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());
}

void sendMsg(const String & msg) {
  HTTPClient http;
  http.begin(API_URL);
  http.addHeader("Content-Type", "application/json");
  http.POST("{\"chat_id\": \"" + String(CHATID) + "\", \"text\": \"" + msg + "\"}");
  http.end();
}

void sendData(double value) {
  long time = getCurrentTime();
  Serial.println(time);
  HTTPClient http;
  http.begin("https://data.mongodb-api.com/app/data-hjows/endpoint/data/beta/action/insertOne");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Access-Control-Request-Headers", "*");
  http.addHeader("api-key", "");
  http.POST("{\"dataSource\": \"Cluster0\", \"database\": \"planthero\", \"collection\": \"sensorvalues\", \"document\": {\"time\": {\"$date\": {\"$numberLong\": \"" + String(time) + "000\"}}, \"value\": " + String(value) + "}}");
  http.end();
}
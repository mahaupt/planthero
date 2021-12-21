#include <Arduino.h>



void takeMeasurement(bool sendHttp = false);
void initWifi();
void sleep();

void setup() {
  Serial.begin(115200);
  initWifi();
  
  delay(100);
  takeMeasurement(true);
  //sleep();
}

void loop() {
  delay(60000);
  takeMeasurement(true);
}


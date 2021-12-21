#include <Arduino.h>

#define SENSOR 36
#define SENSOR_AIR 2600
#define SENSOR_WATER 1150

void sendMsg(const String & msg);
void sendData(double value);

double calcMoisture(uint16_t svalue)
{
  double v = (double)svalue-SENSOR_WATER;
  v /= SENSOR_AIR-SENSOR_WATER;
  v = 1 - v;
  if (v < 0) return 0;
  if (v > 1) return 1;
  return v;
}

void takeMeasurement(bool sendHttp = false) {
  // put your main code here, to run repeatedly:
  uint16_t value = analogRead(SENSOR);
  Serial.print("Value ");
  Serial.print(value);
  Serial.print(" ");
  double v = calcMoisture(value)*100.0;
  Serial.println(v);

  if (sendHttp) {
    sendMsg(String(value) + " " + String(v));
    sendData(v);
  }
}
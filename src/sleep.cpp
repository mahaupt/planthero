#include <Arduino.h>
#include "time.h"

#define THOUR 14

void sleep() {
  /*configTime(0, 3600, "pool.ntp.org");
  struct tm tnow, ttgt, tbegin;
  getLocalTime(&tnow);
  memcpy(&ttgt, &tnow, sizeof(tm));
  memcpy(&tbegin, &tnow, sizeof(tm));
  tbegin.tm_min = 0;
  tbegin.tm_sec = 0;
  tbegin.tm_hour = 0;
  ttgt.tm_min = 0;
  ttgt.tm_sec = 0;
  ttgt.tm_hour = THOUR;
  
  double secsnow = difftime(mktime(&tnow), mktime(&tbegin));
  double secstgt = difftime(mktime(&ttgt), mktime(&tbegin));
  double secsleep = secstgt - secsnow;
  if (secsleep < 0) {
    secsleep += 24*3600; // next day
  }*/
  double secsleep = 600;

  Serial.print("Sleep: ");
  Serial.println(secsleep);
  Serial.flush(); 
  esp_sleep_enable_timer_wakeup(secsleep * 1000000);
  esp_deep_sleep_start();
}

uint64_t getCurrentTime() {
  configTime(0, 3600, "pool.ntp.org");
  struct tm tnow;
  getLocalTime(&tnow);
  return (uint64_t)mktime(&tnow);
}
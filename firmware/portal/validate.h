#ifndef VALIDATE_H
#define VALIDATE_H

#include "config.h"

// Briefly joins the real network to check if captured password is valid.
// NOTE: This temporarily leaves AP mode (~5s) — clients may notice.
bool checkPassword(const String &password) {
  WiFi.mode(WIFI_AP_STA);            // keep AP alive while probing as STA
  WiFi.begin(TARGET_SSID, password.c_str());
  unsigned long start = millis();
  while (millis() - start < 6000) {  // wait up to 6s
    if (WiFi.status() == WL_CONNECTED) {
      WiFi.disconnect();
      return true;
    }
    delay(200);
  }
  WiFi.disconnect();
  return false;
}

#endif

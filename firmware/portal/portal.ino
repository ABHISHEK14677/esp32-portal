#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include "config.h"
#include "handlers.h"

DNSServer dnsServer;
WebServer webServer(80);

void setup() {
  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASS, AP_CHANNEL, 0, AP_MAX_STA);
  delay(100);

  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());  // wildcard DNS -> portal

  registerRoutes(webServer);
  webServer.begin();

  Serial.println("[*] AP up: " AP_SSID);
  Serial.print("[*] Portal: http://");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}

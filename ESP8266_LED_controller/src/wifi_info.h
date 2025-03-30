#ifndef WIFI_INFO_H_
#define WIFI_INFO_H_

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif

#include <ESPAsyncWebServer.h>
#include <Preferences.h>

// 只宣告，不初始化
extern const char *dft_ssid;
extern const char *dft_password;
extern const char *ap_ssid;
extern const char *ap_password;

extern AsyncWebServer server;
extern Preferences preferences;

// WiFi 相關函式
void wifi_connect();
void start_ap_mode();
void handle_wifi_config();
void scan_wifi_networks(AsyncWebServerRequest *request);  // WIFI掃描

#endif /* WIFI_INFO_H_ */

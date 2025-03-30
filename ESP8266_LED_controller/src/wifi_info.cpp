#include "wifi_info.h"

// 變數初始化（這裡才真正定義）
const char *dft_ssid = "WI-FI_2.4G";
const char *dft_password = "hsiu11235";
const char *ap_ssid = "ESP8266-LEDctrl-Setup";
const char *ap_password = "12345678";

// 初始化 Web 伺服器與 Preferences
AsyncWebServer server(80);
Preferences preferences;

// 連接 WiFi
void wifi_connect() {
    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(true);

    // 從 Preferences 讀取 SSID 與密碼
    preferences.begin("wifi", false);
    String ssid = preferences.getString("ssid", dft_ssid);//從 NVS 找 SSID
    String password = preferences.getString("password", dft_password);
    preferences.end();

    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.printf("WiFi connecting to %s...\n", ssid.c_str());

    unsigned long startAttemptTime = millis();

    // 嘗試 30 秒內連接 WiFi
    while (!WiFi.isConnected() && millis() - startAttemptTime < 25000) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");

    if (WiFi.isConnected()) {
        Serial.printf("WiFi connected! IP: %s\n", WiFi.localIP().toString().c_str());
    } else {
        Serial.println("WiFi connect failed. Switching to AP mode...");
        start_ap_mode();
    }
}

// 啟動 AP 模式，並建立設定網頁
void start_ap_mode() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ap_ssid, ap_password);
    Serial.println("AP Mode started!");
    Serial.printf("Connect to WiFi '%s' and go to 192.168.4.1\n", ap_ssid);

    handle_wifi_config();
}

// 處理 Web 設定介面
void handle_wifi_config() {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        String html = "<h1>WiFi Setting</h1>";
        html += "<form action='/set_wifi' method='POST'>";
        html += "SSID: <input type='text' name='ssid'><br>";
        html += "Password: <input type='password' name='password'><br>";
        html += "<input type='submit' value='Save'>";
        html += "</form>";
        request->send(200, "text/html", html);
    });

    server.on("/set_wifi", HTTP_POST, [](AsyncWebServerRequest *request) {
        String ssid, password;

        if (request->hasParam("ssid", true)) {
            ssid = request->getParam("ssid", true)->value();
        }
        if (request->hasParam("password", true)) {
            password = request->getParam("password", true)->value();
        }

        if (ssid.length() > 0) {
            preferences.begin("wifi", false);
            preferences.putString("ssid", ssid);
            preferences.putString("password", password);
            preferences.end();
            request->send(200, "text/html", "<h1>WiFi 設定已儲存！請重新啟動設備。</h1>");
            delay(2000);
            ESP.restart();
        } else {
            request->send(400, "text/html", "<h1>SSID 不可為空！</h1>");
        }
    });

    server.begin();
}

#include "WiFiManager.h"

#include "userBoardDefines.h"

#ifdef M5STACK
#include <M5StickCPlus.h>
#endif
#ifdef GENERIC_ESP32
#include <Arduino.h>
#endif

#include "WiFi.h"
#include "WiFiType.h"
#include "blockClockTypes.h"
#include "esp_smartconfig.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "powerManager.h"
#include "prefsManager.h"
#include "screen.h"

const int WIFI_CONNECTION_TIMEOUT = 200;

void WiFiManager::initWiFi() {
  WiFi.mode(WIFI_AP_STA);

  if (dontHaveWiFiDataInPrefs()) {
    initWiFiSmartConfig();
    delay(3000);
    ESP.restart();
  }

  SsidPasswd ssidPasswd = getPrefsSsidPasswd();

  screen->drawStringPush("Connecting to: " + truncateString(ssidPasswd.ssid),
                         10, 50, 1);
  screen->drawStringPush("Please Stand By", 10, 60, 1);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssidPasswd.ssid.c_str(), ssidPasswd.passwd.c_str());

  int count = 0;

  while (waitingWiFiConnection(WiFi.status(), count)) {
    count++;
    delay(100);
  }

  screen->clearHalfScreen();

  if (connectionFailed(WiFi.status())) {
    screen->drawStringPush(
        "Failed to connect to: " + truncateString(ssidPasswd.ssid), 10, 60, 1);
    screen->drawStringPush("Press main button to wipe WiFi data", 10, 70, 1);
    screen->drawStringPush("Or press other button to restart", 10, 80, 1);

    while (true) {
#ifdef M5STACK
      M5.update();
      if (M5.BtnA.wasPressed()) {
        screen->drawStringPush("Wiping WiFi data and restarting", 10, 90, 1);
        wipeWiFiData();
        delay(4000);
        ESP.restart();
      }

      if (M5.BtnB.wasPressed() || M5.Axp.GetBtnPress()) {
        ESP.restart();
      }
#endif

#ifdef GENERIC_ESP32
      if (digitalRead(BUTTON1PIN) == 0) {
        screen->drawStringPush("Wiping WiFi data and restarting", 10, 90, 1);
        wipeWiFiData();
        delay(4000);
        ESP.restart();
      }
#endif
      delay(1000);
    }
  }

  screen->drawStringPush(
      "Successfuly connected to: " + truncateString(ssidPasswd.ssid), 10, 60,
      1);

  setWiFiMaxPowerSave();
}

void WiFiManager::initWiFiSmartConfig() {
  WiFi.beginSmartConfig(SC_TYPE_ESPTOUCH);

  screen->drawStringPush("Waiting for SmartConfig", 10, 30, 1);

  while (!WiFi.smartConfigDone()) {
    delay(500);
  }

  screen->drawStringPush("Smartconfig received", 10, 40, 1);
  screen->drawStringPush("Trying to connect", 10, 50, 1);

  int count = 0;
  while (waitingWiFiConnection(WiFi.status(), count)) {
    count++;
    delay(100);
  }

  screen->drawStringPush("Connected to: " + WiFi.SSID(), 10, 60, 1);
  screen->drawStringPush("Saving WiFi data", 10, 70, 1);

  String ssid = getSsidPasswd("SSID");
  String password = getSsidPasswd("PASS");

  saveWiFiDataInStorage(ssid, password);

  screen->drawStringPush("Restarting", 10, 80, 1);

  delay(500);
}

bool WiFiManager::waitingWiFiConnection(wl_status_t status, int count) {
  if ((status != WL_CONNECTED && status != WL_CONNECT_FAILED &&
       status != WL_NO_SSID_AVAIL) &&
      count <= WIFI_CONNECTION_TIMEOUT) {
    return true;
  }

  return false;
}

bool WiFiManager::connectionFailed(wl_status_t status) {
  if (status == WL_NO_SSID_AVAIL || status == WL_IDLE_STATUS ||
      status == WL_CONNECT_FAILED || status == WL_DISCONNECTED) {
    return true;
  }

  return false;
}

String WiFiManager::getSsidPasswd(String ssidPasswd) {
  ssidPasswd.toUpperCase();

  wifi_config_t conf;
  esp_wifi_get_config(WIFI_IF_STA, &conf);

  if (ssidPasswd == "SSID") {
    return String(reinterpret_cast<const char*>(conf.sta.ssid));
  }
  if (ssidPasswd == "PASS") {
    return String(reinterpret_cast<const char*>(conf.sta.password));
  }
}

bool WiFiManager::isWiFiConnected() { return WiFi.status() == WL_CONNECTED; }

WiFiData WiFiManager::getWiFiData() {
  WiFiData wifiData;
  wifi_ap_record_t wifiApInformation;

  esp_err_t err = esp_wifi_sta_get_ap_info(&wifiApInformation);

  Serial.println(esp_err_to_name(err));

  if (err != ESP_OK) {
    Serial.println(esp_err_to_name(err));
  }

  wifiData.connected = isWiFiConnected();
  wifiData.SignalStrength = wifiApInformation.rssi;
  wifiData.SSID = String(reinterpret_cast<char*>(wifiApInformation.ssid));

  return wifiData;
}

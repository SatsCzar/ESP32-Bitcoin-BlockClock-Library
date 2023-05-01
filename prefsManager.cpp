#include "prefsManager.h"

#include "WiFiManager.h"
#include "userBoardDefines.h"
#ifdef M5STACK
#include <M5StickCPlus.h>
#endif
#ifdef GENERIC_ESP32
#include <Arduino.h>
#endif

#include <Preferences.h>

#include "blockClockTypes.h"
#include "blockClockUtils.h"

Preferences preferences;

void wipeWiFiData() {
  preferences.begin("wifi");
  preferences.clear();
  preferences.end();
}

SsidPasswd getPrefsSsidPasswd() {
  SsidPasswd ssidPasswd;
  preferences.begin("wifi");

  ssidPasswd.ssid = preferences.getString("ssid", "none");
  ssidPasswd.passwd = preferences.getString("password", "none");

  preferences.end();

  return ssidPasswd;
}

void saveWiFiDataInStorage(String ssid, String password) {
  preferences.begin("wifi");
  preferences.putString("ssid", ssid);
  preferences.putString("password", password);
  preferences.end();
}

bool dontHaveWiFiDataInPrefs() {
  SsidPasswd SsidPasswd = getPrefsSsidPasswd();

  if (SsidPasswd.ssid != "none") {
    return false;
  }

  return true;
}

PriceData getBitcoinDataInPrefs(CurrencyState currency) {
  PriceData priceData;

  String symbol = currencyStateToString(currency);
  String path = "BTC-" + symbol;

  preferences.begin(path.c_str());
  priceData.price = preferences.getString("price", "");
  priceData.change1h = preferences.getFloat("change_1h", 0.0);
  priceData.change24h = preferences.getFloat("change_24h", 0.0);
  priceData.change7d = preferences.getFloat("change_7d", 0.0);
  priceData.change30d = preferences.getFloat("change_30d", 0.0);
  priceData.timestamp = preferences.getLong64("timestamp", 0);
  priceData.error = preferences.getBool("error", false);
  priceData.currency = currency;
  preferences.end();

  return priceData;
}

void saveBitcoinDataInPrefs(PriceData priceData) {
  String symbol = currencyStateToString(priceData.currency);
  String path = "BTC-" + symbol;

  preferences.begin(path.c_str());
  preferences.putString("price", priceData.price);
  preferences.putFloat("change_1h", priceData.change1h);
  preferences.putFloat("change_24h", priceData.change24h);
  preferences.putFloat("change_7d", priceData.change7d);
  preferences.putFloat("change_30d", priceData.change30d);
  preferences.putLong64("timestamp", priceData.timestamp);
  preferences.putBool("error", priceData.error);
  preferences.end();
}
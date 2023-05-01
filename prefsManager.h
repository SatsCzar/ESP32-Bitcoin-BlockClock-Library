#ifndef PREFSMANAGER
#define PREFSMANAGER

#include "userBoardDefines.h"
#ifdef M5STACK
#include <M5StickCPlus.h>
#endif
#ifdef GENERIC_ESP32
#include <Arduino.h>
#endif

#include "WiFiManager.h"
#include "blockClockTypes.h"
#include "blockClockUtils.h"

void wipeWiFiData();
SsidPasswd getPrefsSsidPasswd();
void saveWiFiDataInStorage(String ssid, String password);
bool dontHaveWiFiDataInPrefs();
PriceData getBitcoinDataInPrefs(CurrencyState currency);
void saveBitcoinDataInPrefs(PriceData priceData);

#endif
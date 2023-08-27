#ifndef BLOCKCLOCKUTILS
#define BLOCKCLOCKUTILS

#include "userBoardDefines.h"
#ifdef M5STACK
#include <M5StickCPlus.h>
#endif
#ifdef GENERIC_ESP32
#include <Arduino.h>
#endif

enum ScreenState {
  BLOCKHEIGHT,
  RECOMMENDED_FEES,
  DATEANDTIME,
  PRICE,
  BTC_CHANGE,
  WIFIDATA,
  NUM_SCREEN_STATES
};

enum CurrencyState {
  BRL,
  USD,
  NUM_CURRENCIES_STATES
};

extern ScreenState currentScreenState;
extern CurrencyState currentCurrencyState;

void changeScreenState();
void changeCurrencyState();
String currencyStateToString(CurrencyState currency);
String currencyStateToSymbol(CurrencyState currency);
String intWithThousandSeparator(int number);
String truncateString(String input);
String replaceCommaWithDot(String str);

#endif
#include "blockClockUtils.h"

#include "userBoardDefines.h"
#ifdef M5STACK
#include <M5StickCPlus.h>
#endif
#ifdef GENERIC_ESP32
#include <Arduino.h>
#endif

#include <esp_system.h>

ScreenState currentScreenState = BLOCKHEIGHT;
CurrencyState currentCurrencyState = BRL;

void changeScreenState() {
  currentScreenState =
      static_cast<ScreenState>((currentScreenState + 1) % NUM_SCREEN_STATES);
}

void changeCurrencyState() {
  currentCurrencyState = static_cast<CurrencyState>((currentCurrencyState + 1) %
                                                    NUM_CURRENCIES_STATES);
}

String currencyStateToString(CurrencyState currency) {
  static const String currencies[] = {"BRL", "USD"};

  return currencies[currency];
}

String currencyStateToSymbol(CurrencyState currency) {
  static const String currencies[] = {"R$", "US$"};

  return currencies[currency];
}

String intWithThousandSeparator(int number) {
  String numberStr = String(number);
  int length = numberStr.length();
  int pos = length % 3;

  String result = "";

  for (int i = 0; i < length; i++) {
    if (i > 0 && i % 3 == pos) {
      result += ".";
    }
    result += numberStr.charAt(i);
  }

  return result;
}

String truncateString(String input) {
  if (input.length() > 10) {
    input.remove(7);
    input.concat("...");
  }
  return input;
}

String replaceCommaWithDot(String str) {
  for (int i = 0; i < str.length(); i++) {
    if (str[i] == ',') {
      str[i] = '.';
    }
  }
  return str;
}
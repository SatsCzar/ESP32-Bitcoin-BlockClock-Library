#ifndef SCREEN
#define SCREEN

#include "userBoardDefines.h"

#ifdef M5STACK
#include <M5StickCPlus.h>
#endif

#ifdef GENERIC_ESP32
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#endif

#include "blockClockTypes.h"
#include "blockClockUtils.h"

class Screen {
 private:
  TFT_eSPI *lcd;
  TFT_eSprite *sprite;

 public:
  explicit Screen();
  void initScreen();
  void drawStringPush(String value, int32_t x, int32_t y, uint8_t size);
  void drawString(String value, int32_t x, int32_t y, uint8_t size);
  void clearScreen();
  void clearSprite();
  void drawBlockHeightScreen(String blockheight);
  void drawRecommendedFeesScreen(RecommendedFees recommendedFees);
  void drawnPriceScreen(PriceData priceData);
  void drawnChangeScreen(PriceData priceData);
  void drawnDateAndTimeScreen(String hours, String minutes, String ddmmyyyy);
  void printChange(String time, float change, int16_t x, int16_t y);
  void printFee(String text, uint16_t fee, int16_t x, int16_t y);
  void drawnWiFiDataScreen(WiFiData wifiData);
  void printBattery(int batteryLevel);
  void clearBatterySprite();
  void clearBatteryScreen();
  void clearScreenExceptBattery();
  void setBitcoinTextColor(float delta);
  void resetTextColor();
  void clearHalfScreen();
  void clearSpriteExceptBattery();
};

#endif
#ifndef POWERMANAGER
#define POWERMANAGER

#include "userBoardDefines.h"
#ifdef M5STACK
#include <M5StickCPlus.h>
#endif
#ifdef GENERIC_ESP32
#include <Arduino.h>
#endif

void setWiFiMaxPowerSave();
void setCpuMaxPowerSave();

#ifdef M5STACK
int getBatteryLevel();
int calculateBatteryPercentage(float voltage);
bool isCharging();
#endif

#endif
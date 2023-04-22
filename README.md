# ESP32 Bitcoin BlockClock Library

## Installation

To install the ESP32 Bitcoin BlockClock Library, follow these steps:

1. Download the latest release of the library from its GitHub repository: [ESP32 Bitcoin BlockClock Library](https://github.com/SatsCzar/ESP32-Bitcoin-BlockClock-Library).
2. In the Arduino IDE, go to `Sketch > Include Library > Add .ZIP Library...`.
3. Navigate to the downloaded .zip file and click `Open`. The library will be installed.

Alternatively, you can manually install the library:

1. Download the latest release of the library from its GitHub repository: [ESP32 Bitcoin BlockClock Library](https://github.com/SatsCzar/ESP32-Bitcoin-BlockClock-Library).
2. Extract the contents of the .zip file.
3. Copy the extracted folder to your Arduino libraries folder, usually located at `<Your Documents Folder>/Arduino/libraries/`.

After installation, you should see the library in the Arduino IDE under `Sketch > Include Library`. You can now use the library in your projects by including the appropriate header files.

For a complete guide on how to install an Arduino library, visit the [Arduino Library Installation Guide](https://www.arduino.cc/en/guide/libraries).

## Required Libraries

### For M5StickC Plus:
- [M5StickC Plus](https://github.com/m5stack/M5StickC-Plus)
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson)

### For TTGO T-Display:
- [TTGO T-Display](https://github.com/Xinyuan-LilyGO/TTGO-T-Display)
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson)

## Function Overview

- **ApiClient**: Handles API requests for block height, recommended fees, and Bitcoin price.
- **BlockClockTypes**: Defines data structures for price, WiFi, and recommended fees.
- **BlockClockUtils**: Manages screen state, currency state, and various utility functions.
- **PowerManager**: Configures power saving options and battery management (for M5StickC Plus).
- **prefsManager**: Handles data storage and retrieval from persistent storage.
- **screen**: Manages screen drawing, updates, and text formatting.
- **timeManager**: Handles time synchronization and date/time management.
- **WiFiManager**: Manages WiFi connections, smart configuration, and WiFi data retrieval.

## Credits

This library uses the following third-party libraries and services:

- [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI) by Bodmer
- [M5StickC Plus](https://github.com/m5stack/M5StickC-Plus) by M5Stack
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson) by Benoit Blanchon
- [CoinLib](https://coinlib.io/) for Bitcoin price data
- [mempool.space](https://mempool.space/) for Block Height and Fees data
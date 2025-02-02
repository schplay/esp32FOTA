[![PlatformIO](https://github.com/chrisjoyce911/esp32FOTA/workflows/PlatformIO/badge.svg)](https://github.com/chrisjoyce911/esp32FOTA/actions/)

# esp32FOTA library for Arduino

## Purpose

A simple library to add support for Over-The-Air (OTA) updates to your project. Forked from [https://github.com/chrisjoyce911/esp32FOTA](https://github.com/chrisjoyce911/esp32FOTA)

The original project had grown stale with un-merged PRs. The intention of this fork is to update the lib to make it more useful for full-featured projects.

## Features

- [x] Web update (requires web server)
- [x] Batch firmware sync
- [x] Force firmware update [issues 8]
- [x] https support [#26][i26] ( Thanks to @fbambusi )
- [x] SPIFFS updates ( Thanks to [@tobozo](https://github.com/tobozo) )
- [x] Semantic Version support via ( [semver.c](https://github.com/h2non/semver.c) )
- [ ] Multi firmware update record
- [ ] Stream update (e.g. MQTT or other)
- [ ] Checking for update via bin headers [issue 15]

## How it works

This library tries to access a JSON file hosted on a webserver, and reviews it to decide if a newer firmware has been published, if so it will download it and install it.

There are a few things that need to be in place for an update to work.

- A webserver with the firmware information in a JSON file
- Firmware version
- Firmware type
- Firmware bin
- SPIFFS bin

## Usage

### Hosted JSON

This is hosted by a webserver and contains information about the latest firmware

```json
{
    "type": "esp32-fota-http",
    "version": "2.0",
    "host": "192.168.0.100",
    "port": 80,
    "bin": "/fota/esp32-fota-http-2.ino.bin",
    "spiffs": "/fota/esp32-fota-http-2.spiffs.bin"
}
```

#### Firmware types

Types are used to compare with the current loaded firmware, this is used to make sure that when loaded, the device will still do the intended job.

As an example, a device used as a data logger should ony be updated with new versions of the data logger.

##### examples

- TTGO-T8-ESP32-Logger
- TTGO-T8-ESP32-Temp
- TTGO-T8-ESP32-Relay


### Debug

Messages depends of build level. If you pass -D CORE_DEBUG_LEVEL=3 to build flags, it enable the messages

### Sketch

In this example a version 1  of 'esp32-fota-http' is in use, it would be updated when using the JSON example.

```cpp
#include <esp32fota.h>
#include <WiFi.h>

const char *ssid = "";
const char *password = "";

esp32FOTA esp32FOTA("esp32-fota-http", "1.0");

void setup()
{
  esp32FOTA.checkURL = "http://server/fota/fota.json";
  Serial.begin(115200);
  setup_wifi();
}

void setup_wifi()
{
  delay(10);
  Serial.print("Connecting to ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
}

void loop()
{
  bool updatedNeeded = esp32FOTA.execHTTPcheck();
  if (updatedNeeded)
  {
    esp32FOTA.execOTA();
  }
  delay(2000);
}
```

[issue 15]: https://github.com/chrisjoyce911/esp32FOTA/issues/15
[issues 8]: https://github.com/chrisjoyce911/esp32FOTA/issues/8

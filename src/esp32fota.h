/*
   esp32 firmware OTA
   Date: December 2018
   Author: Chris Joyce <https://github.com/chrisjoyce911/esp32FOTA/esp32FOTA>
   Purpose: Perform an OTA update from a bin located on a webserver (HTTP Only)
*/

#ifndef esp32fota_h
#define esp32fota_h

#include "Arduino.h"
#include <WiFiClientSecure.h>

class esp32FOTA
{
public:
  esp32FOTA(String firwmareType, String firwmareVersion);
  void forceUpdate(String firwmareHost, int firwmarePort, String firwmarePath, String spiffsPath="");
  void execOTA();
  void execOTA(int partition);
  bool execHTTPcheck();
  String getPayloadVersion();
  bool useDeviceID;
  String checkURL;
  WiFiClient clientForOta;

private:
  String getDeviceID();
  String _firwmareType;
  String _firwmareVersion;
  String _payloadVersion;
  String _host;
  String _bin;
  String _spiffs;
  int _port;

};

class secureEsp32FOTA
{
public:
  secureEsp32FOTA(String firwmareType, String firwmareVersion);
  bool execHTTPSCheck();
  void executeOTA();
  void executeOTA(int partition);
  String getPayloadVersion();
  String _descriptionOfFirmwareURL;
  char *_certificate;
  unsigned int _securePort = 443;
  WiFiClientSecure clientForOta;
  String _host;

private:
  bool prepareConnection(String locationOfServer);
  String secureGetContent();
  bool isValidContentType(String line);
  String _firwmareType;
  String _firwmareVersion;
  String _payloadVersion;
  String locationOfFirmware;
  String _bin;
  String _spiffs;
  int _port;
};

#endif

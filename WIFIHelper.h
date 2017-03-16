// WIFIHelper.h

#ifndef _WIFIHELPER_h
#define _WIFIHELPER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>

class WIFIHelperClass
{
 protected:


 public:
	InfoFromCaptiveWiFiClass Info;
	void captiveWiFi();
};

extern WIFIHelperClass WIFIHelper;

#endif


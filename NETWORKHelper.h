// NETWORKHelper.h

#ifndef _NETWORKHELPER_h
#define _NETWORKHELPER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "DebugGitsy.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>

const String fingerprint_github		= "21 99 13 84 63 72 17 13 b9 ed 0e 8f 00 a5 9b 73 0d d0 56 58";
const String fingerprint_firebase	= "20 94 9a 11 02 81 8e 54 54 f7 b6 8e bb c1 67 54 93 67 55 86";

class NETWORKHelperClass
{
private:
	String getVersion_handle(String raw_gitsyVersion);
	String getURL_handle(String raw_gitsyVersion);
protected:
	
	bool getVersion_fromGithub(String& version, String& url);
	bool getVersion_fromFirebase(String& version, String& url);
public:
	String request(String link, String thumbprint = fingerprint_github);
	bool getFirmwareLastestVersion(String& version, String& url);
	int updateFirmware(String link, String newVersion);

};

extern NETWORKHelperClass NetworkHelper;

#endif


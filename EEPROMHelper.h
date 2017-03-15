// EEPROMHelper.h

#ifndef _EEPROMHELPER_h
#define _EEPROMHELPER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <EEPROM.h>

class EEPROMHelperClass
{
protected:
	void writeString(int address, String data);
	String readString(int address);
public:
	void init();
	void save_BlynkInfo(String auth, String domain, uint16_t port);
	bool get_BlynkInfo(String& auth, String& domain, uint16_t& port);
	void save_WifiInfo(String ssid, String password);
	bool get_WifiInfo(String& ssid, String& password);
	void eraser();
};

extern EEPROMHelperClass EEPROMHelper;

#endif


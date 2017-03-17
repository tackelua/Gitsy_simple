// EEPROMHelper.h

#ifndef _EEPROMHELPER_h
#define _EEPROMHELPER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "DebugGitsy.h"
#include <EEPROM.h>

#if defined(DEBUG) && defined(TEST_EEPROM)
#define DEBUG_EEPROM DEBUG
#endif // DEBUG

class EEPROMHelperClass
{
protected:
	void writeString(int address, String data);
	String readString(int address);
public:
	void init();

	void update_WifiInfo(String ssid, String password);
	bool get_WifiInfo(String& ssid, String& password);

	void update_BlynkInfo(String auth, String domain, uint16_t port);
	bool get_BlynkInfo(String& auth, String& domain, uint16_t& port);
		
	void save_Info(String ssid, String password, String auth, String domain, uint16_t port);
	bool get_Info(String& ssid, String& password, String& auth, String& domain, uint16_t& port);
	
	void end();
	void eraser();
};

extern EEPROMHelperClass EEPROMHelper;

#endif


// BLYNKHelper.h

#ifndef _BLYNKHELPER_h
#define _BLYNKHELPER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "DebugGitsy.h"
#include <BlynkSimpleEsp8266.h>
#include <Blynk\BlynkConfig.h>

#if defined(DEBUG) && defined(TEST_BLYNK)
#define DEBUG_BLYNK DEBUG
#define BLYNK_PRINT DEBUG_BLYNK
#endif // DEBUG

class BLYNKHelperClass
{
 protected:
	 String _auth;
	 String _domain = BLYNK_DEFAULT_DOMAIN;
	 uint16_t _port = BLYNK_DEFAULT_PORT;

 public:
	//Default: domain=_domain, port= _port
	void init(String ssid, String password, String auth, String domain = "", uint16_t port = 0);
	void begin(String auth, String domain = "", uint16_t port = 0);
	bool run();
};

extern BLYNKHelperClass BlynkHelper;

#endif


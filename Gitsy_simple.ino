#include <Blynk.h>
#include "DebugGitsy.h"
#include "Declarations.h"
#include "EEPROMHelper.h"
#include "FIREBASEHelper.h"
#include "BLYNKHelper.h"
#include "WIFIHelper.h"

#ifdef RUN_MAIN

void setup()
{
	EEPROMHelper.init();

#ifdef DEBUG
	DEBUG.begin(74880);
#endif // DEBUG

	if (WiFiHelper.begin())
	{
	BEGIN:
		String _ssid = InfoFromWiFiMangager.WIFI_SSID;
		String _password = InfoFromWiFiMangager.WIFI_PASSWORD;
		String _auth = InfoFromWiFiMangager.BLYNK_AUTH;
		String _domain = InfoFromWiFiMangager.BLYNK_DOMAIN;
		uint16_t _port = InfoFromWiFiMangager.BLYNK_PORT;
#ifdef DEBUG
		DEBUG.println(_ssid);
		DEBUG.println(_password);
		DEBUG.println(_auth);
		DEBUG.println(_domain);
		DEBUG.println(_port);
#endif // DEBUG
		EEPROMHelper.save_Info(_ssid, _password, _auth, _domain, _port);
		BlynkHelper.begin(_auth, _domain, _port);
	}
	else
	{
#ifdef DEBUG
		DEBUG.println("WiFi connected");
		DEBUG.println(WiFi.localIP());
#endif // DEBUG
		String _auth;
		String _domain;
		uint16_t _port;
		if (EEPROMHelper.get_BlynkInfo(_auth, _domain, _port))
		{
			BlynkHelper.begin(_auth, _domain, _port);
		}
		else
		{
#ifdef DEBUG
			DEBUG.println("EEPROM does not have Blynk Info");
			DEBUG.flush();
#endif // DEBUG

			WiFiHelper.captiveWiFi();
			goto BEGIN;
		}
	}
	check_FreeRAM("after setup()");
}

void loop()
{
	BlynkHelper.run();
}

#endif // RUN_MAIN
#include "DebugGitsy.h"
#include "Declarations.h"
#include "EEPROMHelper.h"
#include "FIREBASEHelper.h"
#include "BLYNKHelper.h"
#include "WIFIHelper.h"
#include "NETWORKHelper.h"
#include "BlynkGitsyFunctions.h"

#ifdef RUN_MAIN

void setup()
{
	EEPROMHelper.init();

	gitsyStart();
	gitsyCheckUpdate();

	Blynk.virtualWrite(BLYNK_PIN_LABLE_IP, WiFi.localIP().toString());
	terminal.println(F("\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n"));
	terminal.println(F("Device started !"));
	terminal.println(F("Blynk v" BLYNK_VERSION));
	terminal.println(F("Type /help for show more commands"));
	terminal.flush();

	Blynk.syncAll();

#ifdef DEBUG
	DEBUG.println("Time: " + String(millis()));
	check_FreeRAM("after setup()");
#endif // DEBUG

}

void loop()
{
	BlynkHelper.run();
}

#endif // RUN_MAIN

void gitsyStart() {
#ifdef DEBUG
	DEBUG.begin(74880);
	check_FreeRAM("start");
	DEBUG.println(_version);
	DEBUG.println(WiFi.macAddress());
	DEBUG.println("Wait for connect...");
#endif // DEBUG

	if (WiFiHelper.begin())
	{
	BEGIN:
		String _ssid = InfoFromWiFiMangager.WIFI_SSID;
		String _password = InfoFromWiFiMangager.WIFI_PASSWORD;
		String _auth = InfoFromWiFiMangager.BLYNK_AUTH;
		String _domain = InfoFromWiFiMangager.BLYNK_DOMAIN;
		uint16_t _port = InfoFromWiFiMangager.BLYNK_PORT;
		EEPROMHelper.save_Info(_ssid, _password, _auth, _domain, _port);
		BlynkHelper.begin(_auth, _domain, _port);
		FirebaseHelper.set_Info(_ssid, _password, _auth, _domain, _port);
	}
	else
	{
#ifdef DEBUG
		DEBUG.println("WiFi connected");
		DEBUG.println(WiFi.localIP());
#endif // DEBUG
		String _ssid;
		String _password;
		String _auth;
		String _domain;
		uint16_t _port;
		if(EEPROMHelper.get_Info(_ssid, _password, _auth, _domain, _port))
		//if (EEPROMHelper.get_BlynkInfo(_auth, _domain, _port))
		{
			BlynkHelper.begin(_auth, _domain, _port);
			FirebaseHelper.set_Info(_ssid, _password, _auth, _domain, _port);
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
}


void gitsyCheckUpdate() {
	String version;
	String url;
	bool autoUpdate;
	if (NetworkHelper.getFirmwareLastestVersion(version, url, autoUpdate)) {
#ifdef DEBUG
		DEBUG.println("SUCCESS");
		DEBUG.println(version);
		DEBUG.println(url);
#endif // DEBUG

		if (autoUpdate) {
			if ((version.compareTo(_version) != 0) && (url.length() > 0)) {
				NetworkHelper.updateFirmware(url, version);
			}
		}
	}
	else
	{
#ifdef DEBUG
		Serial.println("FAILED");
#endif // DEBUG
	}
}
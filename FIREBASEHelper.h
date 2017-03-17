// FIREBASEHelper.h

#ifndef _FIREBASEHELPER_h
#define _FIREBASEHELPER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "DebugGitsy.h"
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#if defined(DEBUG) && defined(TEST_FIREBASE)
#define DEBUG_FIREBASE DEBUG
#endif // DEBUG

#define FIREBASE_HOST "blynk-database.firebaseio.com"
#define FIREBASE_AUTH "iY7AlCgTDrXD6AYKX579nKW2WrqXKKBUMfep9rVs" 
//Auth token secrets at link https://console.firebase.google.com/project/blynk-database/settings/serviceaccounts/databasesecrets

#define path_isCreated "Firebase_isCreated"

#define path_isWifiUptodate "Wifi_isUpToDate"
#define path_ssid "Wifi_SSID"
#define path_password "Wifi_Passphrase"
#define path_ip "Wifi_IP"

#define path_isBlynkUptodate "Blynk_isUpToDate"
#define path_auth "Blynk_Auth"
#define path_domain "Blynk_Domain"
#define path_port "Blynk_Port"

#define path_LastestFirmware "LastestFirmware"
#define path_version "Version"
#define path_url "URL"
#define path_autoUpdate "Auto Update"


class FIREBASEHelperClass
{
private:
	bool began = false;
protected:
	String path_log = "Logs/" + String(WiFi.macAddress());
	String path = "ClientDetails/" + (String)WiFi.macAddress();
	bool lastCommand_failed(String at = "");
	bool lastCommand_success(String at = "");
	void init(String host = FIREBASE_HOST, String auth = FIREBASE_AUTH);

public:
	bool get_FirmwareInfo(String& version, String& url, bool& autoUpdate);

	bool update_WifiInfo(String ssid, String password);
	bool get_WifiInfo(String& ssid, String& password, bool& isUpToDate);

	bool update_BlynkInfo(String auth, String domain, uint16_t port);
	bool get_BlynkInfo(String& auth, String& domain, uint16_t& port, bool& isUpToDate);

	bool set_Info(String ssid, String password, String auth, String domain, uint16_t port);
	bool get_Info(String& ssid, String& password, String& auth, String& domain, uint16_t& port);

	bool log(String log);
	bool remove();
};

extern FIREBASEHelperClass FirebaseHelper;

#endif


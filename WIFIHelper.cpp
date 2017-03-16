// 
// 
// 

#include "DebugGitsy.h"
#include "WIFIHelper.h"

#if defined(DEBUG) && defined(TEST_WIFI_HELPER)
#define DEBUG_WIFI_HELPER DEBUG
#endif // DEBUG

void WIFIHelperClass::captiveWiFi()
{
	//WiFiManager
	//Local intialization. Once its business is done, there is no need to keep it around
	WiFiManager wifiManager;

	//reset settings - for testing
	//wifiManager.resetSettings();

	//sets timeout until configuration portal gets turned off
	//useful to make it all retry or go to sleep
	//in seconds
	//wifiManager.setTimeout(120);

	//it starts an access point with the specified name
	//here  "AutoConnectAP"
	//and goes into a blocking loop awaiting configuration

	//WITHOUT THIS THE AP DOES NOT SEEM TO WORK PROPERLY WITH SDK 1.5 , update to at least 1.5.1
	//WiFi.mode(WIFI_STA);

	Serial.print("Mode: ");
	Serial.println(WiFi.getMode());
	Serial.print("PhyMode: ");
	Serial.println(WiFi.getPhyMode());
	Serial.print("softAPgetStationNum: ");
	Serial.println(WiFi.softAPgetStationNum());

	//if (!wifiManager.startConfigPortal("OnDemandAP")) {
	if (!wifiManager.startConfigPortal("Gitsy"/* + String(WiFi.macAddress().substring(String(WiFi.macAddress()).length() - 2))).c_str()*/)) {
		Serial.println("failed to connect and hit timeout");
		delay(3000);
		//reset and try again, or maybe put it to deep sleep
		ESP.reset();
		delay(5000);
	}

	//if you get here you have connected to the WiFi
	Serial.println("connected...yeey :)");

}


WIFIHelperClass WIFIHelper;


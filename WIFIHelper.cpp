// 
// 
// 

#include "DebugGitsy.h"
#include "WIFIHelper.h"

#if defined(DEBUG) && defined(TEST_WIFI_HELPER)
#define DEBUG_WIFI_HELPER DEBUG
#endif // DEBUG

String gith_fullHeader;
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

#ifdef DEBUG_WIFI_HELPER
	DEBUG_WIFI_HELPER.println("\r\nWiFiHelper.captiveWiFi()");
	DEBUG_WIFI_HELPER.print("Mode: ");
	DEBUG_WIFI_HELPER.println(WiFi.getMode());
	DEBUG_WIFI_HELPER.print("PhyMode: ");
	DEBUG_WIFI_HELPER.println(WiFi.getPhyMode());
	DEBUG_WIFI_HELPER.print("softAPgetStationNum: ");
	DEBUG_WIFI_HELPER.println(WiFi.softAPgetStationNum());
#endif // DEBUG_WIFI_HELPER

	String mac = String(WiFi.macAddress());
	byte len = mac.length();
	mac = String(mac.charAt(len - 4)) + mac.substring(len - 2);
	if (!wifiManager.startConfigPortal(("Gitsy" + mac).c_str())) {
#ifdef DEBUG_WIFI_HELPER
		DEBUG_WIFI_HELPER.println("failed to connect and hit timeout");
#endif // DEBUG_WIFI_HELPER

		//reset and try again, or maybe put it to deep sleep
		ESP.reset();
		delay(1000);
	}

	gith_fullHeader = "";
#ifdef DEBUG_WIFI_HELPER
	//if you get here you have connected to the WiFi
	DEBUG_WIFI_HELPER.println("connected...yeey :)");

	String _ssid = InfoFromWiFiMangager.WIFI_SSID;
	String _password = InfoFromWiFiMangager.WIFI_PASSWORD;
	String _auth = InfoFromWiFiMangager.BLYNK_AUTH;
	String _domain = InfoFromWiFiMangager.BLYNK_DOMAIN;
	uint16_t _port = InfoFromWiFiMangager.BLYNK_PORT;

	DEBUG_WIFI_HELPER.println(_ssid);
	DEBUG_WIFI_HELPER.println(_password);
	DEBUG_WIFI_HELPER.println(_auth);
	DEBUG_WIFI_HELPER.println(_domain);
	DEBUG_WIFI_HELPER.println(_port);
	DEBUG_WIFI_HELPER.flush();
#endif // DEBUG_WIFI_HELPER

}

bool WIFIHelperClass::begin() {
	WiFi.setAutoConnect(true);
	WiFi.setAutoReconnect(true);
	if (WiFi.waitForConnectResult() == WL_CONNECTED)
	{
		//ket noi san sang, chua co data trong InfoFromWiFiMangager
		return false;
	}
	else
	{
		//Thong tin wifi chua duoc luu truoc do
		captiveWiFi();
		return true;
	}
}

WIFIHelperClass WiFiHelper;


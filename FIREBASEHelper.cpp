// 
// 
// 

#include "FIREBASEHelper.h"

void FIREBASEHelperClass::init(String host, String auth)
{
	Firebase.begin(host, auth);
	path = "ClientDetails/" + (String)WiFi.macAddress();
}

bool FIREBASEHelperClass::set_Info(String ssid, String password, String auth, String domain, uint16_t port) {
	DynamicJsonBuffer jsonBuffer;
	JsonObject& jsonWifi = jsonBuffer.createObject();

	jsonWifi[path_isCreated] = true;
	jsonWifi[path_isWifiUptodate] = true;
	jsonWifi[path_isBlynkUptodate] = true;

	jsonWifi[path_auth] = auth;
	jsonWifi[path_domain] = domain;
	jsonWifi[path_port] = port;

	jsonWifi[path_ssid] = ssid;
	jsonWifi[path_password] = password;
	jsonWifi[path_ip] = WiFi.localIP().toString();

	Serial.print("re-Read port from jsonWifi: ");
	Serial.println(jsonWifi.get<uint16_t>(path_port));

#ifdef DEBUG_FIREBASE
	DEBUG_FIREBASE.println("FirebaseHelper.update_WifiInfo()");
	jsonWifi.prettyPrintTo(DEBUG_FIREBASE);
	DEBUG_FIREBASE.println();
#endif // DEBUG_FIREBASE

	Firebase.set(path, jsonWifi);
	if (Firebase.success()) {
#ifdef DEBUG_FIREBASE
		DEBUG_FIREBASE.println("Success");
#endif // DEBUG_FIREBASE
		return true;
	}
	if (Firebase.failed()) {
#ifdef DEBUG_FIREBASE
		DEBUG_FIREBASE.println("Failed.");
		DEBUG_FIREBASE.println(Firebase.error());
#endif // DEBUG_FIREBASE
		return false;
	}
}

FIREBASEHelperClass FirebaseHelper;


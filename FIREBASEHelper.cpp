// 
// 
// 

#include "FIREBASEHelper.h"

void FIREBASEHelperClass::init(String host, String auth)
{
	Firebase.begin(host, auth);
	path = "ClientDetails/" + (String)WiFi.macAddress();
}

bool FIREBASEHelperClass::lastCommand_failed(String at) {
	bool _failed = Firebase.failed();
	if (_failed) {
#ifdef DEBUG_FIREBASE
		if (at.length() > 0) {
			DEBUG_FIREBASE.print(at);
		}
		DEBUG_FIREBASE.println("\tFailed");
		DEBUG_FIREBASE.println(Firebase.error());
#endif // DEBUG_FIREBASE
	}
	return _failed;
}
bool FIREBASEHelperClass::lastCommand_success(String at) {
	bool _success = Firebase.success();
	if (_success) {
#ifdef DEBUG_FIREBASE
		if (at.length() > 0) {
			DEBUG_FIREBASE.print(at);
		}
		DEBUG_FIREBASE.println("\tSuccess");
#endif // DEBUG_FIREBASE
	}
	return _success;
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

#ifdef DEBUG_FIREBASE
	DEBUG_FIREBASE.println("\r\nFirebaseHelper.set_Info()");
	jsonWifi.prettyPrintTo(DEBUG_FIREBASE);
	DEBUG_FIREBASE.println();
#endif // DEBUG_FIREBASE

	Firebase.set(path, jsonWifi);
	if (lastCommand_success()) {
		return true;
	}
	if (lastCommand_failed()) {
		return false;
	}
}
bool FIREBASEHelperClass::get_Info(String& ssid, String& password, String& auth, String& domain, uint16_t& port) {
#ifdef DEBUG_FIREBASE
	DEBUG_FIREBASE.println("\r\nFirebaseHelper.get_Info()");
#endif // DEBUG_FIREBASE

	FirebaseObject ObjInfo = Firebase.get(path);
	if (Firebase.success()) {
#ifdef DEBUG_FIREBASE
		DEBUG_FIREBASE.println("Success");
		ObjInfo.getJsonVariant().prettyPrintTo(DEBUG_FIREBASE);
		DEBUG_FIREBASE.println();
#endif // DEBUG_FIREBASE

		ssid = ObjInfo.getString(path_ssid);
		password = ObjInfo.getString(path_password);
		auth = ObjInfo.getString(path_auth);
		domain = ObjInfo.getString(path_domain);
		port = uint16_t(ObjInfo.getInt(path_port));

		return true;
	}
	if (lastCommand_failed()) {
		return false;
	}
}

bool FIREBASEHelperClass::update_WifiInfo(String ssid, String password) {
#ifdef DEBUG_FIREBASE
	DEBUG_FIREBASE.println("\r\nFirebaseHelper.update_WifiInfo()");
#endif // DEBUG_FIREBASE

	Firebase.setString(path + "/" path_ssid, ssid);

	if (lastCommand_failed(path_ssid)) {
		return false;
	}
	if (lastCommand_success(path_ssid)) {
		Firebase.setString(path + "/" path_password, password);
		if (lastCommand_failed(path_password)) {
			return false;
		}
		if (lastCommand_success(path_password)) {
			Firebase.setBool(path + "/" path_isWifiUptodate, true);
			if (lastCommand_failed(path_isWifiUptodate)) {
				return false;
			}
			if (lastCommand_success(path_isWifiUptodate)) {
				return true;
			}
		}
	}
}
bool FIREBASEHelperClass::get_WifiInfo(String& ssid, String& password, bool& isUpToDate) {
#ifdef DEBUG_FIREBASE
	DEBUG_FIREBASE.println("\r\nFirebaseHelper.get_WifiInfo()");
#endif // DEBUG_FIREBASE

	FirebaseObject ObjInfo = Firebase.get(path);
	if (Firebase.success()) {
#ifdef DEBUG_FIREBASE
		DEBUG_FIREBASE.println("Success");
		ObjInfo.getJsonVariant().prettyPrintTo(DEBUG_FIREBASE);
		DEBUG_FIREBASE.println();
#endif // DEBUG_FIREBASE

		ssid = ObjInfo.getString(path_ssid);
		password = ObjInfo.getString(path_password);
		isUpToDate = ObjInfo.getBool(path_isWifiUptodate);

		return true;
	}
	if (lastCommand_failed()) {
		return false;
	}
}

bool FIREBASEHelperClass::update_BlynkInfo(String auth, String domain, uint16_t port) {
#ifdef DEBUG_FIREBASE
	DEBUG_FIREBASE.println("\r\nFirebaseHelper.update_BlynkInfo()");
#endif // DEBUG_FIREBASE

	Firebase.setString(path + "/" path_auth, auth);
	if (lastCommand_failed(path_auth)) {
		return false;
	}
	if (lastCommand_success(path_auth)) {
		Firebase.setString(path + "/" path_domain, domain);
		if (lastCommand_failed(path_domain)) {
			return false;
		}
		if (lastCommand_success(path_domain)) {
			Firebase.setInt(path + "/" path_port, port);
			if (lastCommand_failed(path_port)) {
				return false;
			}
			if (lastCommand_success(path_port)) {
				Firebase.setBool(path + "/" path_isBlynkUptodate, true);
				if (lastCommand_failed(path_isBlynkUptodate)) {
					return false;
				}
				if (lastCommand_success(path_isBlynkUptodate)) {
					return true;
				}
			}
		}
	}
}
bool FIREBASEHelperClass::get_BlynkInfo(String& auth, String& domain, uint16_t& port, bool& isUpToDate) {
#ifdef DEBUG_FIREBASE
	DEBUG_FIREBASE.println("\r\nFirebaseHelper.get_WifiInfo()");
#endif // DEBUG_FIREBASE

	FirebaseObject ObjInfo = Firebase.get(path);
	if (Firebase.success()) {
#ifdef DEBUG_FIREBASE
		DEBUG_FIREBASE.println("Success");
		ObjInfo.getJsonVariant().prettyPrintTo(DEBUG_FIREBASE);
		DEBUG_FIREBASE.println();
#endif // DEBUG_FIREBASE

		auth = ObjInfo.getString(path_auth);
		domain = ObjInfo.getString(path_domain);
		port = uint16_t(ObjInfo.getBool(path_port));
		isUpToDate = ObjInfo.getBool(path_isBlynkUptodate);

		return true;
	}
	if (lastCommand_failed()) {
		return false;
	}
}


FIREBASEHelperClass FirebaseHelper;


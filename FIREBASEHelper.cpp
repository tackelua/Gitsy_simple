// 
// 
// 

#include "FIREBASEHelper.h"

void FIREBASEHelperClass::init(String host, String auth)
{
	if (!began) {
		began = true;
		Firebase.begin(host, auth);
		//path = "ClientDetails/" + (String)WiFi.macAddress(); //init in default
	}
}

bool FIREBASEHelperClass::lastCommand_failed(String at) {
	bool _failed = Firebase.failed();
	if (_failed) {
#ifdef DEBUG_FIREBASE
		if (at.length() > 0) {
			DEBUG_FIREBASE.print(at);
			DEBUG_FIREBASE.print("\t");
		}
		DEBUG_FIREBASE.println("Failed");
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
			DEBUG_FIREBASE.print("\t");
		}
		DEBUG_FIREBASE.println("Success");
#endif // DEBUG_FIREBASE
	}
	return _success;
}

bool FIREBASEHelperClass::set_Info(String ssid, String password, String auth, String domain, uint16_t port) {

	init();

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
	jsonWifi[path_FirmwareVersion] = String(_version);

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

	init();

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

bool FIREBASEHelperClass::get_FirmwareInfo(String& version, String& url, bool& autoUpdate) {
	
	init();

#ifdef DEBUG_FIREBASE
	DEBUG_FIREBASE.println("\r\nFirebaseHelper.get_FirmwareInfo()");
#endif // DEBUG_FIREBASE

	FirebaseObject ObjInfo = Firebase.get(path_LastestFirmware);
	if (Firebase.success()) {
		version = ObjInfo.getString(path_version);
		url = ObjInfo.getString(path_url);
		autoUpdate = ObjInfo.getBool(path_autoUpdate);
#ifdef DEBUG_FIREBASE
		DEBUG_FIREBASE.println("Success");
		ObjInfo.getJsonVariant().prettyPrintTo(DEBUG_FIREBASE);
		DEBUG_FIREBASE.println();
		//DEBUG_FIREBASE.println(version);
		//DEBUG_FIREBASE.println(url);
#endif // DEBUG_FIREBASE

		return true;
	}
	if (lastCommand_failed()) {
		return false;
	}
}


bool FIREBASEHelperClass::update_WifiInfo(String ssid, String password) {

	init();

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

	init();

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

	init();

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

	init();

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

//bool FIREBASEHelperClass::set_FVersion_IP() {
//
//	init();
//
//#ifdef DEBUG_FIREBASE
//	DEBUG_FIREBASE.println("\r\nFirebaseHelper.set_FVersion_IP()");
//#endif // DEBUG_FIREBASE
//	Firebase.setString(path_version, _version);
//	if (lastCommand_failed(path_version)) {
//		return false;
//	}
//	if (lastCommand_success(path_version)) {
//		Firebase.setString(path_ip, WiFi.localIP().toString());
//		if (lastCommand_failed(path_ip)) {
//			return false;
//		}
//		if (lastCommand_success(path_ip)) {
//			return true;
//		}
//	}
//}

bool FIREBASEHelperClass::log(String log) {

	init();

#ifdef DEBUG_FIREBASE
	DEBUG_FIREBASE.println("\r\nFirebaseHelper.log()");
#endif // DEBUG_FIREBASE
	Firebase.pushString(path_log, log);
}

bool FIREBASEHelperClass::remove() {

	init();

#ifdef DEBUG_FIREBASE
	DEBUG_FIREBASE.println("\r\nFirebaseHelper.remove()");
#endif // DEBUG_FIREBASE

	Firebase.remove(path);
	if (lastCommand_success()) {
		return true;
	}
	if (lastCommand_failed()) {
		return false;
	}
}

FIREBASEHelperClass FirebaseHelper;


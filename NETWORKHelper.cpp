// 
// 
// 

#include "NETWORKHelper.h"
#include "FIREBASEHelper.h"
//#include "EEPROMHelper.h"
#include "gitsyVersion.h"
#include <ESP8266httpUpdate.h>

String NETWORKHelperClass::getVersion_handle(String raw_gitsyVersion) {
	String gitsy_version = raw_gitsyVersion;
	int idx = gitsy_version.lastIndexOf("_version \""); //data in file: #define _version "v0.2.4 20170310"
	if (idx == -1)
	{
		return "";
	}
	else
	{
		gitsy_version = gitsy_version.substring(idx);
		gitsy_version = gitsy_version.substring(10, gitsy_version.lastIndexOf("\""));
#ifdef DEBUG_NETWORK
		DEBUG_NETWORK.println("gitsyVersion: " + gitsy_version);
#endif // DEBUG_NETWORK

		return gitsy_version;
	}
}

String NETWORKHelperClass::getURL_handle(String raw_gitsyVersion) {
	String url = raw_gitsyVersion;
	int _pos = url.indexOf("<url>");
	if (_pos > -1) {
		url = url.substring(_pos + 5);
		_pos = url.indexOf("</url>");
		if (_pos > -1) {
			url = url.substring(0, _pos);
#ifdef DEBUG_NETWORK
			DEBUG_NETWORK.println("URL: " + url);
#endif // DEBUG_NETWORK
			return url;
		}
	}
	return "";
}

String NETWORKHelperClass::request(String link, String thumbprint)
{
#ifdef DEBUG_NETWORK
	DEBUG_NETWORK.println("NetworkHelper.Request()");
	DEBUG_NETWORK.println(link);
#endif // DEBUG_NETWORK

	HTTPClient http;

	//USE_SERIAL.print("[HTTP] begin...\n");
	// configure traged server and url
	//http.begin("https://araw.githubusercontent.com/tackelua/gitsy/master/gitsy_version.h", fingerprint); //HTTPS gith
	//http.begin("http://gitsy.16mb.com/gitsy/firmwares/gitsy_version.h"); //HTTP
	//http.begin(link);

	if (link.indexOf("https") == 0)
	{
		http.begin(link, thumbprint);
	}
	else if (link.indexOf("http") == 0)
	{
		http.begin(link);
	}


	//Serial.print("http code: ");
	//Serial.println(http.GET());
	//Serial.println(http.getString());

	int httpCode = http.GET();

	if (httpCode == HTTP_CODE_OK) {
		String payload = http.getString();
		http.end();
#ifdef DEBUG_NETWORK
		DEBUG_NETWORK.println(payload);
#endif // DEBUG_NETWORK
		return payload;
	}
	else
	{
#ifdef DEBUG_NETWORK
		DEBUG_NETWORK.print(httpCode);
		DEBUG_NETWORK.println(" Failed");
		DEBUG_NETWORK.println(http.errorToString(httpCode));
#endif // DEBUG_NETWORK
		http.end();
		return "";
	}
}

bool NETWORKHelperClass::getVersion_fromGithub(String& version, String& url) {
#ifdef DEBUG_NETWORK
	DEBUG_NETWORK.println("\r\ngetVersion_fromGithub()");
#endif // DEBUG_NETWORK
	String raw_gitsyVersion_h = request("https://raw.githubusercontent.com/tackelua/Gitsy_simple/master/gitsyVersion.h");
	if (raw_gitsyVersion_h.length() > 0) {
		String _ver = getVersion_handle(raw_gitsyVersion_h);
		if (_ver.length() > 0) {
			version = _ver;
			String _url = getURL_handle(raw_gitsyVersion_h);
			if (_url.length() > 0) {
				url = _url;
				return true;
			}
		}
	}
	return false;
}

bool NETWORKHelperClass::getVersion_fromFirebase(String& version, String& url) {
#ifdef DEBUG_NETWORK
	DEBUG_NETWORK.println("\r\ngetVersion_fromFirebase()");
#endif // DEBUG_NETWORK
	return FirebaseHelper.get_FirmwareInfo(version, url);
}

bool NETWORKHelperClass::getFirmwareLastestVersion(String& version, String& url) {
#ifdef DEBUG_NETWORK
	DEBUG_NETWORK.println("\r\ngetFirmwareLastestVersion()");
#endif // DEBUG_NETWORK
	if (getVersion_fromGithub(version, url))
	{
		return true;
	}
	else
	{
		if (getVersion_fromFirebase(version, url)) {
			if ((version.length() == 0) || (url.length() == 0)) {
				return false;
			}
		}
		else
		{
			return false;
		}
	}
}

int NETWORKHelperClass::updateFirmware(String link, String newVersion)
{
#ifdef DEBUG_NETWORK
	DEBUG_NETWORK.println("\r\nNetworkHelper.updateFirmware()");
	DEBUG_NETWORK.println(link);
	DEBUG_NETWORK.flush();
#endif // DEBUG_NETWORK

	FirebaseHelper.log("Update " _version " to " + newVersion);
	//EEPROMHelper.end();

	//ESPhttpUpdate.rebootOnUpdate(true);
	int result;
	if (link.indexOf("http:") == 0)
	{
#ifdef DEBUG_NETWORK
		DEBUG_NETWORK.println("http update");
		DEBUG_NETWORK.flush();
#endif // DEBUG_NETWORK
		result = ESPhttpUpdate.update(link);
		delay(1000);
	}
	else if(link.indexOf("https") == 0)
	{
#ifdef DEBUG_NETWORK
		DEBUG_NETWORK.println("https update");
		DEBUG_NETWORK.flush();
#endif // DEBUG_NETWORK
		result = ESPhttpUpdate.update(link, _version, fingerprint_firebase);
		delay(1000);
	}
	switch (result)
	{
	case HTTP_UPDATE_FAILED:
#ifdef DEBUG_NETWORK
		DEBUG_NETWORK.println("HTTP_UPDATE_FAILED");
		DEBUG_NETWORK.flush();
#endif // DEBUG_NETWORK
		FirebaseHelper.log("HTTP_UPDATE_FAILED");
		break;
	case HTTP_UPDATE_NO_UPDATES:
#ifdef DEBUG_NETWORK
		DEBUG_NETWORK.println("HTTP_UPDATE_NO_UPDATES");
		DEBUG_NETWORK.flush();
#endif // DEBUG_NETWORK
		FirebaseHelper.log("HTTP_UPDATE_NO_UPDATES");
		break;
	case HTTP_UPDATE_OK:
#ifdef DEBUG_NETWORK
		DEBUG_NETWORK.println("HTTP_UPDATE_OK");
		DEBUG_NETWORK.flush();
#endif // DEBUG_NETWORK
		break;
	default:
		break;
	}

	return result;
}
NETWORKHelperClass NetworkHelper;


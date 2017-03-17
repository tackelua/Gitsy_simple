#ifdef TEST_NETWORK

#include "NETWORKHelper.h"
#include "gitsyVersion.h"

void setup() {
	Serial.begin(74880);
	check_FreeRAM("");
	Serial.println(_version);
	Serial.println("Connecting...");
	WiFi.begin("IoT Guest", "mic@dtu12345678()");
	WiFi.waitForConnectResult();
	if (WiFi.isConnected()) {
		Serial.println("Connected");
	}
	FirebaseHelper.init();
	String version, url;
	if (NetworkHelper.getFirmwareLastestVersion(version, url)) {
		Serial.println("SUCCESS");
		Serial.println(version);
		Serial.println(url);
	}
	else
	{
		Serial.println("FAILED");
	}

	if ((version != String(_version)) && (url.length() > 0)) {
		NetworkHelper.updateFirmware(url, version);
	}
	
	check_FreeRAM("end setup()");
}

void loop() {
	;
}

#endif // TEST_NETWORK


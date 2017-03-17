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

	gitsyCheckUpdate();

	check_FreeRAM("end setup()");
}

void loop() {
	if (Serial.available() > 0) {
		String a = Serial.readString();
		if (a.indexOf("restart") > -1) {
			ESP.restart();
			delay(1000);
		}
		else if (a.indexOf("reset") > -1)
		{
			ESP.reset();
			delay(1000);
		}
	}
}

#endif // TEST_NETWORK

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
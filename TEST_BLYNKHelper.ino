#ifdef TEST_BLYNK

#include "BLYNKHelper.h"


void setup() {
	String WIFI_SSID = "IoT Guest";
	String WIFI_PASS = "mic@dtu12345678()";
	String BLYNK_AUTH = "cd677497e6c4467d83e22c72a8b61498";
	String BLYNK_DOMAIN = "thec.vn";
	DEBUG.begin(74880);
	BlynkHelper.init(WIFI_SSID, WIFI_PASS, BLYNK_AUTH, BLYNK_DOMAIN);

	delay(1000);
	String newAuth = "fa8066adb93f4f73bacdcc78594d37a3";
	BlynkHelper.begin(newAuth);
}

void loop() {
	BlynkHelper.run();

}

#endif // TEST_BLYNK
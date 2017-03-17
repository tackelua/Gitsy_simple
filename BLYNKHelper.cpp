// 
// 
// 

#include "BLYNKHelper.h"

void BLYNKHelperClass::init(String ssid, String password, String auth, String domain, uint16_t port)
{
	_auth = auth;
	if (domain != "") {
		_domain = domain;
	}
	if (port != 0) {
		_port = port;
	}
	Blynk.begin(_auth.c_str(), ssid.c_str(), password.c_str(), _domain.c_str(), _port);
}
void BLYNKHelperClass::begin(String auth, String domain, uint16_t port) {
#ifdef DEBUG_BLYNK
	DEBUG_BLYNK.println("\r\nBlynkHelper.begin()");
#endif // DEBUG_BLYNK
	_auth = auth;
	if (domain != "") {
		_domain = domain;
	}
	if (port != 0) {
		_port = port;
	}
	Blynk.disconnect();
	Blynk.config(_auth.c_str(), _domain.c_str(), _port);

#ifdef DEBUG_BLYNK
	unsigned long t = millis();
#endif // DEBUG_BLYNK

	while (Blynk.connect() != true) {
#ifdef DEBUG_BLYNK
		if ((millis() - t) > 100) {
			t = millis();
			DEBUG_BLYNK.print(".");
		}
#endif // DEBUG_BLYNK
		delay(1);
	}
#ifdef DEBUG_BLYNK
	DEBUG_BLYNK.println();
#endif // DEBUG_BLYNK
}
bool BLYNKHelperClass::run() {
	return Blynk.run();
}

BLYNKHelperClass BlynkHelper;


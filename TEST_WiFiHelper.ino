#ifdef TEST_WIFI_HELPER

void setup() {
	Serial.begin(74880);
	if (WiFiHelper.begin())
	{
		Serial.println(InfoFromWiFiMangager.BLYNK_AUTH);
		Serial.println(InfoFromWiFiMangager.BLYNK_DOMAIN);
		Serial.println(InfoFromWiFiMangager.BLYNK_PORT);
		Serial.println(InfoFromWiFiMangager.WIFI_PASSWORD);
		Serial.println(InfoFromWiFiMangager.WIFI_SSID);
	}
	else
	{
		Serial.println("WiFi connected");
		Serial.println(WiFi.localIP());
	}
}

void loop() {
	;
}
#endif // TEST_WIFI_HELPER
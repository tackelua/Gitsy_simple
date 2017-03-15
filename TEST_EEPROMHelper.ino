#ifdef TEST_EEPROM

#ifdef DEBUG
#define DEBUG_EEPROM DEBUG
#endif // DEBUG

void setup() {
	EEPROMHelper.init();
	DEBUG_EEPROM.begin(74880);
	String blAuth, blDomain;
	uint16_t blPort;

	String wfSSID, wfPW;

	String tAuth, tDomain;
	uint16_t tPort;
	String tSSID, tPW;
	tAuth = "fa8066adb93f4f73bacdcc78594d37a3";
	tDomain = "blynk-cloud.com";
	tPort = 8442;

	DEBUG.println("Saving Info");
	EEPROMHelper.save_Info("ssid", "password", "this_is_Blynk_auth Token", "domain.git", 1234);
	String a, b, c, d;
	uint16_t e;
	EEPROMHelper.get_Info(a, b, c, d, e);
	DEBUG.println("get Info:" + a + "|" + b + "|" + c + "|" + d + "|" + String(e));

	DEBUG.println("Saving Blynk Info");
	EEPROMHelper.save_BlynkInfo(tAuth, tDomain, tPort);
	if (EEPROMHelper.get_BlynkInfo(blAuth, blDomain, blPort))
	{
		DEBUG_EEPROM.println("get_BlynkInfo:" + blAuth + "|" + blDomain + "|" + String(blPort));
		tSSID = "DayLaTen WiFi";
		tPW = "This is PW";
	}

	DEBUG.println("Saving Wifi Info");
	EEPROMHelper.save_WifiInfo(tSSID, tPW);
	if (EEPROMHelper.get_WifiInfo(wfSSID, wfPW))
	{
		DEBUG_EEPROM.println("get_WifiInfo:" + wfSSID + "|" + wfPW);
	}

	DEBUG_EEPROM.println("Erasing");
	EEPROMHelper.eraser();

	DEBUG_EEPROM.println("Read again");
	if (EEPROMHelper.get_BlynkInfo(blAuth, blDomain, blPort))
	{
		DEBUG_EEPROM.println("BLYNK:" + blAuth + "|" + blDomain + "|" + String(blPort));
	}
	else
	{
		DEBUG_EEPROM.println("No Blynk Info");
	}

	if (EEPROMHelper.get_WifiInfo(wfSSID, wfPW))
	{
		DEBUG_EEPROM.println("WIFI:" + wfSSID + "|" + wfPW);
	}
	else
	{
		DEBUG_EEPROM.println("No Wifi Info");
	}

	DEBUG_EEPROM.println("Force Read");
	DEBUG_EEPROM.println("Blynk:" + blAuth + "|" + blDomain + "|" + String(blPort));
	DEBUG_EEPROM.println("Wifi:" + wfSSID + "|" + wfPW);
}

void loop() {
	;
}

#endif // TEST_EEPROM
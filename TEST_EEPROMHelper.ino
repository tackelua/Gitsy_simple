#ifdef TEST_EEPROM

#define DEBUG_EEPROM DEBUG

void setup() {
	EEPROMHelper.init();
	DEBUG_EEPROM.begin(74880);
	String blAuth;// = _emptyArray;
	String blDomain;// = _emptyArray;
	uint16_t blPort;

	String wfSSID;// = _emptyArray;
	String wfPW;// = _emptyArray;

	String tAuth, tDomain;
	uint16_t tPort;
	String tSSID, tPW;
	tAuth = "fa8066adb93f4f73bacdcc78594d37a3";
	tDomain = "blynk-cloud.com";
	tPort = 8442;

	DEBUG.println("Saving Blynk Info");
	EEPROMHelper.save_BlynkInfo(tAuth, tDomain, tPort);
	if (EEPROMHelper.get_BlynkInfo(blAuth, blDomain, blPort))
	{
		DEBUG_EEPROM.println("BLYNK:" + blAuth + "|" + blDomain + "|" + String(blPort));
		tSSID = "DayLaTen WiFi";
		tPW = "This is PW";
	}

	EEPROMHelper.save_WifiInfo(tSSID, tPW);
	if (EEPROMHelper.get_WifiInfo(wfSSID, wfPW))
	{
	DEBUG_EEPROM.println("BLYNK:" + blAuth + "|" + blDomain + "|" + String(blPort));
	}

	DEBUG_EEPROM.println("Erasing");
	EEPROMHelper.eraser();

	DEBUG_EEPROM.println("Read again");
	if (EEPROMHelper.get_BlynkInfo(blAuth, blDomain, blPort));
	{
		DEBUG_EEPROM.println("BLYNK:" + blAuth + "|" + blDomain + "|" + String(blPort));
	}
	if (EEPROMHelper.get_WifiInfo(wfSSID, wfPW))
	{
		DEBUG_EEPROM.println("BLYNK:" + blAuth + "|" + blDomain + "|" + String(blPort));
	}
}

void loop() {
	;
}

#endif // TEST_EEPROM
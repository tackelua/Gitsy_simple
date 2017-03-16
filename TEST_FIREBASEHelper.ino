#ifdef TEST_FIREBASE

void setup()
{
	Serial.begin(74880);
	Serial.println("Start");
	WiFi.begin("IoT Guest", "mic@dtu12345678()");
	WiFi.waitForConnectResult();
	if (WiFi.isConnected()) {
		Serial.println("Connected");
	}
	check_FreeRAM("before Firebase");
	
	FirebaseHelper.init(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop()
{
	check_FreeRAM("before update_WifiInfo");

	static int i = 0;
	FirebaseHelper.update_WifiInfo("new ssid" + String(i++), "new pw" + String(i));
	delay(1000);
	String ns, np;
	bool ni;
	FirebaseHelper.get_WifiInfo(ns, np, ni);
	Serial.println(ns);
	Serial.println(np);
	Serial.println(ni);

	FirebaseHelper.update_BlynkInfo(ns, np, ni);
	delay(1000);
	FirebaseHelper.remove();
	delay(5000);

}

void testFirebase(String path) {
	ulong t = millis();
	FirebaseObject a = Firebase.get(path);
	if (Firebase.success()) {
		Serial.println("\nSuccess");
		a.getJsonVariant().prettyPrintTo(Serial);

		Serial.println();
		String b = a.getString(path_auth);
		Serial.println(b);

		//a.getJsonVariant()["abc"] = "abcddd";

		bool bl = a.getBool("abc");
		Serial.println(bl);

		bl = a.getBool("Blynk_isUpToDate");
		Serial.println(bl);

		bl = a.getBool(path_ip);
		Serial.println(bl);

		JsonVariant jva = a.getJsonVariant();
		Firebase.set("New JasionVariant From Firebase.get", jva);

		
	}
	if (Firebase.failed()) {
		Serial.println(Firebase.error());
	}
	t = millis() - t;
	Serial.println("t = " + String(t));

	JsonVariant jv = a.getJsonVariant();
	JsonObject& jo = jv.as<JsonObject>();
	jo["Wifi_SSID"] = "new SSID";
	jo["new field"] = "OK new";

	Firebase.set("hello", jo);

	DynamicJsonBuffer jsonBuffer;

	// create an object
	JsonObject& object1 = jsonBuffer.createObject();
	object1[path_password] = "passwordgith";
	Firebase.set("/", object1);
	check_FreeRAM("end testFirebase");

}
#endif // RUN_MAIN


uint32_t check_FreeRAM(String free_ram_at) {
	uint32_t freeRam = ESP.getFreeHeap();
#ifdef DEBUG
	DEBUG.println("Free RAM " + free_ram_at + ": " + (String)freeRam);
	DEBUG.flush();
#endif // DEBUG
	return freeRam;
}
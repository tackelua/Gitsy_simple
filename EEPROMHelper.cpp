// 
// 
// 

#include <EEPROM.h>
#include "EEPROMHelper.h"

#ifdef DEBUG
#define DEBUG_EEPROM DEBUG
#endif // DEBUG

#define EXIST_STRING "true"

#define EEPROM_SIZE 300
#define EEPROM_ADDR_EXIST 0
#define EEPROM_ADDR_BLYNK_TOKEN 10
#define EEPROM_ADDR_BLYNK_DOMAIN 50
#define EEPROM_ADDR_BLYNK_PORT 110

#define EEPROM_ADDR_WIFI_SSID 160
#define EEPROM_ADDR_WIFI_PASSWORD 210

void EEPROMHelperClass::init()
{
	EEPROM.begin(EEPROM_SIZE);
}

void EEPROMHelperClass::writeString(int address, String data) {
#ifdef DEBUG_EEPROM
	DEBUG_EEPROM.print("EEPROM WriteString at " + String(address));
	DEBUG_EEPROM.println(" - DATA = " + data);
	DEBUG_EEPROM.flush();
#endif // DEBUG_EEPROM
	for (int i = 0; i < data.length(); i++) {
		EEPROM.write(address + i, data.charAt(i));
		//delay(1);
	}
	EEPROM.write(address + data.length(), 0);
	delay(10);
	EEPROM.commit();
}

String EEPROMHelperClass::readString(int address) {
	char data_array[50];
	EEPROM.get(address, data_array);
	String str_ret = data_array;
#ifdef DEBUG_EEPROM
	DEBUG_EEPROM.print("EEPROM ReadString at " + String(address));
	DEBUG_EEPROM.println(" - DATA = " + str_ret);
	DEBUG_EEPROM.flush();
#endif // DEBUG_EEPROM
	return str_ret;
}

void EEPROMHelperClass::save_BlynkInfo(String auth, String domain, uint16_t port) {
#ifdef DEBUG_EEPROM
	DEBUG_EEPROM.println("Save Blynk to EEPROM: " + auth + " | " + domain + " | " + String(port));
#endif // DEBUG_EEPROM

	writeString(EEPROM_ADDR_EXIST, EXIST_STRING);
	writeString(EEPROM_ADDR_BLYNK_TOKEN, auth);
	writeString(EEPROM_ADDR_BLYNK_DOMAIN, domain);
	writeString(EEPROM_ADDR_BLYNK_PORT, (String)port);
}

bool EEPROMHelperClass::get_BlynkInfo(String& auth, String& domain, uint16_t& port) {
	String haveToken = readString(EEPROM_ADDR_EXIST);
	if (haveToken == EXIST_STRING) {
		auth = readString(EEPROM_ADDR_BLYNK_TOKEN);
		domain = readString(EEPROM_ADDR_BLYNK_DOMAIN);
		port = readString(EEPROM_ADDR_BLYNK_PORT).toInt();
		return true;
	}
	else return false;
}

void EEPROMHelperClass::save_WifiInfo(String ssid, String password) {
#ifdef DEBUG_EEPROM
	DEBUG_EEPROM.println("Save WiFi to EEPROM: " + ssid + " | " + password);
#endif // DEBUG_EEPROM

	writeString(EEPROM_ADDR_EXIST, EXIST_STRING);
	writeString(EEPROM_ADDR_WIFI_SSID, ssid);
	writeString(EEPROM_ADDR_WIFI_PASSWORD, password);
}

bool EEPROMHelperClass::get_WifiInfo(String& ssid, String& password) {
	String haveToken = readString(EEPROM_ADDR_EXIST);
	if (haveToken == EXIST_STRING) {
		ssid = readString(EEPROM_ADDR_WIFI_SSID);
		password = readString(EEPROM_ADDR_WIFI_PASSWORD);
		return true;
	}
	else return false;
}

void EEPROMHelperClass::eraser() {
	for (int i = 0; i < EEPROM_SIZE; i++) {
		EEPROM.write(i, 0);
		delay(1);
	}
	delay(10);
	EEPROM.commit();
}

EEPROMHelperClass EEPROMHelper;

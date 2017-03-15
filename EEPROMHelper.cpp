//
// Use save_Info to save flag in EEPROM, update_WifiInfo and update_BlynkInfo do not save flag
// tackelua@gmail.com 2017-03-15
//  

#include <EEPROM.h>
#include "EEPROMHelper.h"

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
	for (int i = 0; i < data.length(); i++) {
		EEPROM.write(address + i, data.charAt(i));
		delay(1);
	}
	EEPROM.write(address + data.length(), 0);
	delay(10);
	EEPROM.commit();
}

String EEPROMHelperClass::readString(int address) {
	char data_array[50];
	EEPROM.get(address, data_array);
	String str_ret = data_array;
	return str_ret;
}

void EEPROMHelperClass::update_WifiInfo(String ssid, String password) {
	//writeString(EEPROM_ADDR_EXIST, EXIST_STRING);
	writeString(EEPROM_ADDR_WIFI_SSID, ssid);
	writeString(EEPROM_ADDR_WIFI_PASSWORD, password);
}
bool EEPROMHelperClass::get_WifiInfo(String& ssid, String& password) {
	String haveInfo = readString(EEPROM_ADDR_EXIST);
	if (haveInfo == EXIST_STRING) {
		ssid = readString(EEPROM_ADDR_WIFI_SSID);
		password = readString(EEPROM_ADDR_WIFI_PASSWORD);
		return true;
	}
	else return false;
}

void EEPROMHelperClass::update_BlynkInfo(String auth, String domain, uint16_t port) {
	//writeString(EEPROM_ADDR_EXIST, EXIST_STRING);
	writeString(EEPROM_ADDR_BLYNK_TOKEN, auth);
	writeString(EEPROM_ADDR_BLYNK_DOMAIN, domain);
	writeString(EEPROM_ADDR_BLYNK_PORT, (String)port);
}
bool EEPROMHelperClass::get_BlynkInfo(String& auth, String& domain, uint16_t& port) {
	String haveInfo = readString(EEPROM_ADDR_EXIST);
	if (haveInfo == EXIST_STRING) {
		auth = readString(EEPROM_ADDR_BLYNK_TOKEN);
		domain = readString(EEPROM_ADDR_BLYNK_DOMAIN);
		port = readString(EEPROM_ADDR_BLYNK_PORT).toInt();
		return true;
	}
	else return false;
}

void EEPROMHelperClass::save_Info(String ssid, String password, String auth, String domain, uint16_t port) {
	writeString(EEPROM_ADDR_EXIST, EXIST_STRING);
	writeString(EEPROM_ADDR_WIFI_SSID, ssid);
	writeString(EEPROM_ADDR_WIFI_PASSWORD, password);
	writeString(EEPROM_ADDR_BLYNK_TOKEN, auth);
	writeString(EEPROM_ADDR_BLYNK_DOMAIN, domain);
	writeString(EEPROM_ADDR_BLYNK_PORT, (String)port);
}
bool EEPROMHelperClass::get_Info(String& ssid, String& password, String& auth, String& domain, uint16_t& port) {
	String haveInfo = readString(EEPROM_ADDR_EXIST);
	if (haveInfo == EXIST_STRING) {
		ssid = readString(EEPROM_ADDR_WIFI_SSID);
		password = readString(EEPROM_ADDR_WIFI_PASSWORD);
		auth = readString(EEPROM_ADDR_BLYNK_TOKEN);
		domain = readString(EEPROM_ADDR_BLYNK_DOMAIN);
		port = readString(EEPROM_ADDR_BLYNK_PORT).toInt();
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

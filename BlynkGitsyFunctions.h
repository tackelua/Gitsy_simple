#ifndef _BLYNKGITSYFUNCTIONS_H
#define _BLYNKGITSYFUNCTIONS_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include <BlynkSimpleEsp8266.h>
#include "DebugGitsy.h"
#include "gitsyVersion.h"

#pragma region DEFINE_BLYNK_PIN
#define BLYNK_PIN_TERMINAL	V0
#define BLYNK_PIN_LABLE_IP	V10

//#define BLYNK_PIN_BUTTON_0	V0
#define BLYNK_PIN_BUTTON_1	V1
#define BLYNK_PIN_BUTTON_2	V2
#define BLYNK_PIN_BUTTON_3	V3
#define BLYNK_PIN_BUTTON_4	V4
#define BLYNK_PIN_BUTTON_5	V5
#define BLYNK_PIN_BUTTON_6	V6
#define BLYNK_PIN_BUTTON_7	V7
#define BLYNK_PIN_BUTTON_8	V8
#define BLYNK_PIN_BUTTON_9	V9
#define BLYNK_PIN_BUTTON_10	V10

//#define BLYNK_PIN_BUTTON_0	V10
#define BLYNK_PIN_SLIDER_1	V11
#define BLYNK_PIN_SLIDER_2	V12
#define BLYNK_PIN_SLIDER_3	V13
#define BLYNK_PIN_SLIDER_4	V14
#define BLYNK_PIN_SLIDER_5	V15
#define BLYNK_PIN_SLIDER_6	V16
#define BLYNK_PIN_SLIDER_7	V17
#define BLYNK_PIN_SLIDER_8	V18
#define BLYNK_PIN_BUTTON_9	V19
#define BLYNK_PIN_BUTTON_10	V20
#pragma endregion

WidgetTerminal terminal(BLYNK_PIN_TERMINAL);

#pragma region FunctionsHelper
int Virtual_to_Digital(int pin) {
	switch (pin) {
	case V0: return D0;
	case V1: return D1;
	case V2: return D2;
	case V3: return D3;
	case V4: return D4;
	case V5: return D5;
	case V6: return D6;
	case V7: return D7;
	case V8: return D8;
#if defined(ARDUINO_ESP8266_NODEMCU)
	case V9: return D9;
	case V10: return D10;
#endif // ARDUINO_ESP8266_NODEMCU

	default: return -1;
	}
}
int Digital_to_Virtual(int pin) {
	switch (pin) {
	case D0: return V0;
	case D1: return V1;
	case D2: return V2;
	case D3: return V3;
	case D4: return V4;
	case D5: return V5;
	case D6: return V6;
	case D7: return V7;
	case D8: return V8;
#if defined(ARDUINO_ESP8266_NODEMCU)
	case D9: return V9;
	case D10: return V10;
#endif // ARDUINO_ESP8266_NODEMCU

	default: return -1;
	}
}

int Button_to_Slider(int button) {
	if ((button >= V1) && (button <= V10)) {
		return (button + 10);
	}
	return -1;
}
int Slider_to_Button(int slider) {
	if ((slider >= V10) && (slider <= V20)) {
		return (slider - 10);
	}
	return -1;
}
void BlynkWrite_ButtonHelper(int button, int param_asInt) {
	if ((param_asInt == 0) || (param_asInt = 1)) {
		Blynk.virtualWrite(Button_to_Slider(button), param_asInt ? 1023 : 0);
		//delay(10);
		digitalWrite(Virtual_to_Digital(button), param_asInt);
#ifdef DEBUG
		DEBUG.print("BLYNK_PIN_BUTTON_V" + String(button) + " value: ");
		DEBUG.println(param_asInt);
#endif // DEBUG
	}
}
void BlynkWrite_SliderHelper(int slider, int param_asInt) {
	analogWrite(Virtual_to_Digital(Slider_to_Button(slider)), param_asInt);
	Blynk.virtualWrite(Slider_to_Button(slider), bool(param_asInt));
#ifdef DEBUG
	DEBUG.print("BLYNK_PIN_SLIDER_V" + String(slider) + "  value: ");
	DEBUG.println(param_asInt);
#endif // DEBUG
}
#pragma endregion

BLYNK_WRITE(BLYNK_PIN_TERMINAL)
{
	// if you type "Marco" into Terminal Widget - it will respond: "Polo:"
	if (String("/help") == param.asStr())
	{
#ifdef DEBUG_BLYNK
		DEBUG_BLYNK.println("terminal> /help");
#endif // DEBUG_BLYNK

		terminal.println("/rs\tRestart your device");
		terminal.println(F("/na\tUpdate new Blynk Auth Token"));
		terminal.println(F("/sy\tSynchronous status"));
		terminal.println(F("/fw\tCheck your current firmware"));
		terminal.println(F("/lf\tCheck lastest firmware"));
		terminal.println(F("/uf\tUpdate lastest firmware"));
		terminal.println(F("/ip\tShow your ip"));
		terminal.println(F("/cl\tClear screen"));
	}
	else if (String("/rs") == param.asStr())
	{
#ifdef DEBUG_BLYNK
		DEBUG_BLYNK.println("terminal> /rs");
#endif // DEBUG_BLYNK
		terminal.println(F("Your device is being restarted...\r\n"));
		terminal.flush();
		delay(500);
		ESP.restart();
		delay(5000);
	}
	else if (String(param.asStr()).indexOf("/na") > -1)
	{
#ifdef DEBUG_BLYNK
		DEBUG_BLYNK.println("terminal> /na");
#endif // DEBUG_BLYNK
		String dataStr = param.asStr();
		String Blynk_auth, Blynk_domain;
		uint16_t Blynk_port;
		EEPROMHelper.get_BlynkInfo(Blynk_auth, Blynk_domain, Blynk_port);

		if (dataStr.length() == 3)
		{
			terminal.println(F("/na <Auth> <Server> <Port>\r\n<Server> <Port> are optional.\r\nExample:\r\n/na fa8066adb93f4f73bacdcc78594dd7a4\r\n/na fa8066adb93f4f73bacdcc78594dd7a4 blynk-cloud.com 8442\r\nMake sure for your infomation are correct, you can not change after sending"));
		}
		else
		{
			int pos_auth = dataStr.indexOf(" ");
			if (pos_auth > -1)
			{
				String newData = dataStr.substring(pos_auth + 1);
				int pos_domain = newData.indexOf(" ");
				if (pos_domain == -1)
				{
					Blynk_auth = newData;
				}
				else
				{
					Blynk_auth = newData.substring(0, pos_domain);
					newData = newData.substring(pos_domain + 1);
					int pos_port = newData.indexOf(" ");
					if (pos_port == -1)
					{
						Blynk_domain = newData;
					}
					else
					{
						Blynk_domain = newData.substring(0, pos_port);
						newData = newData.substring(pos_port + 1);
						Blynk_port = newData.toInt();
					}
				}
			}
			if ((Blynk_auth != "") && (Blynk_domain != "") && (Blynk_port != 0)) {
#ifdef DEBUG
				DEBUG.println("Auth: " + Blynk_auth);
				DEBUG.println("Domain: " + Blynk_domain);
				DEBUG.println("Port: " + (String)Blynk_port);
#endif // DEBUG
				BlynkHelper.begin(Blynk_auth, Blynk_domain, Blynk_port);
				EEPROMHelper.update_BlynkInfo(Blynk_auth, Blynk_domain, Blynk_port);
				FirebaseHelper.update_BlynkInfo(Blynk_auth, Blynk_domain, Blynk_port);
			}
		}
	}
	else if (String("/sy") == param.asStr())
	{
#ifdef DEBUG_BLYNK
		DEBUG_BLYNK.println("terminal> /sy");
#endif // DEBUG_BLYNK
		Blynk.virtualWrite(BLYNK_PIN_LABLE_IP, WiFi.localIP().toString());
		Blynk.syncAll();
		for (byte i = 0; i <= 4; i++) {
			Blynk.syncVirtual(i);
			Blynk.syncVirtual(10 + i);
		}
		terminal.println(F("Sync done."));
	}
	else if (String("/uf") == param.asStr())
	{
#ifdef DEBUG_BLYNK
		DEBUG_BLYNK.println("terminal> /uf");
#endif // DEBUG_BLYNK
		String lf, url;
		bool up;
		NetworkHelper.getFirmwareLastestVersion(lf, url, up);
		if (lf.compareTo(_version) == 0) {
			terminal.print(F("Your firmware is lastest: "));
			terminal.println(lf);
		}
		else {
			terminal.print(F("Lastest version: "));
			terminal.println(lf);
			terminal.println(F("Firmware updating. Please wait a moment!"));
			terminal.flush();
			NetworkHelper.updateFirmware(url, lf);
			//check_firmware_isUpdate(serverUpdate, true); //restart if update done.
			terminal.println(F("Update can not complete."));
		}
	}
	else if (String("/fw") == param.asStr())
	{
#ifdef DEBUG_BLYNK
		DEBUG_BLYNK.println("terminal> /fw");
#endif // DEBUG_BLYNK
		terminal.println(_version);
	}
	else if (String("/lf") == param.asStr())
	{
#ifdef DEBUG_BLYNK
		DEBUG_BLYNK.println("terminal> /lf");
#endif // DEBUG_BLYNK
		String lf = Firebase.getString(F("LastestFirmware/Version"));
		terminal.println(lf);
	}
	else if (String("/ip") == param.asStr())
	{
#ifdef DEBUG_BLYNK
		DEBUG_BLYNK.println("terminal> /ip");
#endif // DEBUG_BLYNK
		terminal.println(WiFi.localIP());
		Blynk.virtualWrite(BLYNK_PIN_LABLE_IP, WiFi.localIP().toString());
	}
	else if (String("/cl") == param.asStr())
	{
#ifdef DEBUG_BLYNK
		DEBUG_BLYNK.println("terminal> /cl");
#endif // DEBUG_BLYNK
		terminal.println(F("\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n"));
	}
	else if (String("/factoryreset") == param.asStr())
	{
#ifdef DEBUG_BLYNK
		DEBUG_BLYNK.println("terminal> /factoryreset");
#endif // DEBUG_BLYNK
		terminal.println("Eraser EEPROM");
		EEPROMHelper.eraser();
		EEPROMHelper.end();

		terminal.println("Eraser Firebase");
		FirebaseHelper.remove();

		terminal.println("WiFi Disconnect");
		terminal.flush();
		WiFi.disconnect();
		WiFi.setAutoConnect(false);
		delay(1000);
		ESP.restart();
		delay(1000);
	}

	//else {
	//	terminal.println(F("Wrong command"));
	//}

	// Ensure everything is sent
	terminal.flush();
}

BLYNK_READ(BLYNK_PIN_LABLE_IP) {
	Blynk.virtualWrite(BLYNK_PIN_LABLE_IP, WiFi.localIP().toString());
}

#pragma region BLYNK_PIN_4
BLYNK_WRITE(BLYNK_PIN_BUTTON_4){
	BlynkWrite_ButtonHelper(BLYNK_PIN_BUTTON_4, param.asInt());
}
BLYNK_WRITE(BLYNK_PIN_SLIDER_4) {
	BlynkWrite_SliderHelper(BLYNK_PIN_SLIDER_4, param.asInt());
}
#pragma endregion




#ifdef ARDUINO_ESP8266_NODEMCU
BLYNK_WRITE(BLYNK_PIN_BUTTON_9){
	BlynkWrite_ButtonHelper(Digital_to_Virtual(BLYNK_PIN_SLIDER_9), param.asInt());
}
BLYNK_WRITE(BLYNK_PIN_BUTTON_10){
	BlynkWrite_ButtonHelper(Digital_to_Virtual(BLYNK_PIN_SLIDER_10), param.asInt());
}
#endif // ARDUINO_ESP8266_NODEMCU


#endif // !_BLYNKGITSYFUNCTIONS_H
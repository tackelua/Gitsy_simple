#include <BlynkSimpleEsp8266.h>
#include "gitsyVersion.h"

#define BLYNK_PIN_TERMINAL	V0
#define BLYNK_PIN_BUTTON1	V1
#define BLYNK_PIN_BUTTON2	V2
#define BLYNK_PIN_BUTTON3	V3
#define BLYNK_PIN_BUTTON4	V4
#define BLYNK_PIN_BUTTON5	V5
#define BLYNK_PIN_BUTTON6	V6
#define BLYNK_PIN_BUTTON7	V7
#define BLYNK_PIN_BUTTON8	V8
#define BLYNK_PIN_LABLE_IP	V10

#define BLYNK_PIN_SLIDER1	V11
#define BLYNK_PIN_SLIDER2	V12
#define BLYNK_PIN_SLIDER3	V13
#define BLYNK_PIN_SLIDER4	V14
#define BLYNK_PIN_SLIDER5	V15
#define BLYNK_PIN_SLIDER6	V16
#define BLYNK_PIN_SLIDER7	V17
#define BLYNK_PIN_SLIDER8	V18

WidgetTerminal terminal(BLYNK_PIN_TERMINAL);

BLYNK_WRITE(BLYNK_PIN_TERMINAL)
{
	// if you type "Marco" into Terminal Widget - it will respond: "Polo:"
	if (String("/help") == param.asStr())
	{
		terminal.println(F("/rs\tRestart your device"));
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
		terminal.println(F("Your device is being restarted...\r\n"));
		terminal.flush();
		delay(500);
		ESP.restart();
		delay(5000);
	}
	else if (String(param.asStr()).indexOf("/na") > -1)
	{
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
		terminal.println(_version);
	}
	else if (String("/lf") == param.asStr())
	{
		String lf = Firebase.getString(F("LastestFirmware/Version"));
		terminal.println(lf);
	}
	else if (String("/ip") == param.asStr())
	{
		terminal.println(WiFi.localIP());
		Blynk.virtualWrite(BLYNK_PIN_LABLE_IP, WiFi.localIP().toString());
	}
	else if (String("/cl") == param.asStr())
	{
		terminal.println(F("\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n"));
	}
	else if (String("/factoryreset") == param.asStr())
	{
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
BLYNK_READ(BLYNK_PIN_LABLE_IP)
{
	Blynk.virtualWrite(BLYNK_PIN_LABLE_IP, WiFi.localIP().toString());
}

BLYNK_WRITE(BLYNK_PIN_BUTTON1)
{
	BlynkWrite_ButtonHelper(BLYNK_PIN_BUTTON1, param.asInt());
}
BLYNK_WRITE(BLYNK_PIN_SLIDER1)
{
	BlynkWrite_SliderHelper(BLYNK_PIN_SLIDER1, param.asInt());
}

BLYNK_WRITE(BLYNK_PIN_BUTTON2)
{
	BlynkWrite_ButtonHelper(BLYNK_PIN_BUTTON2, param.asInt());
}
BLYNK_WRITE(BLYNK_PIN_SLIDER2)
{
	BlynkWrite_SliderHelper(BLYNK_PIN_SLIDER2, param.asInt());
}

BLYNK_WRITE(BLYNK_PIN_BUTTON3)
{
	BlynkWrite_ButtonHelper(BLYNK_PIN_BUTTON3, param.asInt());
}
BLYNK_WRITE(BLYNK_PIN_SLIDER3)
{
	BlynkWrite_SliderHelper(BLYNK_PIN_SLIDER3, param.asInt());
}

BLYNK_WRITE(BLYNK_PIN_BUTTON4)
{
	BlynkWrite_ButtonHelper(BLYNK_PIN_BUTTON4, param.asInt());
}
BLYNK_WRITE(BLYNK_PIN_SLIDER4)
{
	BlynkWrite_SliderHelper(BLYNK_PIN_SLIDER4, param.asInt());
}

BLYNK_WRITE(BLYNK_PIN_BUTTON5)
{
	BlynkWrite_ButtonHelper(BLYNK_PIN_BUTTON5, param.asInt());
}
BLYNK_WRITE(BLYNK_PIN_SLIDER5)
{
	BlynkWrite_SliderHelper(BLYNK_PIN_SLIDER5, param.asInt());
}

BLYNK_WRITE(BLYNK_PIN_BUTTON6)
{
	BlynkWrite_ButtonHelper(BLYNK_PIN_BUTTON6, param.asInt());
}
BLYNK_WRITE(BLYNK_PIN_SLIDER6)
{
	BlynkWrite_SliderHelper(BLYNK_PIN_SLIDER6, param.asInt());
}

BLYNK_WRITE(BLYNK_PIN_BUTTON7)
{
	BlynkWrite_ButtonHelper(BLYNK_PIN_BUTTON7, param.asInt());
}
BLYNK_WRITE(BLYNK_PIN_SLIDER7)
{
	BlynkWrite_SliderHelper(BLYNK_PIN_SLIDER7, param.asInt());
}

BLYNK_WRITE(BLYNK_PIN_BUTTON8)
{
	BlynkWrite_ButtonHelper(BLYNK_PIN_BUTTON8, param.asInt());
}
BLYNK_WRITE(BLYNK_PIN_SLIDER8)
{
	BlynkWrite_SliderHelper(BLYNK_PIN_SLIDER8, param.asInt());
}
//==========================================================

int Button_to_Slider(int button) {
	if ((button >= 0) && (button <= 8)) {
		return (button + 10);
	}
	return -1;
}
int Slider_to_Button(int slider) {
	if ((slider >= 10) && (slider <= 18)) {
		return (slider - 10);
	}
	return -1;
}
void BlynkWrite_ButtonHelper(int button, int param_asInt) {
	if ((param_asInt == 0) || (param_asInt = 1)) {
		Blynk.virtualWrite(Button_to_Slider(button), param_asInt ? 1023 : 0);
		//delay(10);
		pinMode(button, OUTPUT);
		digitalWrite(button, param_asInt);
#ifdef DEBUG
		DEBUG.print("BLYNK_PIN_BUTTON " + String(button) + " value: ");
		DEBUG.println(param_asInt);
#endif // DEBUG
	}
}
void BlynkWrite_SliderHelper(int slider, int param_asInt) {
	pinMode(slider, OUTPUT);
	analogWrite(slider, param_asInt);
	Blynk.virtualWrite(Slider_to_Button(slider), bool(param_asInt));
#ifdef DEBUG
	DEBUG.print("BLYNK_PIN_SLIDER " + String(slider) + "  value: ");
	DEBUG.println(param_asInt);
#endif // DEBUG
}
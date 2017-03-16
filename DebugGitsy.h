// Debug.h

#ifndef _DEBUG_h
#define _DEBUG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define RUN_MAIN
#define DEBUG Serial

#define DEBUG_EEPROM DEBUG
#define DEBUG_FIREBASE DEBUG
#define DEBUG_BLYNK DEBUG
#define DEBUG_WIFI_HELPER DEBUG


//#define TEST_EEPROM
//#define TEST_FIREBASE
//#define TEST_BLYNK
//#define TEST_WIFI_HELPER

#if defined(TEST_EEPROM) || defined(TEST_FIREBASE) || defined(TEST_BLYNK) || defined(TEST_WIFI_HELPER)
#undef RUN_MAIN
#endif


#endif


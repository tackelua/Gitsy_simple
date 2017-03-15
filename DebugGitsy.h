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

//#define TEST_EEPROM
#define TEST_FIREBASE
//#define TEST_BLYNK

#if defined(TEST_EEPROM) || defined(TEST_FIREBASE) || defined(TEST_BLYNK)
#undef RUN_MAIN
#endif


#endif


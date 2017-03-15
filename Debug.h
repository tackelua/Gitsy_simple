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

#if defined(TEST_EEPROM)
#undef RUN_MAIN
#endif


#endif


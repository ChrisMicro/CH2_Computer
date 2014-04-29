/*
 * platform.h
 *
 *  Created on: 30.11.2013
 *      Author: christoph
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

	//#define PC_PLATFORM     // GMC4 simulation on Pc
    #define ARDUINO_PLATFORM // Arduino Uno
	#define CH2_PLATFORM     // Arduino Uno compatible, but internal 8Mhz oscillator
	#define CH2_SPEAKERPIN 9

    #include <stdio.h>
	#include <stdint.h>

	#ifdef PC_PLATFORM

		#define STSIZE 0x10000

	#endif

	#ifdef ARDUINO_PLATFORM
		#include "keyboard.h"
		void systemOut(char * str);
		void SystemOutHex(char * str,uint16_t n);
	#endif

	/***************************************************************************************
	  Function Prototypes
	***************************************************************************************/


#endif /* PLATFORM_H_ */

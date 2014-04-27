#include "Arduino.h"
#include <util/delay.h>
#include "pitches.h"
#include "display.h"
#include "keyboard.h"

/**
*
* @file CH2_Keyboard.ino
*
* @brief keyboard test
*
* @author ChrisMicro
* @copyright (c) 2014 ChrisMicro
*
*/

uint16_t frequencyTable[]={
   NOTE_A4 ,
   NOTE_B4 ,
   NOTE_C5 ,
   NOTE_D5 ,
   NOTE_E5 ,
   NOTE_F5 ,
   NOTE_G5 ,
   NOTE_A5 ,
   NOTE_B5 ,
   NOTE_C6 ,
   NOTE_D6 ,
   NOTE_E6 ,
   NOTE_F6 ,
   NOTE_G6 ,
   NOTE_A6 ,
   NOTE_B6
};
void setup()
{
	  initDisplay();
	  pinMode(5, OUTPUT);      // sets the digital pin as output
}

#define CH2_SPEAKERPIN 9

void loop() {

	static int8_t value=0;
	uint8_t n;

	// blink LED
	for(n=0;n<3;n++)
	{
		ledOn();
		delay(200);
		ledOff();
		delay(200);
	}

	// show helo
	_putchar('H');	showMatrix(200);
	_putchar('E');	showMatrix(200);
	_putchar('L');	showMatrix(200);
	_putchar('O');	showMatrix(500);


	//**************** key display example ***************************
	do
	{
		n=_getchar();
		value=getKey();
		_putchar(n);
		showLeds(value);
	}
	while(value!=0);

	//**************** key sound display example ***************************
	tone(CH2_SPEAKERPIN, frequencyTable[0],50);
	do
	{
		n=_getchar();
		value=getKey();
		tone(CH2_SPEAKERPIN, frequencyTable[value],50);
		delay(50);
		_putchar(n);
		showLeds(value);
	}
	while(value!=0);
}

/*
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
*/

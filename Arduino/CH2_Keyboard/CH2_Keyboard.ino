//#include "Arduino.h"
#include <util/delay.h>
/**
*
* @file CH2_Keyboard.ino
*
* @brief keyboard test
*
* @author ChrisMicro
* @copyright (c) 2014 ChrisMicro
*
* The CH2-Computer can be used as a shield for Ardduinos with an Atmega168 or Atmega328
* microcontroller ( mainly Arduino Uno ).
*

    CH2_Computer, Hardware Version v0.2

    5x7 matrix pin out

    There are 5 rows ( Cathodes, active low )
    cathode,port pin
    C0:     PD7
    C1:     PD6
    C2:     PD5
    C3:     PD4
    C4:     PD3

    There are 7 columns ( Anodes, active high )
    The columns are the anodes

    A0:     PB0
    A1:     PB2
    A2:     PB3
    A3:     PB4
    A4:     PB5
    A5:     PC3
    A6:     PD2

row  ^
    4|
    3|
    2|
    1|
    0+ - - - - - - >
     6 5 4 3 2 1 0 column

*/
void initDisplay()
{
  // set row lines as output
  DDRD|=(1<<7)|(1<<6)|(1<<5)|(1<<4)|(1<<3);
  // set col lines as output
  DDRB|=(1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<0);
  DDRD|=(1<<2);
  DDRC|=(1<<3);
}

void setup() {
  initDisplay();
  pinMode(5, OUTPUT);      // sets the digital pin as output
}
/**
* @brief Set one column line of the 5x7 matrix active
*
* @param uint8_t col: 0..6
*
* example:
* setCol(2) turns the second column line ON
* to light one pixel there has to be also a active row
* e.g. with setRow(0).
*/
// col 0..6 , anodes
void setCol(uint8_t col)
{
  // the columns are the anodes of the 5x7 matrix
  if(col==6)PORTD|=(1<<2);
  else PORTD&=~(1<<2);

  if(col==5)
  {
    PORTC|=(1<<3);
    //DDRC|=(1<<3);
  }
  else PORTC&=~(1<<3);

  if(col==4)PORTB|=(1<<5);
  else PORTB&=~(1<<5);

  if(col==3)PORTB|=(1<<4);
  else PORTB&=~(1<<4);

  if(col==2)PORTB|=(1<<3);
  else PORTB&=~(1<<3);

  if(col==1)PORTB|=(1<<2);
  else PORTB&=~(1<<2);

  if(col==0)PORTB|=(1<<0);
  else PORTB&=~(1<<0);
}

/**
* @brief Set one row line of the 5x7 matrix active
*
* @param uint8_t col: 0..4
*
*/
// row 0..4, cathodes
void setRow(uint8_t row)
{
  uint8_t n;

  // the rows are cathodes of the matrix and therefore active low
  PORTD|=(1<<7)|(1<<6)|(1<<5)|(1<<4)|(1<<3); // clear all rows
  // resetting the line will drive the LED
  PORTD&=~(1<<(3+row));
}

/**
* @brief Set multiple row lines, used to switch on multiple LEds
*
* @param uint8_t col: bits to be set, range: b00000..b11111
*
*/
void setRowPattern(uint8_t bitPattern)
{
  uint8_t n;
  for(n=0;n<5;n++)
  {
    if((bitPattern&(1<<n))!=0)PORTD&=~(1<<(3+n));
    else PORTD|=(1<<(3+n));
  }
}

void ledOn(){
  DDRC|=1; // set port to output
  PORTC|=1; // set pin high
}
void ledOff(){
  PORTC&=~1; // set pin low
}

#include "keyboard.h"
#include "pitches.h"

#define CH2_SPEAKERPIN 9

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
void loop() {

	static int8_t value=0;
	uint8_t n;

	ledOff();

	if(keyPressed())
	{
		value=getKey();
		if(value!=-1)
		{
			tone(CH2_SPEAKERPIN, frequencyTable[value],50);
			delay(50);
		}
		if(value==0)ledOn();

	}

	// display binary value
	for(n=0;n<4;n++)
	{
		initDisplay();
		setCol(n);
		setRowPattern(value);

		delay(1);
	}

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


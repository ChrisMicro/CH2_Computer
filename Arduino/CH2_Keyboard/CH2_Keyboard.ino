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

    '1','2','3',
    '4','5','6',
    '7','8','9',
    '*','0','#'

    keyboard pin layout for mulicomp keypad ( used in v0.1 )

    key line driver active high PD3, PD4, PD5, PD6
    key line inputs PB0, PB2, PB3,



    keyboard layout for S512J-BF7KUV ( conrad )



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

/*
    keyboard pin layout for mulicomp keypad ( used in v0.1 )

	keys 1   ,2    ,3   : PD3, row 0
	Keys 4   ,5    ,6   : PD4, row 1
	keys 7   ,8    ,9   : PD5, row 2
	keys *   ,0    ,#   : PD6, row 3
         PB3  PB2  PB0

	keyboard pin connection
	pin1: PB2
	pin2: PD3
	pin3: PB3
	pin4: PD6
	pin5: PB0
	pin6: PD5
	pin7: PD4

 */

// row 0..3
void setKeyRow(uint8_t row)
{
  uint8_t n;
  if(row<4)
  {
	  // display lines
	  DDRC|=(1<<3); // set line as output
	  PORTC&=~(1<<3); // discharge
	  DDRD|=(1<<2); // set line as output
	  PORTD&=~(1<<2); // discharge
	  DDRB|=((1<<4)|(1<<5)); // set line as output
	  PORTB&=~((1<<4)|(1<<5)); // discharge

	  // key lines
	  PORTB&=~((1<<0)|(1<<2)|(1<<3)); // discharge
	  DDRB=((1<<0)|(1<<2)|(1<<3)); // set all key lines as output

	  PORTD&=~((1<<3)|(1<<4)|(1<<5)|(1<<6)); // discharge and make sure pull ups are turned off
	  DDRD=((1<<3)|(1<<4)|(1<<5)|(1<<6)); // set all selector lines as output

	  DDRD&=~((1<<3)|(1<<4)|(1<<5)|(1<<6)); // set all selector lines to input
	  DDRB&=~((1<<0)|(1<<2)|(1<<3)); // set all key lines as input

	  // display lines
	  DDRC&=~(1<<3); // line as input
	  DDRD&=~(1<<2); // line as input
	  DDRB&=~((1<<4)|(1<<5)); // set line as input

	  // key row selection
	  DDRD|=(1<<(3+row)); // set the row key line to output
	  PORTD|=(1<<(3+row)); // set row key pin to high
  }
}
void ledOn(){
  DDRC|=1; // set port to output
  PORTC|=1; // set pin high
}
void ledOff(){
  PORTC&=~1; // set pin low
}

#define KEYSCANDELAY 1
uint8_t getKeyColumnPattern()
{
  uint8_t result=0;

  PORTB&=~((1<<3)|(1<<2)); // set not used multiplexer lines to 0
  DDRB|=((1<<3)|(1<<2)); // set multplexer lines as outputs
  DDRB&=~(1<<0); // set the selected line as input
  _delay_us(KEYSCANDELAY);
  if(PINB&(1<<0)) result|=(1<<0) ;

  PORTB&=~((1<<3)|(1<<0)); // set not used multiplexer lines to 0
  DDRB|=((1<<3)|(1<<0)); // set multplexer lines as outputs
  DDRB&=~(1<<2); // set the selected line as input
  _delay_us(KEYSCANDELAY);
  if(PINB&(1<<2)) result|=(1<<1) ;

  PORTB&=~((1<<2)|(1<<0)); // set not used multiplexer lines to 0
  DDRB|=((1<<2)|(1<<0)); // set multplexer lines as outputs
  DDRB&=~(1<<3); // set the selected line as input
  _delay_us(KEYSCANDELAY);
  if(PINB&(1<<3)) result|=(1<<2) ;

  return result;
}
// return the number of the key pressed
uint8_t scanKey()
{
	uint8_t n,value,result=0,tmp;
	n=4;

	do
	{
		n--;
		setKeyRow(n);
		value=getKeyColumnPattern();
		if(value>0) result=3;
		if(value>1) result=2;
		if(value>2) result=1;

		if(result>0)break;

	}while(n>0);
	return result+n*3;
}

void loop() {
  uint8_t n,value;
  ledOn();
// scan the keyboard and show the key as pixel
// on the matrix display
  for(n=0;n<4;n++)
  {
	setKeyRow(n);

	value=getKeyColumnPattern();
	if(value!=0)ledOff();
	initDisplay();
	setCol(n);
	setRowPattern(value);
	delay(1);
  }

/*
  // show the binary value of the key pressed
  while(1)
  {
	value=scanKey();
	initDisplay();
	setCol(0);
	setRowPattern(value);
	delay(1);
  }
 */
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


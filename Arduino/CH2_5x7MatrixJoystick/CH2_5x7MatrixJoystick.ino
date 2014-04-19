#include "Arduino.h"

/**
*
* @file CH2_5x7MatrixJoystic.ino
*
* @brief Drive the row and colun lines of the 5x7 matrix display of the CH2-computer
*        by values of the joystick
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


    Joystick
    ========
    axis,   port, description
    x-axis: PC1,  analog input 1 ( arduino name A1 )
    y-axis: PC2,  analog input 2 ( arduino name A2 )

         ^ 5V
         |
    0v------->5V
         |
         0V

*/

void setup() {
  // set row lines as output
  DDRD|=(1<<7)|(1<<6)|(1<<5)|(1<<4)|(1<<3);
  // set col lines as output
  DDRB|=(1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<0);
  DDRD|=(1<<2);
  DDRC|=(1<<3);
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

void loop() {
  const int xAxis = A1;
  const int yAxis = A2;

  uint32_t x,y;
  // read the analog in value:
  delay(10); // settling time for adc
  x = 1023-analogRead(xAxis); // x axis of joystick is inverted
  delay(10); // settling time for adc
  y = analogRead(yAxis);
  uint8_t row,col;
  setCol(6-(x*7/1024));
  setRow(y*5/1024);
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


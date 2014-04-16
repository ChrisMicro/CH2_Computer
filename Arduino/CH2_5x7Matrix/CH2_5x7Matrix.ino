
/**
*
* @file CH2_5x7Matrix.ino
*
* @brief Drive the row and colun lines of the 5x7 matrix display of the CH2-computer
*
* @author ChrisMicro
* @copyright (c) 2014 ChrisMicro
*
* The CH2-Computer can be used as a shield for Ardduinos with an Atmega168 or Atmega328
* microcontroller ( mainly Arduino Uno ).
*  
*/

void setup() {                
  // set row lines as output
  DDRD|=(1<<7)|(1<<6)|(1<<5)|(1<<4)|(1<<3);
  // set col lines as output
  DDRD|=(1<<2);
  DDRC|=(1<<5);
  DDRB|=(1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<0);
  
}

// col 0..7
void setCol(uint8_t col)
{
  // the columns are the anodes of the 5x7 matrix
  if(col==6)PORTD|=(1<<2);
  else PORTD&=~(1<<2);

  if(col==5)
  {
    PORTC|=(1<<5);
    DDRC|=(1<<5);
  }
  else PORTC&=~(1<<5);

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

void setRow(uint8_t row)
{
  uint8_t n;
  // the rows are cathodes of the matrix
  for(n=0;n<5;n++){PORTD|=(1<<(3+n));} // clear all rows
  // resetting the line will drive the LED
  PORTD&=~(1<<(3+row));
}

void loop() {
  uint8_t row,col;
  for(row=0;row<5;row++)
  {
    for(col=0;col<7;col++)  
    {
      setCol(col);
      setRow(row);
      delay(100);
    }
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

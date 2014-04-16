
/**
*
* @file CH2_Blink.ino
*
* @brief Turns on an LED on for one second, then off for one second, repeatedly.
*
* @author ChrisMicro
* @copyright (c) 2014 ChrisMicro
*
* The CH2-Computer can be used as a shield for Ardduinos with an Atmega168 or Atmega328
* microcontroller ( mainly Arduino Uno ).
*  
*/

void setup() {                
   
}

void ledOn(){
  DDRC|=1;  // set port to output
  PORTC|=1; // set pin high
}
void ledOff(){
  PORTC&=~1; // set pin low
}

void loop() {
  ledOn();
  delay(1000);              // wait for a second
  ledOff();
  delay(1000);              // wait for a second
}

/
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


/**
*
* @file CH2_LightSensorx.ino
*
* @brief use the led as light sensor
*
* @author ChrisMicro
* @copyright (c) 2014 ChrisMicro
*
* The CH2-Computer can be used as a shield for Ardduinos with an Atmega168 or Atmega328
* microcontroller ( mainly Arduino Uno ).
*
*/

const int lightSensor = A0;   

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {
  int x,y;
  DDRC|=(1<<0); // set led to output
  PORTC=~(1<<0); // discharge LED
  DDRC=~(1<<0); // led input to ADC
  // read the analog in value:
  delay(1);  // charging time
  x = analogRead(lightSensor);  // x axis is inverted

 
  // print the results to the serial monitor:
  Serial.print("light = " );                       
  Serial.println(x);      

  delay(400);                     
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

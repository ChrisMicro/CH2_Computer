/*
  Read Analog X and Y inputs and write the values to the serial port.
  
  X-Axis: analog pin 2
  Y-Axis: analog pin 3
  
  Note: The pin configuration for the version 2 of the CH2 computer will change.
 
 */

const int xAxis = A3;  
const int yAxis = A4;  

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {
  int x,y;
  // read the analog in value:
  delay(10);  // settling time for adc
  x = 1023-analogRead(xAxis);  // x axis is inverted
  delay(10);  // settling time for adc
  y = analogRead(yAxis); 
 
  // print the results to the serial monitor:
  Serial.print("x = " );                       
  Serial.print(x);      
  Serial.print("  y = " );                       
  Serial.println(y);  
  
  // wait 10 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(100);                     
}

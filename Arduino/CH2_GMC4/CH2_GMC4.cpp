/**
*
* @file CH2_GMC4
*
* @brief 4 bit microcontroller emulation on the CH2-Computer
*
* @author ChrisMicro
* @copyright (c) 2014 ChrisMicro
*
* The CH2-Computer can be used as a shield for Ardduinos with an Atmega168 or Atmega328
* microcontroller ( mainly Arduino Uno ).
*
*/
#include "Arduino.h"

#include "systemout.h"
#include "display.h"
#include "keyboard.h"
#include "gmc4Vm.h"
#include "demo.h"

void setup() {

  //Serial.begin(9600);
  Serial.begin(19200);
  Serial.println("gmc4 emulator ready");
  startup();
}

extern "C"
{

  void arduinoSound(uint16_t frequency, uint16_t duration)
  {
/*
    uint16_t n;
    uint16_t d;
    d=1.0/(frequency)*1e6/2/2-35;
    cli();
    for(n=0;n<((float)frequency/2*duration/1000);n++)
    {
      //digitalWrite(9, HIGH);   // set the LED on
      PORTB|=(1<<1);
      delayMicroseconds(d);
      //digitalWrite(9, LOW);    // set the LED off
      PORTB&=~(1<<1);
      delayMicroseconds(d);
    }
    sei();*/
	#ifdef CH2_PLATFORM
		tone(CH2_SPEAKERPIN, frequency,duration);
		delay(duration+50);
	#else
		tone(CH_SPEAKERPIN, frequency,duration);
		delay(duration);
	#endif
  }
  void systemOut(char * str)
  {
    Serial.println(str);
  }
  void SystemOutHex(char * str,uint16_t n)
  {
    Serial.print(str);
    Serial.print(" ");
    Serial.println(n,HEX);

  }
}

uint8_t testProg[]={0,0XF,0,0,1,0XF,0,0};
// random number music generator
uint8_t Program7[]={0xB,1,6,4,0xE,0xB,0xF,0,0};
// electronic dice
uint8_t Program2[]={0xA,1,3,1,3,0xB,1,0xD,7,0xF,0,0xE,0xA,1,0,0xF,0,2,0xF,0,0xE};


/**************************************************************************

    uint8_t isDigitOfBase(char *chr, uint8_t base)

     check if the char is digit of the given base
     base 10 : 0..9
     base 16 : 0..9 a..f A..F

     return
      true: char is a hex digit
      false: not

*************************************************************************/
uint8_t Base=16;
// tbd: only base 10 or 16 allowed at the moment
uint8_t isDigitOfBase(char chr)
{
    uint8_t flag=false;

    if(Base==16)
    {
        if((chr>='a')&&(chr<='f'))flag=true;
        if((chr>='A')&&(chr<='F'))flag=true;
    }
    if((chr>='0')&&(chr<='9'))flag=true;

    return flag;
}
#define ARDUINO
void loop() {
#ifdef ARDUINO


#endif
  uint8_t inp;

  uint8_t number=0,oldNumber=0;
  Cpu_t cpu;

  simulatorReset(&cpu);
  //memcpy(&cpu.M,testProg,sizeof(testProg));
  memcpy(&cpu.M,testProg,sizeof(testProg));

  //tone(CH_SPEAKERPIN, 440,100);
  //SYSTEMOUTCHAR('C');
  //showMatrix(1000);

  number=cpu.M[cpu.Pc];
  do
  {
      inp=_getchar();
      //SOUND(2000,30); // gakken key input sound 3kHz,30ms
#ifdef ARDUINO
      Serial.print("key:");
      Serial.print((char)inp);
      Serial.print("  ");
#endif
      switch(inp)
      {
          // increment
          case 'i':{
              cpu.M[cpu.Pc]=number;
              cpu.Pc++;
              cpu.Pc&=0b00111111;
#ifdef ARDUINO
              Serial.print(cpu.Pc,HEX);Serial.print(" ");
              Serial.print(cpu.M[cpu.Pc],HEX);Serial.println(" ");

#else
              printf("%02x: ",);
              printf("%x  ",cpu.M[cpu.Pc]);
#endif
              hex1(cpu.M[cpu.Pc]);
              showLeds(cpu.Pc);
              number=cpu.M[cpu.Pc];
          }break;
          // reset
          case 'r':{
              //simulatorReset(&cpu);
              //memcpy(&cpu.M,Program7,sizeof(Program7));
              cpu.Pc=0;
              number=cpu.M[cpu.Pc];
#ifdef ARDUINO
              Serial.println("reset");
              Serial.print(cpu.Pc,HEX);Serial.print(" ");
              Serial.print(cpu.M[cpu.Pc],HEX);Serial.println(" ");

#else
              printf("reset\n");
              printf("%02x: ",cpu.Pc);
              printf("%x  ",cpu.M[cpu.Pc]);
#endif
              hex1(cpu.M[cpu.Pc]);
              showLeds(cpu.Pc);
              //number=cpu.M[cpu.Pc];

          }break;
          // run ( go )
          case 'g':{
            cpu.Pc=0; // reset program counter
            if(number==9)ElectronicOrgan_GMC4Prog9();
            if(number==0xA)PlayNotes_GMC4ProgA(&cpu);
            else
            {
              if(number==2)memcpy(&cpu.M,Program2,sizeof(Program2));
              if(number==7)memcpy(&cpu.M,Program7,sizeof(Program7));

  #ifdef ARDUINO
                Serial.println("run");
  #else
                printf("runt\n");
  #endif
                //SYSTEMOUTHEX("adr",cpu.Pc);
                do
                {
                  do
                  {
                    executeVm(&cpu);
                    showCpu(&cpu);
                    if(cpu.Pc>0x6F)break;
                  }while(!keyPressed());
                }while(getKey()!=HASHKEY);
  #ifdef ARDUINO
                Serial.println("stop");
  #else
                printf("stopt\n");
  #endif
            }
          }break;
          // aset ( set address )
          case 's':{
              cpu.Pc=(oldNumber<<4)+number;
              //printf("%02x: ",cpu.Pc);
              //printf("%x  ",cpu.M[cpu.Pc]);
          }break;
          default:
          {
              if(isDigitOfBase(inp))
              {
                oldNumber=number;
                if(inp>='a')number=inp-'a'+10;
                else if (inp>='A')number=inp-'A'+10;
                else number=inp-'0';
                hex1(number);
              }

          }break;
      }
  }while((inp!='x'));

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


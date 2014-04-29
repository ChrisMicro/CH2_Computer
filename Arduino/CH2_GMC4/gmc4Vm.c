/**
*
* @file gmc4Vm.c
*
* @brief virtual machine of the gmc4 microcontroller
*
* @author ChrisMicro
* @copyright (c) 2014 ChrisMicro
*
* This virtual machine emulates the function of the 4 bit microcontroller gmc4
*
*/

#include <stdint.h>
#include <stdio.h>
#include "gmc4Vm.h"
#include "systemout.h"
#include "sound.h"
#include "display.h"


void simulatorReset(Cpu_t *cpu)
{
	uint8_t n;
	for(n=0;n<M_SIZE;n++)cpu->M[n]=0xF; // memory reset value is 0xF
	cpu->Pc=0;
	cpu->flag=0;
	cpu->leds=0;
	SOUND(0,100);
}
/***************************************************************/
uint8_t isKeyPressed(void)
{
	return true;
}
/*
uint8_t getKey(void){
	return getchar();
}*/
void show7Segment(uint8_t value)
{
	//putchar(value+'0');
	SYSTEMOUTCHAR(value+'0');
}

void showCpu(Cpu_t *cpu)
{
	/*
	printf("%02x: ",cpu->Pc);
	printf("%x  ",cpu->M[cpu->Pc]);
	printf("f:%d ",cpu->flag);
	printf("A:%x ",cpu->M[AR]);
	printf("B:%x ",cpu->M[BR]);
	printf("Y:%x ",cpu->M[YR]);
	printf("Z:%x ",cpu->M[ZR]);
*/
}
#define DISASM(str) SYSTEMOUT(str)

/***************************************************************/

void executeVm(Cpu_t *cpu)
{
	uint8_t temp;
	uint8_t command;
	//SYSTEMOUTHEX("adr",cpu->Pc);
	//SYSTEMOUTHEX("flag",cpu->flag);
	command=cpu->M[cpu->Pc];
	cpu->Pc++;
	switch(command)
	{
		// KA 	K->Ar 	 0, 1 	The pressed key from the hex keypad is saved to the A register.
		// If a key is not pressed, the Flag is set to 1, otherwise it is 0.
		case KA:{
		  DISASM("KA   ");
		  if(KEYHIT())
          {
            cpu->M[AR]=GETKEY();
            cpu->flag=0;
            SYSTEMOUTHEX("Key:",cpu->M[AR]);
          }else {
            SYSTEMOUT("nokey");
            cpu->flag=1;
          }

            showMatrix(20);


		}break;
		// AO 	Ar->Op 		1 	The 7-segment readout displays the value currently contained in the A register.
		case AO:{
			DISASM("AO   ");
			show7Segment(cpu->M[AR]);
			 //PRINT7SEGMENT(x);
			cpu->flag=1;
		}break;
		// CH 	Ar<=>Br
        // Yr<=>Zr 	1 	Exchange the contents of the A and B registers, and the Y and Z registers.
		case CH:{
			DISASM("CH   ");

			temp=cpu->M[AR];
			cpu->M[AR]=cpu->M[BR];
			cpu->M[BR]=temp;
			temp=cpu->M[YR];
			cpu->M[YR]=cpu->M[ZR];
			cpu->M[ZR]=temp;
			cpu->flag=1;
		}break;
		// CY 	Ar<=>Yr 	1 	Exchange the contents of the A and Y registers.
		case CY:{
			DISASM("CY   ");

			temp=cpu->M[AR];
			cpu->M[AR]=cpu->M[YR];
			cpu->M[YR]=temp;
			cpu->flag=1;
		}break;
		// AM 	Ar->M 		1 	Write the contents of the A register to data memory (memory address is 50 + Y register).
		case AM:{
			DISASM("AM   ");

			cpu->M[((cpu->M[YR])&0xF)+M_OFFSET]=cpu->M[AR];
			cpu->flag=1;
		}break;
		// MA 	M->Ar 		1 	Write the contents of data memory (50 + Y register) to the A register.
		case MA:{
			DISASM("MA   ");

			cpu->M[AR]=cpu->M[((cpu->M[YR])&0xF)+M_OFFSET];
			cpu->flag=1;
		}break;
		// M+ 	M+Ar->Ar 	0, 1 	Add the contents of data memory (50 + Y register) to the A register. If there is overflow, the Flag is set to 1, otherwise 0.
		case MPLUS:{
			DISASM("M+   ");

			cpu->M[AR]+=cpu->M[((cpu->M[YR])&0xF)+M_OFFSET];
			if(((cpu->M[AR])&0x10)!=0)cpu->flag=1;
			else cpu->flag=0;
			cpu->M[AR]&=0x0F;
		}break;
		// M- 	M-Ar->Ar 	0, 1 	Subtract the contents of data memory (50 + Y register) from the A register. If the result is negative, the Flag is set to 1, otherwise 0.
		case MMINUS:{
			DISASM("M-   ");

			cpu->M[AR]-=cpu->M[((cpu->M[YR])&0xF)+M_OFFSET];
			if(((cpu->M[AR])&0x10)!=0)cpu->flag=1;
			else cpu->flag=0;
			cpu->M[AR]&=0x0F;
		}break;
		// TIA [ ] 	[ ] -> Ar 	1 	Transfer immediate to the A register.
		case TIA:{
			DISASM("TIA  ");

			cpu->M[AR]=cpu->M[cpu->Pc];
			cpu->Pc++;
			cpu->flag=1;
		}break;
		// AIA [ ] 	Ar + [ ] -> Ar 	0, 1 	Add immediate to the A register. If there is overflow, the Flag is set to 1, otherwise 0.
		case AIA:{
			DISASM("AIA  ");

			cpu->M[AR]+=cpu->M[cpu->Pc];
			if(((cpu->M[AR])&0x10)!=0)cpu->flag=1;
			else cpu->flag=0;
			cpu->M[AR]&=0x0F;
			cpu->Pc++;
		}break;
		// TIY [ ] 	[ ] -> Yr 	1 	Transfer immediate to the Y register.
		case TIY:{
			DISASM("TIA  ");

			cpu->M[YR]=cpu->M[cpu->Pc];
			cpu->Pc++;
			cpu->flag=1;
		}break;
		// AIY [ ] 	Yr + [ ] -> Yr 	0, 1 	Add immediate to the Y register. If there is overflow, the Flag is set to 1, otherwise 0.
		case AIY:{
			DISASM("AIY  ");

			cpu->M[YR]+=cpu->M[cpu->Pc];
			if(((cpu->M[YR])&0x10)!=0)cpu->flag=1;
			else cpu->flag=0;
			cpu->M[YR]&=0x0F;
			cpu->Pc++;
		}break;
		// CIA [ ] 	Ar != [ ] ? 	0, 1 	Compare immediate to the A register. If equal, Flag reset to 0, otherwise set to 1.
		case CIA:{
			DISASM("CIA  ");

			if(cpu->M[AR]!=cpu->M[cpu->Pc])cpu->flag=0;
			else cpu->flag=1;
			cpu->Pc++;
		}break;
		// CIY [ ] 	Yr != [ ] ? 	0, 1 	Compare immediate to the Y register. If equal, Flag reset to 0, otherwise set to 1.
		case CIY:{
			DISASM("CIY  ");

			if(cpu->M[YR]!=cpu->M[cpu->Pc])cpu->flag=0;
			else cpu->flag=1;
			cpu->Pc++;
		}break;
		//JUMP [ ] [ ] 		1 	Jump to the immediate address if the Flag is 1, otherwise just increment the program counter.
		//The Flag is then set to 1. Note that this is an absolute address. That is, JUMP [0] [2] will change the address pointer to hex address 0x02.
		//You can jump both forward and backward in program space.
		case JUMP:{
			DISASM("JUMP ");

			if((cpu->flag)==1)
			{
				temp=cpu->M[cpu->Pc]<<4;
				cpu->Pc++;
				temp+=cpu->M[cpu->Pc]<<4;
				cpu->Pc=temp;
			}else{
				cpu->Pc++;
				cpu->flag=1;
			}
		}break;
		//      --- 	--- 	--- 	Extended code. See table below.
		case EXTENDED:{
			command=(cpu->M[cpu->Pc])|0xE0;
			SYSTEMOUTHEX("com:",command);
			cpu->Pc++;
			if(cpu->flag==1)switch(command)
			{
				case CAL_RSTO:{
					DISASM("CAL_RSTO  ");
					SYSTEMOUTCHAR(' ');
					//SYSTEMOUT("clear 7 seg");
				}break;
				case CAL_SETR:{
					DISASM("CAL_SETR  ");
					cpu->leds|=(1<<(cpu->M[YR]));
					SHOWLEDS(cpu->leds);
					//SYSTEMOUT("led on");
				}break;
				case CAL_RSTR:{
					DISASM("CAL_RSTR  ");
                    cpu->leds&=~(1<<(cpu->M[YR]));
                    SHOWLEDS(cpu->leds);
					//SYSTEMOUT("led off");
				}break;
				// 0xE4 // 	CAL CMPL 	1 	Complement the A register (1 <=> 0).
				case CAL_CMPL:{
					DISASM("CAL_CMPL  ");

					cpu->M[AR]=(~cpu->M[AR])&0x0F;
					cpu->flag=1;
				}break;
				//0xE5 // 	CAL CHNG 	1 	Swap the A/B/Y/Z registers with A'/B'/Y'/Z'
				case CAL_CHNG:{
					DISASM("CAL_CHNG  ");

					temp=cpu->M[AR];
					cpu->M[AR]=cpu->M[AR_];
					cpu->M[AR_]=temp;

					temp=cpu->M[BR];
					cpu->M[BR]=cpu->M[BR_];
					cpu->M[BR_]=temp;

					temp=cpu->M[YR];
					cpu->M[YR]=cpu->M[YR_];
					cpu->M[YR_]=temp;

					temp=cpu->M[ZR];
					cpu->M[ZR]=cpu->M[ZR_];
					cpu->M[ZR_]=temp;

					cpu->flag=1;

				}break;
				// 0xE6 //	CAL SIFT 	0, 1 	Shift the A register right 1 bit. If the starting value is even (bit 0 = 0), set the Flag to 1, otherwise 0.
				case CAL_SIFT:{
					DISASM("CAL_SIFT  ");

					if((cpu->M[AR])&1)cpu->flag=1;
					else cpu->flag=0;
					cpu->M[AR]=(~cpu->M[AR])>>1;
				}break;
				//0xE7 //	CAL ENDS 	1 	Play the End sound.
				case CAL_ENDS:{
					DISASM("CAL_ENDS  ");
					SOUND(NOTE_D6,80);
					SOUND(NOTE_E6,80);
					SOUND(NOTE_F6,80);
					SOUND(NOTE_G6,80);
					SOUND(NOTE_A6,80);
					SOUND(NOTE_B6,80);
				    //soundf(0);
					//SOUND(440,500);
					SYSTEMOUT("end sound");
					cpu->flag=1;
				}break;
				//0xE8 //	CAL ERRS 	1 	Play the Error sound.
				case CAL_ERRS:{
					DISASM("CAL_ERRS  ");
				    for(int n = 0; n < 6; n++)
				    {
				        SOUND(NOTE_G5,20);
				        SOUND(NOTE_A5,20);
				        SOUND(NOTE_B5,20);
				        SOUND(NOTE_C6,20);
				        SOUND(NOTE_D6,20);
				        SOUND(NOTE_E6,20);
				    }
					//SOUND(200,500);
					SYSTEMOUT("play error sound");
					cpu->flag=1;
				}break;
				//0xE9 //	CAL SHTS 	1 	Play a short "pi" sound.
				case CAL_SHTS:{
					DISASM("CAL_SHTS  ");
					SOUND(NOTE_C5,150);
					SYSTEMOUT("play short peep sound");
					cpu->flag=1;
				}break;
				//0xEA //	CAL LONS 	1 	Play a longer "pi-" sound.
				case CAL_LONS:{
					DISASM("CAL_LONS  ");
					SOUND(NOTE_C5,450);
					SYSTEMOUT("play longer peep sound");
					cpu->flag=1;
				}break;
				//0xEB //	CAL SUND 	1 	Play a note based on the value of the A register
				//(allowed values are 1 - E).
				case CAL_SUND:{

					DISASM("CAL_SUND  ");
					//SOUND(cpu->M[AR],500);
					gmcSound(cpu->M[AR],300);

					SYSTEMOUT("play A reg");
					cpu->flag=1;
				}break;
				//0xEC // 	CAL TIMR 	1
				//Pause for the time calculated by (value of A register +1) * 0.1 seconds.
				case CAL_TIMR:{
					DISASM("CAL_TIMR  ");
					uint16_t n;
					showMatrix(((cpu->M[AR])*100+1));
					/*
				    for(n=0;n<((cpu->M[AR])*100+1);n++)
				    {
				      showMatrix();
				      _delay_ms(1);
				    }*/
					SYSTEMOUT("delay");
					cpu->flag=1;
				}break;

				//0xED //	CAL DSPR 	1 	Set the 2-pin LEDs with the value from data memory. The data to display is as follows: the upper three bits come from memory address 5F (bits 0-2), and the lower four from memory address 5E (bits 0-3).
				case CAL_DSPR:{
					DISASM("CAL_DSPR  ");

					SYSTEMOUT("set LED");
					cpu->flag=1;
				}break;
				//0xEE // 	CAL DEM- 	1
				//Subtract the value of the A register from the value in data memory.
				//The new value is stored in data memory as a decimal.
				//Afterwards, the Y register is decremented by 1.
				case CAL_DEMMINUS:{
					DISASM("CAL_DEM-  ");

					//SYSTEMOUT("dem-");
					cpu->M[YR]=cpu->M[YR]-cpu->M[AR];
					cpu->M[YR]++;
					cpu->M[YR]&=0xF;
					cpu->flag=1;
				}break;

				//0xEF //	CAL DEM+ 	1
				//Add the value of the A register to the value in data memory.
				//The new value is stored in memory as a decimal.
				//If the result is overflow, data memory will be automatically adjusted.
				//Afterwards, the Y register is decremented.
				case CAL_DEMPLUS:{
					DISASM("CAL_DEM+  ");

					cpu->M[YR]=cpu->M[YR]+cpu->M[AR];
					cpu->M[YR]--;
					cpu->M[YR]&=0xF;
					cpu->flag=1;
				}break;
			}
		}break;

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

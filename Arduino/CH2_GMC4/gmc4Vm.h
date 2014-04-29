/**
*
* @file gmc4Vm.h
*
* @brief opcodes and functions of the gmc4 Vm
*
* @author ChrisMicro
* @copyright (c) 2014 ChrisMicro
*
*/

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef __GMC4VM__
  #define __GMC4VM__
    #include <stdint.h>

    #define true (1==1)
    #define false !true

    // gmc 4 memory layout
    #define M_SIZE 0x70 // the whole memory program/data/registers

    #define M_OFFSET 0x50 // data memory offset inside main memory

    // register addresses inside memory
    #define AR  0x6F
    #define AR_ 0x69
    #define BR  0x6C
    #define BR_ 0x67
    #define YR  0x6E
    #define YR_ 0x68
    #define ZR  0x6D
    #define ZR_ 0x66

    typedef struct {
      uint8_t M[M_SIZE]; // memory
      uint8_t Pc; // programm counter
      uint8_t flag;
      uint8_t leds;
    }Cpu_t;

    // KA A0 CH CY AM MA MPLUS MMINUS TIA ATA TIY AIY CIA CIY EXTENDED JUMP
    #define KA 0      // KA 	K->Ar 	 0, 1 	The pressed key from the hex keypad is saved to the A register. If a key is not pressed, the Flag is set to 1, otherwise it is 0.
    #define AO 1      // AO 	Ar->Op 		1 	The 7-segment readout displays the value currently contained in the A register.
    #define CH 2      // CH 	Ar<=>Br
                       //       Yr<=>Zr 	1 	Exchange the contents of the A and B registers, and the Y and Z registers.
    #define CY 3      // CY 	Ar<=>Yr 	1 	Exchange the contents of the A and Y registers.
    #define AM 4      // AM 	Ar->M 		1 	Write the contents of the A register to data memory (memory address is 50 + Y register).
    #define MA 5      // MA 	M->Ar 		1 	Write the contents of data memory (50 + Y register) to the A register.
    #define MPLUS 6   // M+ 	M+Ar->Ar 	0, 1 	Add the contents of data memory (50 + Y register) to the A register. If there is overflow, the Flag is set to 1, otherwise 0.
    #define MMINUS 7  // M- 	M-Ar->Ar 	0, 1 	Subtract the contents of data memory (50 + Y register) from the A register. If the result is negative, the Flag is set to 1, otherwise 0.
    #define TIA 8     // TIA [ ] 	[ ] -> Ar 	1 	Transfer immediate to the A register.
    #define AIA 9     // AIA [ ] 	Ar + [ ] -> Ar 	0, 1 	Add immediate to the A register. If there is overflow, the Flag is set to 1, otherwise 0.
    #define TIY 0xA   // TIY [ ] 	[ ] -> Yr 	1 	Transfer immediate to the Y register.
    #define AIY 0xB   // AIY [ ] 	Yr + [ ] -> Yr 	0, 1 	Add immediate to the Y register. If there is overflow, the Flag is set to 1, otherwise 0.
    #define CIA 0xC   // CIA [ ] 	Ar != [ ] ? 	0, 1 	Compare immediate to the A register. If equal, Flag reset to 0, otherwise set to 1.
    #define CIY 0xD   // CIY [ ] 	Yr != [ ] ? 	0, 1 	Compare immediate to the Y register. If equal, Flag reset to 0, otherwise set to 1.
    #define EXTENDED 0x0E //      --- 	--- 	--- 	Extended code. See table below.
    #define JUMP 0xF  //JUMP [ ] [ ] 		1 	Jump to the immediate address if the Flag is 1, otherwise just increment the program counter. The Flag is then set to 1. Note that this is an absolute address. That is, JUMP [0] [2] will change the address pointer to hex address 0x02. You can jump both forward and backward in program space.

    //Extended code table.:
    #define CAL_RSTO     0xE0 // 	CAL RSTO 	1 	Clear the 7-segment readout.
    #define CAL_SETR     0xE1 // 	CAL SETR 	1 	Turn on the 2-pin LED using the Y register (Y register takes the value of 0-6).
    #define CAL_RSTR     0xE2 // 	CAL RSTR 	1 	Turn off the 2-pin LED using the Y register (Y register takes the value of 0-6).
                        //0xE3    	--- 	--- 	Not used.
    #define CAL_CMPL     0xE4 // 	CAL CMPL 	1 	Complement the A register (1 <=> 0).
    #define CAL_CHNG     0xE5 // 	CAL CHNG 	1 	Swap the A/B/Y/Z registers with A'/B'/Y'/Z'
    #define CAL_SIFT     0xE6 //	CAL SIFT 	0, 1 	Shift the A register right 1 bit. If the starting value is even (bit 0 = 0), set the Flag to 1, otherwise 0.
    #define CAL_ENDS     0xE7 //	CAL ENDS 	1 	Play the End sound.
    #define CAL_ERRS     0xE8 //	CAL ERRS 	1 	Play the Error sound.
    #define CAL_SHTS     0xE9 //	CAL SHTS 	1 	Play a short "pi" sound.
    #define CAL_LONS     0xEA //	CAL LONS 	1 	Play a longer "pi-" sound.
    #define CAL_SUND     0xEB //	CAL SUND 	1 	Play a note based on the value of the A register (allowed values are 1 - E).
    #define CAL_TIMR     0xEC // 	CAL TIMR 	1 	Pause for the time calculated by (value of A register +1) * 0.1 seconds.
    #define CAL_DSPR     0xED //	CAL DSPR 	1 	Set the 2-pin LEDs with the value from data memory. The data to display is as follows: the upper three bits come from memory address 5F (bits 0-2), and the lower four from memory address 5E (bits 0-3).
    #define CAL_DEMMINUS 0xEE // 	CAL DEM- 	1 	Subtract the value of the A register from the value in data memory. The new value is stored in data memory as a decimal. Afterwards, the Y register is decremented by 1.
    #define CAL_DEMPLUS  0xEF //	CAL DEM+ 	1 	Add the value of the A register to the value in data memory. The new value is stored in memory as a decimal. If the result is overflow, data memory will be automatically adjusted. Afterwards, the Y register is decremented.

    void simulatorReset(Cpu_t *);
    void showCpu(Cpu_t *);
    void executeVm(Cpu_t *);
#endif // __GMC4VM__

#ifdef __cplusplus
}
#endif

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

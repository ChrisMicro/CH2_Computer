#include "demo.h"
#include <util/delay.h>


/***************************************************************************

  demo start up code

***************************************************************************/

void startup()
{
  SYSTEMOUTCHAR('C');
  showMatrix(1000);

  SYSTEMOUTCHAR('H');
  showMatrix(1000);

  SYSTEMOUTCHAR('2');
  showMatrix(1000);

}
/***************************************************************************

  play notes from keyboard

  emulation of the GMC4 demo program 9

***************************************************************************/
void ElectronicOrgan_GMC4Prog9()
{
  gmcSound(0,100); // play note
  uint8_t c;
  do
  {
    c=getKeyCode();
    gmcSound(c,100); // play note
    hex1(c); // write key to matrix display
  }while(c!=HASHKEY); // pressing the hash key '#' exits the program

}
/***************************************************************************

  play notes from memory

  emulation of the GMC4 demo program A

  memory layout:
  tempo of song, note, duration, note duration ....

  special command 0: repeat the song

***************************************************************************/
void PlayNotes_GMC4ProgA(Cpu_t *cpu)
{
  uint16_t tempo;
  uint16_t speed;
  uint8_t note;
  uint8_t index=0;

  uint8_t c;
  tempo=cpu->M[index++]+1;
  do
  {
	note=cpu->M[index++];
	speed=cpu->M[index++]*tempo*50;
	if(note==0) // repeat song
	{
		index=1;
	}else // play note
	{
		gmcSound(note,speed); // play note
	}
	c=scanKey();
  }while(c!=HASHKEY); // pressing the hash key '#' exits the program
  _putchar('n');
}

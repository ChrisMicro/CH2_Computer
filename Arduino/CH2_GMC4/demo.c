#include "demo.h"
#include <util/delay.h>


/***************************************************************************

  demo start up code

***************************************************************************/

void startup()
{
	initDisplay();
	uint8_t row,col;
	// test display rows and columns, led and speaker
	for(row=0;row<5;row++)
	{
		for(col=0;col<7;col++)
		{

		  setRow(row);
		  setCol(col);

		  _delay_ms(50);

		}
		gmcSound(row,20); // play note
	    toggleLed();
	}
	ledOff();

	// test speaker
    gmcSound(8,20); // play note

	// show computer name
	SYSTEMOUTCHAR('C');
	showMatrix(500);

	SYSTEMOUTCHAR('H');
	showMatrix(500);

	SYSTEMOUTCHAR('2');
	showMatrix(500);

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
  uint16_t duration;
  uint8_t note;
  uint8_t index=0;

  uint8_t c;
  tempo=cpu->M[index++]+1;
  do
  {
	note=cpu->M[index++];
	duration=cpu->M[index++]*tempo*3;
	if(note==0) // repeat song
	{
		index=1;
	}else // play note
	{
		gmcSound(note,duration); // play note
	}
	c=scanKey();
  }while(c!=HASHKEY); // pressing the hash key '#' exits the program
  _putchar('n');
}
/***************************************************************************

 joystick test

***************************************************************************/
void JoystickTest()
{
	  const int xAxis = 1;
	  const int yAxis = 2;

	  uint32_t x,y;
	  uint8_t row,col,c;
	  uint8_t soundOnFlag=0;

	  do
	  {
		  x = 1023-readAdc(xAxis); // x axis of joystick is inverted
		  _delay_ms(10);
		  c=scanKey();
		  if(c==1)soundOnFlag=1;
		  if(c==2)soundOnFlag=0;
		  y = readAdc(yAxis);

		  initDisplay();
		  setCol(6-(x*7/1024));
		  setRow(y*5/1024);
		  if(soundOnFlag)gmcSound((x*7/1024),30); // play note
		  _delay_ms(30);


	  }while(c!=HASHKEY); // pressing the hash key '#' exits the program
	  _putchar('n');
}

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

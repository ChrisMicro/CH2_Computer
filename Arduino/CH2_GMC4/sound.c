#include "sound.h"

void arduinoSound(frequency,duration);

void sound(uint16_t frequency, uint16_t duration)
{
  arduinoSound(frequency,duration);
}

uint16_t frequencyTable[]={
   NOTE_A4 ,
   NOTE_B4 ,
   NOTE_C5 ,
   NOTE_D5 ,
   NOTE_E5 ,
   NOTE_F5 ,
   NOTE_G5 ,
   NOTE_A5 ,
   NOTE_B5 ,
   NOTE_C6 ,
   NOTE_D6 ,
   NOTE_E6 ,
   NOTE_F6 ,
   NOTE_G6 ,
   NOTE_A6 ,
   NOTE_B6
};

void gmcSound(uint8_t note, uint16_t duration)
{
  sound(frequencyTable[note],duration);
}

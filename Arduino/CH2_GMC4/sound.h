#ifdef __cplusplus
extern "C"
{
#endif

#ifndef __SOUND__
  #define __SOUND__

  #include <stdint.h>

  #define NOTE_A4 440
  #define NOTE_B4 494
  #define NOTE_C5 523
  #define NOTE_D5 587
  #define NOTE_E5 659
  #define NOTE_F5 698
  #define NOTE_G5 784
  #define NOTE_A5 880
  #define NOTE_B5 988
  #define NOTE_C6 1047
  #define NOTE_D6 1175
  #define NOTE_E6 1319
  #define NOTE_F6 1397
  #define NOTE_G6 1568
  #define NOTE_A6 1760
  #define NOTE_B6 1976

  void sound(uint16_t frequency, uint16_t duration);
  void gmcSound(uint8_t note, uint16_t duration);

#endif // __SOUND__

#ifdef __cplusplus
}
#endif


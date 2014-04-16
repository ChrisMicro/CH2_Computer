/*
  Melody
 
 Plays a melody
 
 circuit:
 * 100-ohm speaker on digital pin 9
 
 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe
 
 modified 16 April 2014 for the CH2-Microcomputer
 by ChrisMicro

This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/Tone
 
 */
 
 #include "pitches.h"
#define CH_SPEAKERPIN 9 // the speaker is connected to Arduino pin 9 

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

void setup() {

}

void loop() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(CH_SPEAKERPIN, melody[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(CH_SPEAKERPIN);
  }
  // peep every 30s to remind people switching of the computer
  while(1)
  {
    delay(30000);
    tone(CH_SPEAKERPIN, NOTE_A4,10);
  }
  
}

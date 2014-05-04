
#include "Arduino.h"
#define F_CPU 8000000UL // system frequency
#define FS ( F_CPU/256 ) // sampling frequency

/*
  synth
 */

void initTimer()
{
	//TCNT1 = 0; // reset timer 1
	// for FAST PWM (8-Bit PWM) on OC1A
	//TCCR1A = (1 << WGM10) | (1 << COM1A1) ;
	TCCR1A = (1 << WGM10) | (1 << COM1A1) ;

	// tmr1 running on MCU clock/8
	//TCCR1B = (1 << CS11);
	// tmr1 running on MCU full speed clock
	TCCR1B = (1 << WGM12) |(1 << CS10);

	// interrupt mask register: enable timer1 overflow
	TIMSK1 = (1 << TOIE1);

	sei();

	// Speaker Output
	DDRB = (1 << PB1) ;
}
void setup() {
	initTimer();
}
void ledOn()
{
  DDRC|=1;

  PORTC|=1;
}

void ledOff()
{
  PORTC&=~1;
}

volatile uint16_t MsTimer=0,FreqCoefficient=1000,Amplitude=100;

SIGNAL (TIMER1_OVF_vect)
{
	static uint8_t timer=31;
	static uint16_t phase0;
	static uint16_t sig0;

	phase0+=FreqCoefficient; //0.88us

	sig0=Amplitude*(phase0>>8);

	OCR1A=(sig0>>8);

	timer--;
	if(timer==0)
	{
		MsTimer++; // increase millisecond timer
		// mstimerrate=0.992 milli seconds @FCPU16MHz
		timer=31;
	}
}

void iDelay(uint16_t d)
{
	MsTimer=0;
	while(MsTimer<d);
}

void setFreq(uint16_t freq)
{

	FreqCoefficient=freq*65536UL/FS;
}
void loop() {
  ledOn();
  //delay(250);              // wait for a second
  iDelay(250);
  ledOff();
  delay(250);              // wait for a second
  //FreqCoefficient+=100;
  setFreq(0);
}

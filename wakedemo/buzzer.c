#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

/*Defining notes to bee used with their frequency */
#define C4 1911
#define D4 1703
#define E4 1517
#define F4 1432
#define G4 1276
#define A4 1136
#define B4 1012

void init_buzzer() // initialize buzzer
{
  timerAUpmode(); //speaker
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~ BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6; //output to speaker
}

void buzzer_set_period(short cycles) //buzzer clock 
{
  
  CCR0 = cycles;
  CCR1 = cycles >> 1; //half cycle
}

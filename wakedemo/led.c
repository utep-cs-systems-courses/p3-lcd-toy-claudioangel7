#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "stateMachine.h"


unsigned char red_on = 0; //red light off
unsigned char green_on = 0; // green light off

static char redVal[] = {0, LED_RED};
static char greenVal[] = {0, LED_GREEN};

unsigned char led_changed = 0; /* if light changes it should be 1 */
  
void led_init()
{
  P1DIR |= LEDS; // bits are connected to output
  led_changed = 1;
  led_update();
}

void led_update() /*will clear everything*/
{
  if(led_changed){ // if led_changed = 1
    char ledFlags = redVal[red_on] | greenVal[green_on];

    P1OUT &= (0xff^LEDS) | ledFlags; //clearing bits
    P1OUT |= ledFlags; // set bits
    led_changed = 0;
  }
}


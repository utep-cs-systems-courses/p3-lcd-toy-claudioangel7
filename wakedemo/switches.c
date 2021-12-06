#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachine.h"
#include "buzzer.h"
#include "libTimer.h"

//char state;
static unsigned char last_switch, current_switch;
char switch_state_down;
char B1, B2, B3, B4;


static char switch_update_interrupt_sense() // will update the interrupt depending on buttons
{
  char p2val = P2IN;

  P2IES |= (p2val & SWITCHES); // if up then sense down
  P2IES &= (p2val | ~SWITCHES); // if down then sense up

  return p2val;
}

void switch_init() // initialize switch
{
  P2REN |= SWITCHES; // enables resistors changes whether 1 or 0
  P2IE |= SWITCHES; // allows for interrupts to happen in switches
  P2OUT |= SWITCHES; // what actually sets switch to be 1 or 0
  P2DIR &= ~SWITCHES; // allows current to go out and selects bits

  switch_update_interrupt_sense();
  

}

unsigned int switch_read()
{
  unsigned int switch_changed = current_switch ^ last_switch;
  last_switch = current_switch;
  return current_switch | (switch_changed << 8);
}

void __interrupt_vec(PORT2_VECTOR) Port_2()
{
  if(P2IFG & SWITCHES){
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}

// will be used to determine button pressed which will interact with state machine
void switch_interrupt_handler() 
{
  char p2val = switch_update_interrupt_sense();

  B1 = (p2val & SW1) ? 0 : 1;
  B2 = (p2val & SW2) ? 0 : 1;
  B3 = (p2val & SW3) ? 0 : 1;
  B4 = (p2val & SW4) ? 0 : 1;

  if(B1){
  
    switch_state_down = 1; // state 1
   
  }

  else if(B2){
   
    switch_state_down = 2;
    
  }
  else if(B3){
 
    switch_state_down = 3;
    
  }
  else if(B4){
   
    switch_state_down = 4;
  }
}

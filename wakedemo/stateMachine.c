#include <msp430.h>
#include "stateMachine.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"
#define C4 1911
#define D4 1703
#define B4 1012

//int color = COLOR_GREEN;
//#include "functionsDraw.h"

static int state = 0;

char toggle = 0; //on or off
char times = 0; //times led is on
//char dimState = 0; // will know in which dim it is on

void fish() //will change the position of fish 1
{
  
  switch(state){

  case 0:
    clearScreen(COLOR_BLUE); //erases previous fish
    drawFish(40,50, COLOR_ORANGE, 20); //changes position.
    state = 1;
     break;
  case 1:
    clearScreen(COLOR_BLUE);
    drawFish(50,50, COLOR_ORANGE, 20);
    state = 2;
    break;
  case 2:
    clearScreen(COLOR_BLUE);
    drawFish(60,50, COLOR_ORANGE, 20);
    state = 3;
    break;
  case 3:
    clearScreen(COLOR_BLUE);
    drawFish(70, 50, COLOR_ORANGE, 20);
    state = 4;
    break;
  case 4:
    clearScreen(COLOR_BLUE);
    drawFish(80, 50, COLOR_ORANGE, 20);
    state = 1;
    break;
  }
}

void fish2() //will change position of fish every case
{
  
  switch(state){

  case 0:
    clearScreen(COLOR_RED); //will erase previous fish
    drawFish(40,50, COLOR_BLUE, 20); //same fish with new postion
    state = 1;
     break;
  case 1:
    clearScreen(COLOR_RED);
    drawFish(50,50, COLOR_BLUE, 20);
    state = 2;
    break;
  case 2:
    clearScreen(COLOR_RED);
    drawFish(60,50, COLOR_BLUE, 20);
    state = 3;
    break;
  case 3:
    clearScreen(COLOR_RED);
    drawFish(70, 50, COLOR_BLUE, 20);
    state = 4;
    break;
  case 4:
    clearScreen(COLOR_RED);
    drawFish(80, 50, COLOR_BLUE, 20);
    state = 1;
    break;
  }
}

void changeColor() //everytime there is a new diamond drawn
{
  
  switch(state){
  case 1:
    clearScreen(COLOR_GREEN); //will clear the screen
    drawDiamond(20,20,20, COLOR_RED); //draws new different diamond
    state = 2;
    break;
  case 2:
    clearScreen(COLOR_GREEN);
    drawDiamond(20,20, 20, COLOR_YELLOW);
    state = 3;
    break;
  case 3:
    clearScreen(COLOR_GREEN);
    drawDiamond(20,20,20, COLOR_BLUE);
    state = 4;
    break;
  case 4:
    clearScreen(COLOR_GREEN);
    drawDiamond(20,20,20, COLOR_BLACK);
    state = 1;
    break;
  }
}

void buzzer() //used to activate buzzer
{
  static char next = 0;

  switch(next){ //will change to see which note is played
  case 1:
    buzzer_set_period(C4);
    next++;
    break;
  case 2:
    buzzer_set_period(B4);
    next++;
    break;
  case 3:
    buzzer_set_period(D4);
    next++;
    break;
  default:
    next++;
    break;
  
  }
}


void sadness_and_sorrow() {
  static char next = 0;
  switch(next) {

  case 1:
    buzzer_set_period(880); //La
    next++;
    break;
  case 2:
    buzzer_set_period(659); //Mi
    next++;
    break;
  case 3:
    buzzer_set_period(880); //La
    next++;
    break;
  case 4:
    buzzer_set_period(1046); //Do
    next++;
    break;
  case 5:
    buzzer_set_period(1174); //Re 
    next++;
    break;
  case 6:
    buzzer_set_period(880); //La
    next++;
    break;
  case 7:
    buzzer_set_period(1046); //Do
    next++;
    break;
  case 8:
    buzzer_set_period(987); //Si
    next++;
    break;
  case 9:
    buzzer_set_period(1046); //Do
    next++;
    break;
  case 10:
    buzzer_set_period(1174); //Re
    next++;
    break;
  case 11:
    buzzer_set_period(784); //Sol
    next++;
    break;
  case 12:
    buzzer_set_period(1318); //#Mi
    next++;
    break;
  default:
    next++;
    break;
  }

}

//void toggle_green_led()
char toggle_green_led() //will dim the light to 50%
{
  if(times < 500){ //decides how many times the method is done
    times++;
    toggle = toggle_green(toggle); //each time the toggle state will change
    led_update;
  }
  else{
    times = 0;
    // dimState = 2; //added
  }
   return 2;
}

char dim25()
{ //dim light to 25 %
  if(times < 70){ // will keep reapeting until 70
    times++;
    switch(state){ // decides when the leds are turned on
    case 0:
      green_on = 0;
      state = 1;
      break;
    case 1:
      green_on = 0;
      state = 2;
      break;
    case 2:
      green_on = 0;
      state = 3;
    case 3:
      green_on = 1;
      state = 0;
      break;
   }
    led_update();
  }
  else{
    times = 0;
    // dimState = 1;
      }
  return 1;
    // led_changed = 1
}

char dim75(){ //dim light 75%
  if(times < 70){
    times++;
    switch(state){ // switch cases controls how much the led lights up
    case 0:
      green_on = 0;
      state = 1;
      break;
    case 1:
      green_on = 1;
      state = 2;
      break;
    case 2:
      green_on = 1;
      state = 3;
      break;
    case 3:
      green_on = 1;
      state = 0;
      break;
    }
    //led_changed = 1;
    led_update();
  }
  else{
    times = 0;
    // dimState = 3;
  }
  return 3;
}




void dimLights()
{
  static char dimState = 0;
  switch(dimState){
  case 0:       // will activate led at 25%
    dim25();
    dim25();
    dim25();
    dimState = 1;
    break;
  case 1:         // led to 50%
    toggle_green_led();
    toggle_green_led();
    toggle_green_led();
    dimState = 2;
    break;
  case 2:      // led to 50%
    dim75();
    dim75();
    dim75();
    dimState = 0;
    break;
  }
}

void state_advance()  //changes states depending on what switch clicked.
{
  static char next_state;

  switch(switch_state_down){
      case 1:
        fish();// fish that changes color
        sadness_and_sorrow();
	break;
      case 2:
	
	fish2(); // fish with sound will activate
	buzzer();
	break;
     case 3:
       changeColor(); // activate diamond with changing colors
	//toggle_green_led();
	//dimLights();
	//clearScreen(COLOR_YELLOW);
	break;
     case 4: // will turn on green led   
	dimLights();
      	break;
  }      
}



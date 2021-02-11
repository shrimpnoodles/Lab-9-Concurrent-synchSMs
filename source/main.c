/*	Author: lab
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

enum ThreeLEDsSM {start, init, one, two} state;
unsigned char threeLEDS;

ThreeLEDsSM_Tick(){
	switch(state) { 
		case start:
			state = init;
			break;
		case init:
			state = one;
			break;
		case one:
			state = two;
			break;
		case two:
			state = one;
			break;
		default:
			case = start;
			break;
		}
	switch(state){
		case start:
			break;
		case init:
			threeLEDS = 0x00;
			break;
		case one:
			threeLEDS = 0x01;
			break;
		case two:
			threeLEDS = 0x02;
			break;
		default:
			break;
		}
}

enum BlinkingLEDSM {startBL, init_BL, 3on, 3off} state_BL;
unsigned char blinkingLED;
BlinkingLEDSM_Tick(){
	switch(state_BL){
		case startBL:
			state_BL = init_BL;
			break;
		case init_BL:
			state_BL= 3on;
			break;
		case 3on:
			state_BL = 3off;
			break;
		case 3off:
			state_BL = 3on;
			break;
		default:
			case = start_BL;
			break;
		}
	switch(state_BL){ //actions
		case start_BL:
			break;
		case init_BL:
			blinkingLED = 0x00;
			break;
		case 3on:
			blinkningLED = 0x04;
			break;
		case 3off:
			blinkingLED = 0x00;
			break;
		default:
			break;
		}
}

enum CombineLEDsSM { start_com, out_com} state_com;

CombineLEDsSM_Tick(){
	switch( state_com){
	case start_com:
		state_com = out_com;
		break;
	case out_com:
		break;
	default:
		state_com = start_com;
		break;
	}
	switch(state_com){
		case start_com:
			break;
		case out_com:
			PORTB = blinkingLED | threeLEDs;
			break;
		}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xff;  PORTB = 0x00;
	
	state = start;
	state_BL = startBL;
	state_com = start_com;
	TimerSet(100);
	TimerOn();
    /* Insert your solution below */
    while (1) {
	ThreeLEDsSM_Tick();
	BlinkingLEDSM_Tick();
	CombineLEDsSM_Tick();

	while(!TimerFlag){}
	TimerFlag=0;
    }
    return 1;
}

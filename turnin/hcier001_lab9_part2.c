/*	Author: lab
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	submission link: https://drive.google.com/file/d/1Gu8JJY3N-VzPK1QG4fpCv-uDPYHHe8IR/view?usp=sharing
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

enum ThreeLEDsSM {start, init, one, two, three} state;
unsigned char threeLEDS;
unsigned char counter;
void ThreeLEDsSM_Tick(){
	switch(state) { 
		case start:
			state = init;
			break;
		case init:
			state = one;
			break;
		case one:
			if(counter%3 ==0){
				state = two;
			}
			else{
				state = one;
			}
			break;
		case two:
			if(counter%3 ==0 ){
				state = three;
			}
			else {
				state = two;
			}
			break;
		case three:
			if(counter%3 == 0){
				state = one;
			}
			else{
				state = three;
			}
			break;
		default:
			state = start;
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
			counter++;
			break;
		case two:
			threeLEDS = 0x02;
			counter++;
			break;
		case three:
			threeLEDS = 0x04;
			counter++;
			break;
		default:
			break;
		}
}

enum BlinkingLEDSM {startBL, init_BL, fouron, fouroff} state_BL;
unsigned char blinkingLED;
void BlinkingLEDSM_Tick(){
	switch(state_BL){
		case startBL:
			state_BL = init_BL;
			break;
		case init_BL:
			state_BL= fouron;
			break;
		case fouron:
			state_BL = fouroff;
			break;
		case fouroff:
			state_BL = fouron;
			break;
		default:
			state_BL = startBL;
			break;
		}
	switch(state_BL){ //actions
		case startBL:
			break;
		case init_BL:
			blinkingLED = 0x00;
			break;
		case fouron:
			blinkingLED = 0x08;
			break;
		case fouroff:
			blinkingLED = 0x00;
			break;
		default:
			break;
		}
}

enum CombineLEDsSM { start_com, out_com} state_com;

void CombineLEDsSM_Tick(){
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
			PORTB = blinkingLED | threeLEDS;
			break;
		}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xff;  PORTB = 0x00;
	
	state = start;
	state_BL = startBL;
	state_com = start_com;
	counter = 0;
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

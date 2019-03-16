/*
 * Button.c
 *
 * Created: 13-3-2019 15:48:41
 *  Author: Max van Noordennen
 */ 

#include <avr/io.h>
#include "../hardware/Button.h"
#include "../hardware/SegDisplay.h"

typedef enum {NOTHING,BUTTON_LEFT, BUTTON_RIGHT}Buttons;

//void Button_checkinput()
//{
	//DDRC = 0b00000000;
	//DDRB = 0b00000000;
	//DDRD = 0b11111111;
	//
	//
	//
	//int counter = 0;
	//while (1)
	//{
		//if((PINC & (1<<5)) > 0 ) {//if PIN5 of port C is high
		//counter++;
		//writeLedScore(counter);
	//}	
	//else if((PINC3 & 1<<3) > 0) 
	//{
		//counter--;
		//writeLedScore(counter);
	//}
	//PORTD = 0b00100000;
	//}
//}


void Button_initports()
{
	DDRC = 0b00000000;
} 

unsigned char button_state()
{
	if (!(PINC & (1<<5)))
	{
		_delay_ms(25);
		if (!(PINC & (1<<5))) return 1;
	}
	return 0;
}



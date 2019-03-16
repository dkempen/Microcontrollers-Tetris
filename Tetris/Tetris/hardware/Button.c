/*
 * Button.c
 *
 * Created: 13-3-2019 15:48:41
 *  Author: Max van Noordennen
 */ 

#include <avr/io.h>
#include "../hardware/Button.h"

#define BUTTON_MOVE_LEFT 0x80  //PINC
#define BUTTON_MOVE_DOWN 0x70  //PINC
#define BUTTON_MOVE_RIGHT 0x60 //PINC
#define BUTTON_TURN_LEFT 0x80  //PIND
#define BUTTON_TURN_RIGHT 0x60 //PIND

void Button_Init(void)
{
	DDRC = 0b00000000;
	DDRD = 0b00000000;
} 

char Button_GetInput(void)
{
	if ((PINC & BUTTON_MOVE_RIGHT) > 0)
		return 'd';
	else if ((PINC & BUTTON_MOVE_DOWN) > 0)
		return 's';
	else if ((PINC & BUTTON_MOVE_LEFT) > 0)	
		return 'a';		
	else if ((PIND & BUTTON_TURN_LEFT))
		return 'q';
	else if ((PIND & BUTTON_TURN_RIGHT))
		return 'e';
	else
		return 'w';	
	
}



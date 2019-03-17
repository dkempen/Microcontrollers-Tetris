/*
 * Button.c
 *
 * Created: 13-3-2019 15:48:41
 *  Author: Max van Noordennen
 */ 

#include <avr/io.h>
#include "../hardware/Button.h"

#define BUTTON_MOVE_LEFT 0x80  //PIND
#define BUTTON_MOVE_DOWN 0x40  //PIND
#define BUTTON_MOVE_RIGHT 0x20 //PIND
#define BUTTON_TURN_LEFT 0x80  //PINE
#define BUTTON_TURN_RIGHT 0x20 //PINE

void Button_Init(void)
{
	DDRD = 0b00000000;
	DDRE = 0b00000000;
} 

char Button_GetInput(void)
{
	if ((PIND & BUTTON_MOVE_LEFT))	
		return 'a';	
	else if ((PIND & BUTTON_MOVE_DOWN))
		return 's';
	else if ((PIND & BUTTON_MOVE_RIGHT))
		return 'd';
	else if ((PINE & BUTTON_TURN_LEFT))
		return 'q';
	else if ((PINE & BUTTON_TURN_RIGHT))
		return 'e';
	else
		return 'w';	
	
}



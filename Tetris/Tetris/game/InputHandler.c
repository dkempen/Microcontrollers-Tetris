/*
 * InputHandler.c
 *
 * Created: 27-2-2019 14:59:50
 *  Author: Ian
 */ 

#include <stdlib.h>

#include "../util/Random.h"
#include "../hardware/Button.h"

#include "InputHandler.h"



int currentInput = IDLE;


void CheckForInput(void)
{	
	char input = Button_GetInput();

	if (input == 'a')
	currentInput = MOVE_LEFT;
	else if (input == 'd')
	currentInput = MOVE_RIGHT;
	else if (input == 's')
	currentInput = MOVE_DOWN;
	else if (input == 'q')
	currentInput = TURN_LEFT;
	else if (input == 'e')
	currentInput = TURN_RIGHT;
	else
	currentInput = IDLE;
}

void AiInput(void)
{
	int num = (GetSeed()) % 6;

	if (num == 0)
	currentInput = MOVE_LEFT;
	else if (num == 1)
	currentInput = MOVE_RIGHT;
	else if (num == 2)
	currentInput = MOVE_DOWN;
	else if (num == 3)
	currentInput = TURN_LEFT;
	else if (num == 4)
	currentInput = TURN_RIGHT;
	else
	currentInput = IDLE;
}

int GetCurrentInput(void)
{
	return currentInput;
}

void ResetInput(void){
	currentInput = IDLE;
}
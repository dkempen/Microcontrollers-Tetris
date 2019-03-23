/*
 * StateManager.c
 *
 * Created: 27-2-2019 15:00:54
 *  Author: Ian
 */ 

#include "StateManager.h"


int currentState;

void InitStateManager(void)
{
	currentState = STATE_MENU;
}

void SetState(int state)
{
	currentState = state;
}

int GetState()
{
	return currentState;
}

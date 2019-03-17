/*
 * HighScoreScreen.c
 *
 * Created: 27-2-2019 14:59:41
 *  Author: Aspire V3-772G-747a8
 */ 

#include <avr/delay.h>

#include "../hardware/Button.h"

#include "StateManager.h"
#include "HighScoresScreen.h"
#include "Menu.h"

#include "Draw.h"
#include "Score.h"

int currentElement;

void InitHighScoresScreen(void)
{
	currentElement = 0;
	RunHighScoresScreen();
}

void RunHighScoresScreen(void)
{
	
	//Prevents key presses in another screen from affecting the current screen
	_delay_ms(1000);

	while (GetState() == STATE_HIGHSCORES) {


		DrawHighScoresScreen(GetHighScores(), currentElement);

		char input = Button_GetInput();

		if (input == 's')
			SetState(STATE_MENU);
		if (input == 'd'){
			currentElement ++;	
			if(currentElement >= MAX_AMOUNT_OF_HIGHSCORES)
				currentElement = 0;			
		}
	}

	if (GetState() == STATE_MENU)
	RunMenu();
}

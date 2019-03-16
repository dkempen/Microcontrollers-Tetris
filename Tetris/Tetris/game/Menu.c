/*
 * Menu.c
 *
 * Created: 27-2-2019 15:00:13
 *  Author: Aspire V3-772G-747a8
 */ 

#include <util/delay.h>

#include "../hardware/Button.h"

#include "Menu.h"
#include "StateManager.h"
#include "Game.h"
#include "HighScoresScreen.h"
#include "Draw.h"
#include "Score.h"

void InitMenu(void)
{
	InitHighScores();
	RunMenu();
}

void RunMenu(void)
{
	while (GetState() == STATE_MENU) {
		
		//Easybuzz
		_delay_ms(1);
		
		
		//system("cls"); For clearing command prompt, not needed in BIGAVR

		DrawMenu();

		char input = Button_GetInput(); //TODO: Replace with keys from BIGAVR

		if (input == 'a')
		SetState(STATE_GAME);
		else if (input == 's')
		SetState(STATE_HIGHSCORES);
		else if (input == 'd')
		SetState(STATE_EXIT);

	}

	if (GetState() == STATE_GAME)
	InitGame();
	else if (GetState() == STATE_HIGHSCORES)
	InitHighScoresScreen();

}

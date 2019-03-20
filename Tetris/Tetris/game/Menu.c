/*
 * Menu.c
 *
 * Created: 27-2-2019 15:00:13
 *  Author: Aspire V3-772G-747a8
 */ 

#define F_CPU 8000000L

#include <avr/delay.h>

#include "../hardware/Button.h"
#include "../hardware/easybuzz.h"
#include "../hardware/DotMatrix.h"

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
	SegDisplay_writeLedScore(0);
	matrix_clear();
	
	DrawMenu();
	easybuzz_play_loop(SONG_MENU);
	
	//Prevents key presses in another screen from affecting the current screen
	_delay_ms(1000);
	
	while (GetState() == STATE_MENU) {
		easybuzz_update();
		_delay_ms(1);
		
		char input = Button_GetInput(); 

		if (input == 'd')
		SetState(STATE_GAME);
		else if (input == 's')
		SetState(STATE_HIGHSCORES);
	//	else if (input == 'a')
	//	SetState(STATE_EXIT);
	
	}

	if (GetState() == STATE_GAME)
		InitGame();
	else if (GetState() == STATE_HIGHSCORES)
		InitHighScoresScreen();
}

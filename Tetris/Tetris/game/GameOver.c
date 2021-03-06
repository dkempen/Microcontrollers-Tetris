/*
 * GameOver.c
 *
 * Created: 27-2-2019 14:59:32
 *  Author: Ian
 */ 

#define F_CPU 8000000L

#include <avr/delay.h>

#include "../hardware/Button.h"
#include "../hardware//DotMatrix.h"
#include "../hardware/EasyBuzz.h"

#include "StateManager.h"
#include "GameOver.h"
#include "Game.h"
#include "Menu.h"

#include "Draw.h"
#include "Score.h"
#include "Field.h"

void InitGameOver(void)
{
	RunGameOver();
}

void RunGameOver(void)
{
	DrawGameOverScreen(GetScore(), IsHighScore());
	easybuzz_stop_loop();
	easybuzz_play_effect(EFFECT_GAME_OVER);
	
	//Prevents key presses in another screen from affecting the current screen
	int i = 0;
	while (i < 1000)
	{
		if (i == 0 || i == 500)
			matrix_fill();
		if (i == 250 || i == 750)
			DrawFieldWithoutPlayer(GetField());
		easybuzz_update();
		_delay_ms(1);
		i++;
	}
	
	while (GetState() == STATE_GAMEOVER)
	{
		
		easybuzz_update();
		_delay_ms(1);
				

		char input = Button_GetInput();

		if (input == 's')
		SetState(STATE_MENU);
	}

	if (GetState() == STATE_GAME)
	InitGame();
	else if (GetState() == STATE_MENU)
	RunMenu();
}

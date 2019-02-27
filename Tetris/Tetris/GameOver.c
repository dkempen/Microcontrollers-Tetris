/*
 * GameOver.c
 *
 * Created: 27-2-2019 14:59:32
 *  Author: Aspire V3-772G-747a8
 */ 

#include "StateManager.h"
#include "GameOver.h"
#include "Game.h"
#include "Menu.h"

#include "Draw.h"
#include "Score.h"

void InitGameOver(void)
{
	RunGameOver();
}

void RunGameOver(void)
{
	while (GetState() == STATE_GAMEOVER)
	{
		//system("cls"); For clearing command prompt, not needed in BIGAVR

		DrawGameOverScreen(GetScore(), IsHighScore());

		char input = 'a'; //TODO: Remove with keys from BIGAVR

		if (input == 'a')
		SetState(STATE_GAME);
		else if (input == 'd')
		SetState(STATE_MENU);
	}

	if (GetState() == STATE_GAME)
	InitGame();
	else if (GetState() == STATE_MENU)
	RunMenu();
}

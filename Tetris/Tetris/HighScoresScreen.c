/*
 * HighScoreScreen.c
 *
 * Created: 27-2-2019 14:59:41
 *  Author: Aspire V3-772G-747a8
 */ 

#include "StateManager.h"
#include "HighScoresScreen.h"
#include "Menu.h"

#include "Draw.h"
#include "Score.h"

void InitHighScoresScreen(void)
{
	RunHighScoresScreen();
}

void RunHighScoresScreen(void)
{

	while (GetState() == STATE_HIGHSCORES) {

		//system("cls"); For clearing command prompt, not needed in BIGAVR

		DrawHighScoresScreen(GetHighScores(), MAX_AMOUNT_OF_HIGHSCORES);



		char input = 'a'; //TODO: Replace with keys from BIGAVR

		if (input == 'z')
		SetState(STATE_MENU);

	}

	if (GetState() == STATE_MENU)
	RunMenu();
}

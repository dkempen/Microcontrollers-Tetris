/*
 * Game.c
 *
 * Created: 27-2-2019 14:59:23
 *  Author: Aspire V3-772G-747a8
 */ 

#include <stdio.h>
#include <time.h>

#include "Game.h"
#include "GameOver.h"
#include "Menu.h"
#include "StateManager.h"

#include "Blocks.h"
#include "Field.h"
#include "Player.h"
#include "Draw.h"
#include "InputHandler.h"
#include "Score.h"
#include "Collision.h"



void InitGame(void)
{
	InitScore();
	InitField();
	InitBlocks();

	RunGame();
}


void RunGame(void)
{
	SpawnNewBlock();

	int startTime = time(NULL);

	while (GetState() == STATE_GAME)
	{
		//system("cls"); For clearing command prompt, not needed in BIGAVR

		DrawScore(GetScore());
		DrawField(GetField(), GetPlayer());

		int currentTime = time(NULL);
		//Sleep(250); TODO: Implement a deltatime for 4 rotations per second

		CheckForInput();
		UpdatePlayer();

		if (currentTime - startTime >= 1)
		{
			startTime = time(NULL);

			MoveDown();
		}
	}

	if (GetState() == STATE_GAMEOVER)
	InitGameOver();
	else if (GetState() == STATE_MENU)
	RunMenu();
}

void SpawnNewBlock(void)
{
	CheckForFullRow();

	srand(time(NULL));
	int num = rand() % 7;

	InitPlayer(3, 0, num);
	
	//If the newly spawned player block is overlapping with the blocks filling the field
	// then set the state to GameOver
	if (IsOverlapping(GetField(), GetPlayer()) == 0) {

		CheckIfHighScore();
		SetState(STATE_GAMEOVER);
	}
	
}

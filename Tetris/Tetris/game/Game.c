/*
 * Game.c
 *
 * Created: 27-2-2019 14:59:23
 *  Author: Aspire V3-772G-747a8
 */ 

#include <stdio.h>
//#include <time.h>
#include <avr/io.h>

#include "../util/Random.h"

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

#define MILLISEC 128

int millisCounter;

void InitGame(void)
{
	InitScore();
	InitField();
	InitBlocks();

	RunGame();
}


void RunGame(void)
{
	TCCR1B |= ((1 << CS10) | (1 << CS11));
	
	//Tracks millisecond loops
	millisCounter = 0;
	
	SpawnNewBlock();
	
	while (GetState() == STATE_GAME)
	{
		
		if(TCNT1 >= MILLISEC){
			TCNT1 = 0;
			millisCounter += 1;
		}
		
		if(millisCounter % 250 != 0){
			continue;
		}
		
		DrawScore(GetScore());
		DrawField(GetField(), GetPlayer());

		//CheckForInput();
		AiInput();
		UpdatePlayer();

		if (millisCounter >= 1000)
		{
			MoveDown();
			millisCounter = 0;
			TCNT1 = 0;
			
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

	//srand(millisCounter);
	//int num = (rand()) % 7;

	InitPlayer(3, 0, GetSeed() % 8);
	
	//If the newly spawned player block is overlapping with the blocks filling the field
	// then set the state to GameOver
	if (IsOverlapping(GetField(), GetPlayer()) == 0) {

		CheckIfHighScore();
		SetState(STATE_GAMEOVER);
	}
	
}


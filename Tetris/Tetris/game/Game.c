/*
 * Game.c
 *
 * Created: 27-2-2019 14:59:23
 *  Author: Aspire V3-772G-747a8
 */ 

#define F_CPU 8000000L

#include <stdio.h>
#include <avr/io.h>
#include <avr/delay.h>

#include "../hardware/EasyBuzz.h"

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
	
	TCCR3B |= ((1 << CS10) | (1 << CS11));
	
	//Tracks millisecond loops
	millisCounter = 0;
	
	SpawnNewBlock();
	
	
	DrawReadyScreen();
	_delay_ms(3000);
	DrawGoScreen();
	
	
	while (GetState() == STATE_GAME)
	{
			
		
		if(TCNT3 >= MILLISEC){
			TCNT3 = 0;
			millisCounter += 1;
			easybuzz_update();
		}
		
		if(millisCounter % 200 != 0){
			continue;
		}
		
		//DrawScore(GetScore());
		DrawField(GetField(), GetPlayer());
		

		CheckForInput();
		//AiInput();
		UpdatePlayer();

		if (millisCounter >= 1000)
		{
			MoveDown();
			millisCounter = 0;
			TCNT3 = 0;
			
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

	InitPlayer(2, 0, GetSeed() % 7);
	
	//If the newly spawned player block is overlapping with the blocks filling the field
	// then set the state to GameOver
	if (IsOverlapping(GetField(), GetPlayer()) == 0) {

		CheckIfHighScore();
		SetState(STATE_GAMEOVER);
	}
	
}


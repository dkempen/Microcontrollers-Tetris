/*
 * Player.c
 *
 * Created: 27-2-2019 15:00:22
 *  Author: Ian
 */ 

#include "Player.h"
#include "Collision.h"
#include "Field.h"
#include "Blocks.h"
#include "Game.h"
#include "InputHandler.h"
#include "Matrix.h"

Player player;

//Whether the previous move was rotating
//Makes sure the block doesn't rotate multiple times in a row
int previouslyRotated;

void InitPlayer(int startx, int starty, int block)
{
	player.x = startx;
	player.y = starty;
	player.block = GetBlock(block);
	previouslyRotated = -1;
}

void UpdatePlayer(void)
{
	int prevx = player.x;
	int prevy = player.y;
	Block prevBlock = player.block;


	switch (GetCurrentInput()) {
		case MOVE_LEFT:
		player.x -= 1;
		previouslyRotated = -1;
		break;
		
		case MOVE_RIGHT:
		player.x += 1;
		previouslyRotated = -1;
		break;
		
		case TURN_LEFT:
		if(previouslyRotated == -1){
			Rotate(&player, 1);
			previouslyRotated = 0;
		}
		break;
		
		case TURN_RIGHT:
		if(previouslyRotated == -1){
			Rotate(&player, 0);
			previouslyRotated = 0;
		}
		break;
		
		case MOVE_DOWN:
		player.y += 1;
		previouslyRotated = -1;
		break;
		
		case IDLE:
		previouslyRotated = -1;
		break;
	}
	
	ResetInput();

	if (IsOutOfBounds(player) == 0) {
		player.x = prevx;
		player.block = prevBlock;
	}
	else {
		//If the player is colliding with the terrain (excluding the invisible walls),
		if (IsOverlapping(GetField(), player) == 0) {
			//Set player back, but dont spawn new block
			player.x = prevx;
			player.y = prevy;
			player.block = prevBlock;
		}
	}
}

void MoveDown(void)
{
	int prevx = player.x;
	int prevy = player.y;

	player.y += 1;

	if (IsOverlapping(GetField(), player) == 0) {
		//Set player back AND spawn new block
		player.x = prevx;
		player.y = prevy;
		AddPlayerToField(player);
		SpawnNewBlock();
	}
}


Player GetPlayer(void)
{
	return player;
}

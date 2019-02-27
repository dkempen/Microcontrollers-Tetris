/*
 * Draw.c
 *
 * Created: 27-2-2019 14:58:17
 *  Author: Aspire V3-772G-747a8
 */ 

#include "Draw.h"
#include <stdio.h>

void DrawMenu(void)
{
	//TODO: Use lcd display
	
	printf("Tetris\n\n");
	printf("Press w to play, press s to exit\n\n");
	printf("Press x to view the highscores\n");
}

void DrawScore(int score)
{
	//TODO: Use 7 segment display
	printf("Score: %i\n", score);
}

void DrawField(int field[FIELD_WIDTH][FIELD_LENGTH], Player player)
{
	//TODO: Use dotmatrix display
	
	int tempField[FIELD_WIDTH][FIELD_LENGTH];

	//Fill field with values from the original field
	for (int x = 0; x < FIELD_WIDTH; x++) {
		for (int y = 0; y < FIELD_LENGTH; y++) {
			tempField[x][y] = field[x][y];
		}
	}
	//Insert the tiles occupied by the player into the field that will be drawn
	for (int y = 0; y < BLOCK_STORE_SIZE; y++) {
		for (int x = 0; x < BLOCK_STORE_SIZE; x++) {

			if (player.block.tiles[y][x] == 1)
			tempField[player.x + x][player.y + y] = 1;

		}
	}

	
	//Draw the field
	for (int y = 0; y < FIELD_LENGTH; y++) {
		for (int x = 0; x < FIELD_WIDTH; x++) {

			//Mark tiles that are the bottom, or occupied by previously placed blocks
			if (tempField[x][y] == 1)
			printf("x");

			//The rest of the field does not get marked
			else
			printf(" ");
		}
		printf("\n");
	}
}

void DrawGameOverScreen(int score, int isHighScore)
{
	//TODO: Use lcd display
	
	printf("Game Over!\n\n");

	printf("Your score: %i\n\n", score);

	if (isHighScore == 0)
	printf("New Highscore!\n\n");

	printf("Press a to go again, press d to return to menu\n\n");
}

void DrawHighScoresScreen(int * highscores, int amount)
{
	//TODO: Use lcd display
	
	printf("High Scores\n\n");

	for (int i = 0; i < amount; i++) {
		printf("%i. %i\n", (i + 1), highscores[i]);
	}

	printf("\nPress z to return to the menu screen\n");
}

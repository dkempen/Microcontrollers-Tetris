/*
 * Draw.c
 *
 * Created: 27-2-2019 14:58:17
 *  Author: Ian
 */ 

#include <stdio.h>
#include <string.h>

#include "../hardware/DotMatrix.h"
#include "../hardware/SegDisplay.h"
#include "../hardware/lcd.h"

#include "Draw.h"

void DrawMenu(void)
{
	lcd_set_cursor(0);
	lcd_write_string("Tetris    play >");
	lcd_set_cursor(16);
	lcd_write_string("        scores v");
}

void DrawScore(int score)
{		
	SegDisplay_writeLedScore(score);
}

void DrawField(int field[FIELD_WIDTH][FIELD_LENGTH], Player player)
{	
	int tempField[FIELD_WIDTH][FIELD_LENGTH-1];

	//Fill field with values from the original field
	for (int x = 0; x < FIELD_WIDTH; x++) {
		for (int y = 0; y < FIELD_LENGTH-1; y++) {
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

	matrix_draw_game_field(tempField);	
}

void DrawFieldWithoutPlayer(int field[FIELD_WIDTH][FIELD_LENGTH])
{
	int tempField[FIELD_WIDTH][FIELD_LENGTH-1];

	//Fill field with values from the original field
	for (int x = 0; x < FIELD_WIDTH; x++) {
		for (int y = 0; y < FIELD_LENGTH-1; y++) {
			tempField[x][y] = field[x][y];
		}
	}
	
	matrix_draw_game_field(tempField);	
}

void DrawGameOverScreen(int score, int isHighScore)
{
	lcd_set_cursor(0);
	
	char line1[16];
	sprintf(line1, "Your score: %04i", score);
	
	lcd_write_string(line1);
	lcd_set_cursor(16);
	lcd_write_string("v menu          ");
	
	if (isHighScore == 0){
		lcd_set_cursor(16);
		lcd_write_string("v menu   new HS!");
	}	
}

void DrawHighScoresScreen(int * highscores, int currentScore)
{
	
	lcd_set_cursor(0);
	lcd_write_string("Scores    menu v");
	lcd_set_cursor(16);
	
	
	char line2[16];
	sprintf(line2, "  %i. %04i >     ",currentScore+1,highscores[currentScore]);
		
	lcd_write_string(line2);	
}

void DrawReadyScreen(){
	
	lcd_set_cursor(0);
	lcd_write_string("  Get ready...  ");
	lcd_set_cursor(16);
	lcd_write_string("                ");
	
}

void DrawGoScreen(){

	lcd_set_cursor(0);
	lcd_write_string("      Go!       ");
	lcd_set_cursor(16);
	lcd_write_string("                ");	
}
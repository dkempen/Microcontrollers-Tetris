/*
 * Draw.h
 *
 * Created: 27-2-2019 15:01:25
 *  Author: Aspire V3-772G-747a8
 */ 


#ifndef DRAW_H_
#define DRAW_H_

#include "Player.h"
#include "Field.h"

/*
	Draws the menu
*/
void DrawMenu(void);

/*
	Draws the score
*/
void DrawScore(int score);

/*
	Draws the field
*/
void DrawField(int field[FIELD_WIDTH][FIELD_LENGTH], Player player);

/*
	Draws the game over screen
*/
void DrawGameOverScreen(int score, int isHighScore);

/*
	Draws the high score screen	
*/
void DrawHighScoresScreen(int *highscores, int currentScore);

/*
	Tells the player that the game is about to start
*/
void DrawReadyScreen();

/*
	Tells the player that the game has started
*/
void DrawGoScreen();


#endif /* DRAW_H_ */
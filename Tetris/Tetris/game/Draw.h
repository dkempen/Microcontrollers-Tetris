/*
 * Draw.h
 *
 * Created: 27-2-2019 15:01:25
 *  Author: Ian
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
	Draws the current score
	
	@param score - The current score
*/
void DrawScore(int score);

/*
	Draws the field
	
	@param field - The current game field
	@param player - The player object
*/
void DrawField(int field[FIELD_WIDTH][FIELD_LENGTH], Player player);

/*
	Draws the field without the player
	
	@param field - The current game field
*/
void DrawFieldWithoutPlayer(int field[FIELD_WIDTH][FIELD_LENGTH]);

/*
	Draws the game over screen
	
	@param score - The current score
	@param isHighScore - Whether the score is a high score. High score is 0, otherwise -1
*/
void DrawGameOverScreen(int score, int isHighScore);

/*
	Draws the high score screen	
	
	@param highscores - The current high scores
	@param currentScore - The current score
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
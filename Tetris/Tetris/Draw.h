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

void DrawMenu(void);

void DrawScore(int score);
void DrawField(int field[FIELD_WIDTH][FIELD_LENGTH], Player player);

void DrawGameOverScreen(int score, int isHighScore);

void DrawHighScoresScreen(int *highscores, int amount);



#endif /* DRAW_H_ */
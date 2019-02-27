/*
 * Score.c
 *
 * Created: 27-2-2019 15:00:33
 *  Author: Aspire V3-772G-747a8
 */ 

#include "Score.h"


int score;
int highScores[MAX_AMOUNT_OF_HIGHSCORES];

int isHighScore;

void InitScore(void)
{
	score = 0;
	isHighScore = -1;
}

void InitHighScores(void)
{
	for (int i = 0; i < MAX_AMOUNT_OF_HIGHSCORES; i++)
	highScores[i] = 0;
}

void IncreaseScore(int amount)
{
	score += amount;
}

void CheckIfHighScore(void)
{
	for (int i = 0; i < MAX_AMOUNT_OF_HIGHSCORES; i++) {
		if (score > highScores[i]) {
			isHighScore = 0;
			SetAsHighScore(i);
			break;
		}
	}
}

void SetAsHighScore(int pos)
{
	//-1 Because the values are moved down the list
	//Going over the last element would cause it to go out of bounds
	for (int i = MAX_AMOUNT_OF_HIGHSCORES-1; i > pos; i--) {
		highScores[i] = highScores[i-1];
	}

	highScores[pos] = score;
}

int GetScore(void)
{
	return score;
}

int * GetHighScores(void)
{
	return highScores;
}

int IsHighScore(void)
{
	return isHighScore;
}
/*
 * Score.h
 *
 * Created: 27-2-2019 15:02:27
 *  Author: Aspire V3-772G-747a8
 */ 


#ifndef SCORE_H_
#define SCORE_H_

#define MAX_AMOUNT_OF_HIGHSCORES 5

void InitScore(void);
void InitHighScores(void);

void IncreaseScore(int amount);
void CheckIfHighScore(void);
void SetAsHighScore(int pos);

/*
	Used by the Eeprom to set the highscores in non-volatile memory
	
	@param highscores - The highscores in non-volatile memory
*/
void SetHighScores(int *highscores);

int GetScore(void);
int *GetHighScores(void);

/*
Whether the current score is a high score
	Returns 0 if true
	Returns -1 if false
*/
int IsHighScore(void);



#endif /* SCORE_H_ */
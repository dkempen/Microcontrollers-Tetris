/*
 * Score.h
 *
 * Created: 27-2-2019 15:02:27
 *  Author: Ian
 */ 


#ifndef SCORE_H_
#define SCORE_H_

#define MAX_AMOUNT_OF_HIGHSCORES 5

/*
	Initializes the score 
	Should be called when a new game is started
*/
void InitScore(void);

/*
	Reads the highscores from non-volatile memory (Eeprom)
	
*/
void InitHighScores(void);

/*
	Increases the score by a given amount
	
	@param amount - The amount to increase the score by
*/
void IncreaseScore(int amount);

/*
	Checks if the current score is a high score
*/
void CheckIfHighScore(void);

/*
	Puts the current score into the list of high scores at a given position
	And moves the lower scores one position down
	
	@param pos - The new position in the high score list of the current score
*/
void SetAsHighScore(int pos);

/*
	Used by the Eeprom to set the highscores in non-volatile memory
	
	@param highscores - The highscores in non-volatile memory
*/
void SetHighScores(int *highscores);

/*
	Returns the current score
*/
int GetScore(void);

/*
	Returns the current highscores
*/
int *GetHighScores(void);

/*
	Whether the current score is a high score

	Returns 0 if true
	Returns -1 if false
*/
int IsHighScore(void);



#endif /* SCORE_H_ */
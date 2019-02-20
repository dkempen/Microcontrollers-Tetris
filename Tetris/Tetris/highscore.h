
/*
 * highscore.h
 *
 * Created: 20-2-2019 15:52:57
 *  Author: Jordy van Raalte
 */ 
#include <avr/io.h>



void saveScoreIfHighest(int score);
int getHighscore();
int getHighscoreFromEeprom();


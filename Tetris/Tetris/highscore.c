
/*
 * highscore.c
 *
 * Created: 20-2-2019 15:52:06
 *  Author: Jordy van Raalte
 */ 
static 

#include <avr/io.h>
#include "lcd.h"
#include "eeprom.h"
#include "highscore.h"

static int highscore = 0;

void init() {
	highscore = getHighscoreFromEeprom();
}

void saveScoreIfHighest(int score) {
	if(score > highscore){
		writeHighScore(score);
	}
}

int getHighscore() {
	return highscore;
}

int getHighscoreFromEeprom() {
	return readHighScore();
}
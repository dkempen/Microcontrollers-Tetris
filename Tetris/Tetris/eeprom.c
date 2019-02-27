
/*
 * eeprom.c
 * Writes data to the eeprom memory
 * Created: 20-2-2019 14:32:40
 *  Author: User
 */ 

//includes
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/eeprom.h>
#include "eeprom.h"

//defines
#define HIGHSCORE_ADRESS 0011;

void eeprom_writeHighScore(int score) {
	cli();
	//hex 0011 == 17 decimal
	eeprom_update_byte((uint8_t*) 0011, score);
	sei();
}

int eeprom_readHighScore() {
	cli();
	//hex 0011 == 17 decimal
	int score = eeprom_read_byte((uint8_t*) 0011);
	sei();
	return score;
}


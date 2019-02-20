
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
#include <stdint.h>
#include "eeprom.h"

//defines

void writeHighScore(uint8_t score) {
	cli();
	eeprom_update_byte((uint8_t*)17,score);
	sei();
}

int readHighScore() {
	cli();
	uint8_t score = eeprom_read_byte((uint8_t*)17);
	sei();
	return score;
}


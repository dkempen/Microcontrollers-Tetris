/*
 * Eeprom.c
 *
 * Created: 20-3-2019 12:56:33
 *  Author: Aspire V3-772G-747a8
 */ 


#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/eeprom.h>

#include "Eeprom.h"


void WriteHighScore(uint8_t address, int score) {
	//To prevent interrupts from disrupting the reading/writing process
	cli();	
	eeprom_update_byte((uint8_t*) address, score);
	sei();
}

int ReadHighScore(uint8_t address) {
	//To prevent interrupts from disrupting the reading/writing process
	cli();
	int score = eeprom_read_byte((uint8_t*) address);
	sei();
	return score;
}

void WriteHighScores(int *highScores, int size)
{
	for(int i = 0; i < size; i++){
		WriteHighScore(0x11 + (1*i) , highScores[i]);
	}	
}

void ReadHighScores(int *highScores, int size)
{
	for(int i = 0; i < size; i++){
		highScores[i] = ReadHighScore(0x11 + (1*i));		
	}
}
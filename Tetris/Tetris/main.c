/*
 * Tetris.c
 *
 * Created: 20-Feb-19 13:50:34
 * Author : Daan, Ian, Max, Jordy
 */ 

#define F_CPU 8000000L

#include <avr/io.h>
#include "lcd.h"
#include "eeprom.h"


int main(void)
{	
	lcd_init();
	lcd_set_cursor(0);
	writeHighScore(12);
	
	int score = readHighScore();
    while (1) 
    {
    }
}

/*
 * Tetris.c
 *
 * Created: 20-Feb-19 13:50:34
 * Author : Daan, Ian, Max, Jordy
 */ 

#include <avr/io.h>
#include <stdint.h>


int main(void)
{
	uint8_t score = 3;
	writeHighScore(score);
	
	uint8_t score1 = readHighScore();
    while (1) 
    {
    }
}

/*
 * Tetris.c
 *
 * Created: 20-Feb-19 13:50:34
 * Author : Daan, Ian, Max
 */ 

#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "hardware/EasyBuzz.h"
#include "hardware/DotMatrix.h"
#include "hardware/SegDisplay.h"
#include "hardware/lcd.h"

#include "util/Random.h"

#include "game/StateManager.h"
#include "game/Menu.h"
#include "game/Draw.h"



int main(void)
{	
	//Hardware
	SegDisplay_Init();
	lcd_init();
	matrix_init();
	
	lcd_write_line1("Tetris          ");
	lcd_write_line2("Press x to play ");
		
	//Util
	InitRandom();
		
	//Game
	InitStateManager();
    InitMenu();
	
		
		
	
    /* Replace with your application code */	    
	while (1) 
    {
    }
	
	
}

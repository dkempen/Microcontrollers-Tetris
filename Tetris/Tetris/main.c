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

#include "hardware/DotMatrix.h"
#include "hardware/SegDisplay.h"
#include "hardware/Button.h"
#include "hardware/lcd.h"
#include "hardware/EasyBuzz.h"

#include "util/Random.h"

#include "game/StateManager.h"
#include "game/Menu.h"
#include "game/Draw.h"



int main(void)
{	
	//Hardware
	SegDisplay_Init();
	matrix_init();
	Button_Init();
	lcd_init();
	easybuzz_init();
		
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

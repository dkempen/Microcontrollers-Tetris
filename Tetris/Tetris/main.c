/*
 * Tetris.c
 *
 * Created: 20-Feb-19 13:50:34
 * Author : Daan, Ian, Max
 */ 

#include <avr/io.h>

#include "hardware/EasyBuzz.h"
#include "hardware/DotMatrix.h"
#include "hardware/SegDisplay.h"
#include "hardware/Button.h"

#include "util/Random.h"

#include "game/StateManager.h"
#include "game/Menu.h"

#define F_CPU 8000000L

int main(void)
{	
	//Hardware
	SegDisplay_Init();
	Button_Init();
	matrix_init();
	
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

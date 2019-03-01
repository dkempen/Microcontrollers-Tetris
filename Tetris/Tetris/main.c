/*
 * Tetris.c
 *
 * Created: 20-Feb-19 13:50:34
 * Author : Daan, Ian, Max, Jordy
 */ 

#include <avr/io.h>

#include "hardware/DotMatrix.h"

#include "game/StateManager.h"
#include "game/Menu.h"

#define F_CPU 8000000L

int main(void)
{
    InitStateManager();
    InitMenu();
	//matrix_test();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

/*
 * Tetris.c
 *
 * Created: 20-Feb-19 13:50:34
 * Author : Daan, Ian, Max, Jordy
 */ 

#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "hardware/EasyBuzz.h"
#include "hardware/DotMatrix.h"
#include "hardware/lcd.h"


#include "game/StateManager.h"
#include "game/Menu.h"
#include "game/Draw.h"



int main(void)
{
    //InitStateManager();
    //InitMenu();
	//matrix_test();
	
	lcd_init();
	
	lcd_clear();
	lcd_set_cursor(0);
	lcd_write_data('a');
    /* Replace with your application code */
	
    while (1) 
    {
    }
}

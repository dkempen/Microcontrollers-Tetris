/*
 * Tetris.c
 *
 * Created: 20-Feb-19 13:50:34
 * Author : Daan, Ian, Max, Jordy
 */ 

#include <avr/io.h>

#include "game/StateManager.h"
#include "game/Menu.h"

int main(void)
{
   InitStateManager();

   InitMenu();
}

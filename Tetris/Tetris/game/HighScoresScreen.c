/*
 * HighScoreScreen.c
 *
 * Created: 27-2-2019 14:59:41
 *  Author: Aspire V3-772G-747a8
 */ 

#define F_CPU 8000000L

#include <avr/delay.h>

#include "../hardware/Button.h"
#include "../hardware/EasyBuzz.h"

#include "StateManager.h"
#include "HighScoresScreen.h"
#include "Menu.h"

#include "Draw.h"
#include "Score.h"

int currentElement;

void InitHighScoresScreen(void)
{
	currentElement = 0;
	RunHighScoresScreen();
}

void RunHighScoresScreen(void)
{
	DrawHighScoresScreen(GetHighScores(), currentElement);
	
	//Prevents key presses in another screen from affecting the current screen
	_delay_ms(1000);

	while (GetState() == STATE_HIGHSCORES) {
		
		easybuzz_update();
		_delay_ms(1);

		char input = Button_GetInput();

		if (input == 's')
			SetState(STATE_MENU);
		else if (input == 'd'){	
			
			currentElement ++;	
			if(currentElement >= MAX_AMOUNT_OF_HIGHSCORES)
				currentElement = 0;	
				
		    DrawHighScoresScreen(GetHighScores(), currentElement);	
			
			int counter = 0;
			while(counter < 500){
				easybuzz_update();
				_delay_ms(1);	
			counter++;
			}	
			
		}
	
	
	}

	if (GetState() == STATE_MENU)
	RunMenu();
}

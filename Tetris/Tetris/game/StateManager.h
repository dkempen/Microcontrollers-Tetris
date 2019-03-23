/*
 * StateManager.h
 *
 * Created: 27-2-2019 15:03:11
 *  Author: Ian
 */ 


#ifndef STATEMANAGER_H_
#define STATEMANAGER_H_

/*
	The states the game can have
*/
enum States { STATE_MENU, STATE_GAME, STATE_GAMEOVER, STATE_HIGHSCORES};

/*
	Initializes the state manager
*/
void InitStateManager(void);

/*
	Sets the current state to a given value
	
	@param state - the given state
*/
void SetState(int state);

/*
	Returns the current state
*/
int GetState();



#endif /* STATEMANAGER_H_ */
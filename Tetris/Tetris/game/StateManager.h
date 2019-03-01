/*
 * StateManager.h
 *
 * Created: 27-2-2019 15:03:11
 *  Author: Aspire V3-772G-747a8
 */ 


#ifndef STATEMANAGER_H_
#define STATEMANAGER_H_

enum States { STATE_MENU, STATE_GAME, STATE_GAMEOVER, STATE_HIGHSCORES, STATE_EXIT };

void InitStateManager(void);

void SetState(int state);
int GetState();



#endif /* STATEMANAGER_H_ */
/*
 * InputHandler.h
 *
 * Created: 27-2-2019 15:02:12
 *  Author: Aspire V3-772G-747a8
 */ 


#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

/*
Controls all player input
*/

enum Inputs {IDLE, MOVE_LEFT, MOVE_RIGHT, MOVE_DOWN, TURN_LEFT, TURN_RIGHT};


void CheckForInput(void);
void AiInput(void);
int GetCurrentInput(void);



#endif /* INPUTHANDLER_H_ */
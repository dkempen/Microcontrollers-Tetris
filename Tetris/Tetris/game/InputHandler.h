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

/*
	Checks for key presses
*/
void CheckForInput(void);

/*
	Returns random inputs 
*/
void AiInput(void);

/*
	Returns the current input
*/
int GetCurrentInput(void);

/*
	Sets the current input back to IDLE
*/
void ResetInput(void);


#endif /* INPUTHANDLER_H_ */
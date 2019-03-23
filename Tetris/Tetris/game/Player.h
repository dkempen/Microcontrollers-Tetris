/*
 * Player.h
 *
 * Created: 27-2-2019 15:02:37
 *  Author: Ian
 */ 


#ifndef PLAYER_H_
#define PLAYER_H_

#include "Blocks.h"

typedef struct {
	int x;
	int y;
	Block block;

} Player;


/*
	Initializes the player object
	
	@param int - The starting x position
	@param int - The starting y position
	@param int - The index of the block
*/
void InitPlayer(int,int,int);

/*
	Updates the player object
*/
void UpdatePlayer(void);

/*
	Moves the player block down 1 row
	Should be called at a consistent rate
*/
void MoveDown(void);

/*
	Returns the player object
*/
Player GetPlayer(void);



#endif /* PLAYER_H_ */
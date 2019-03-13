/*
 * Player.h
 *
 * Created: 27-2-2019 15:02:37
 *  Author: Aspire V3-772G-747a8
 */ 


#ifndef PLAYER_H_
#define PLAYER_H_

#include "Blocks.h"

typedef struct {
	int x;
	int y;
	Block block;

} Player;

void InitPlayer(int,int,int);
void UpdatePlayer(void);

/*
The player block moves down at a constant rate
No matter the input, this rate of dropping is maintained

@param seed - The value for seeding the block spawner
*/
void MoveDown(void);

Player GetPlayer(void);



#endif /* PLAYER_H_ */
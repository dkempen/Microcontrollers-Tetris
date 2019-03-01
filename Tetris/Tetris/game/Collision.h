/*
 * Collision.h
 *
 * Created: 27-2-2019 15:01:16
 *  Author: Aspire V3-772G-747a8
 */ 


#ifndef COLLISION_H_
#define COLLISION_H_

#include "Field.h"
#include "Player.h"

/*
Checks if the player is overlapping with any already occupied tiles on the map

	@param field - The playing field
	@param player - The player object

	returns 0 if overlapping
	returns -1 otherwise

*/
int IsOverlapping(int field[FIELD_WIDTH][FIELD_LENGTH], Player player);

/*
Checks if the player is moving outside of the playing field

	@param player - The player object

	returns 0 if oob
	returns -1 otherwise
*/
int IsOutOfBounds(Player player);



#endif /* COLLISION_H_ */
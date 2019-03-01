/*
 * Field.h
 *
 * Created: 27-2-2019 15:01:32
 *  Author: Aspire V3-772G-747a8
 */ 


#ifndef FIELD_H_
#define FIELD_H_

#include "Player.h"

#define FIELD_WIDTH 10
#define FIELD_LENGTH 16

void InitField(void);

/*
	Adds the tiles occupied by the player to the field
	Is called after the player block touches already occupied tiles

	@param player - The player object
*/
void AddPlayerToField(Player player);



/*
Checks if a row is filled with blocks.

*/
void CheckForFullRow(void);

/*
Removes a row from the field and moves the rows above it 1 row down

	@param row - The row that is to be removed

*/
void RemoveRow(int row);

int** GetField(void);



#endif /* FIELD_H_ */
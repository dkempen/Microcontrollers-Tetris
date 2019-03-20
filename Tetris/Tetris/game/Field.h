/*
 * Field.h
 *
 * Created: 27-2-2019 15:01:32
 *  Author: Aspire V3-772G-747a8
 */ 


#ifndef FIELD_H_
#define FIELD_H_

#include "Player.h"

#define FIELD_WIDTH 8
#define FIELD_LENGTH 17 //Last row is for collision

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

/*
	Returns the game field
*/
int** GetField(void);

/*
	Returns the amount of rows that have been removed in one play session
*/
int GetRowsRemoved(void);


#endif /* FIELD_H_ */
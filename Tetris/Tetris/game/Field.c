/*
 * Field.c
 *
 * Created: 27-2-2019 14:58:27
 *  Author: Aspire V3-772G-747a8
 */ 

#include "Field.h"
#include "Score.h"

#include "../hardware/EasyBuzz.h"

#define POINTS_PER_ROW 1

int field[FIELD_WIDTH][FIELD_LENGTH];

void InitField(void)
{
	for (int x = 0; x < FIELD_WIDTH; x++) {
		for (int y = 0; y < FIELD_LENGTH; y++) {
			field[x][y] = 0;

			//Fill the bottom row with 1 (so it will check for collision)
			if (y == FIELD_LENGTH-1)
			field[x][y] = 1;
		}

	}
}

void AddPlayerToField(Player player)
{
	//For all block spaces
	for (int x = 0; x < BLOCK_STORE_SIZE; x++) {
		for (int y = 0; y < BLOCK_STORE_SIZE; y++) {

			//If it's occupied
			if (player.block.tiles[y][x] == 1) {

				//Set tile in field as occupied
				field[player.x + x][player.y + y] = 1;

			}

		}
	}
}

void CheckForFullRow(void)
{
	int amountOfRowsRemoved = 0;

	//Does starts at the top and works its way down.
	//This way, removing a row does not interfere with removing another (because the index of the full rows doesn't change)
	//If it started from the bottom, then another full row would move down, which would cause it to be skipped
	//-1, Because the last row is the bottom of the field, this has to be preserved
	for (int y = 0; y < FIELD_LENGTH-1; y++) {
		
		int amountFilled = 0;
		for (int x = 0; x < FIELD_WIDTH; x++) {
			//If the tile is occupied, add to the counter
			if (field[x][y] == 1)
			amountFilled++;
		}
		//Removes the row that is full
		if (amountFilled == FIELD_WIDTH) {
			RemoveRow(y);
			
			easybuzz_play_effect(EFFECT_CLEAR);
			
			//Score increases multiplicatively per row removed
			//This incentivises taking out multiple rows at once
			amountOfRowsRemoved++;
			IncreaseScore(POINTS_PER_ROW * amountOfRowsRemoved);
		}
		
	}
}

void RemoveRow(int row)
{
	//All rows that are above the to be removed row
	//row 0 gets an empty row, so that is a special case
	for (int y = row; y > 1; y--) {
		for (int x = 0; x < FIELD_WIDTH; x++) {
			field[x][y] = field[x][y - 1];
		}
	}

	//Row 0
	for (int x = 0; x < FIELD_WIDTH; x++) {
		field[x][0] = 0;
	}
}

int ** GetField(void)
{
	return field;
}

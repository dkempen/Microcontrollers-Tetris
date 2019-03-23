/*
 * Collision.c
 *
 * Created: 27-2-2019 14:58:08
 *  Author: Ian
 */ 

#include "Collision.h"

int IsOverlapping(int field[FIELD_WIDTH][FIELD_LENGTH], Player player)
{
	//Checks if the player is overlapping an occupied block in the field
	for (int x = 0; x < BLOCK_STORE_SIZE; x++) {
		for (int y = 0; y < BLOCK_STORE_SIZE; y++) {
			if (player.block.tiles[y][x] == 1) {
				if (field[player.x + x][player.y + y] == 1)
				return 0;
			}
		}
	}
	return -1;
}

int IsOutOfBounds(Player player)
{
	//For all block spaces
	for (int x = 0; x < BLOCK_STORE_SIZE; x++) {
		for (int y = 0; y < BLOCK_STORE_SIZE; y++) {

			//If it's occupied
			if (player.block.tiles[y][x] == 1) {

				//Check if it is out of bounds
				if (player.x + x >= FIELD_WIDTH || player.x + x < 0)
				return 0;
			}
		}
	}
	return -1;
}

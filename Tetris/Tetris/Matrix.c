/*
 * Matrix.c
 *
 * Created: 27-2-2019 15:00:02
 *  Author: Aspire V3-772G-747a8
 */ 

#include "Matrix.h"

void **Rotate(Player *player, int direction)
{
	int newMatrix[4][4];
	Block tempBlock = player->block;
	for (int y = 0; y < BLOCK_STORE_SIZE; y++) {
		for (int x = 0; x < BLOCK_STORE_SIZE; x++) {

			//Rotate 90 degrees to the left
			if (direction == 1)
			newMatrix[y][x] = tempBlock.tiles[x][(BLOCK_STORE_SIZE - 1) - y];
			else
			//Rotates 90 degrees to the right
			newMatrix[y][x] = tempBlock.tiles[(BLOCK_STORE_SIZE - 1) - x][y];
		}
	}

	for (int y = 0; y < BLOCK_STORE_SIZE; y++) {
		for (int x = 0; x < BLOCK_STORE_SIZE; x++) {

			player->block.tiles[y][x] = newMatrix[y][x];
		}
	}
}

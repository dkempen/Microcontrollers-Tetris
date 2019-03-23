/*
 * Blocks.h
 *
 * Created: 27-2-2019 15:01:07
 *  Author: Ian
 */ 


#ifndef BLOCKS_H_
#define BLOCKS_H_


#define BLOCK_STORE_SIZE 4

/*
	The tiles are spaces that will become the shape through 1s and 0s
*/
typedef struct {
	//NOTE: Blocks are stored in [y][x] format, due to defining them row by row
	int tiles[BLOCK_STORE_SIZE][BLOCK_STORE_SIZE];

} Block;

/*
	Initializes the blocks 
*/
void InitBlocks(void);

/*
	Returns the block with the given index
	
	@param index - The index of the block
*/
Block GetBlock(int index);



#endif /* BLOCKS_H_ */
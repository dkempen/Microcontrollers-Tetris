/*
 * Blocks.h
 *
 * Created: 27-2-2019 15:01:07
 *  Author: Aspire V3-772G-747a8
 */ 


#ifndef BLOCKS_H_
#define BLOCKS_H_


#define BLOCK_STORE_SIZE 4


typedef struct {
	//NOTE: Blocks are stored in [y][x] format, due to defining them row by row
	int tiles[BLOCK_STORE_SIZE][BLOCK_STORE_SIZE];

} Block;


void InitBlocks(void);
Block GetBlock(int index);



#endif /* BLOCKS_H_ */
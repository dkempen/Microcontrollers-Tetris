/*
 * Blocks.c
 *
 * Created: 27-2-2019 14:57:48
 *  Author: Aspire V3-772G-747a8
 */ 

#include "Blocks.h"



Block blocks[7];

void InitBlocks(void)
{
	// Block 1
	Block block1 ={
	  { {0,0,0,0},
		{1,1,1,1},
		{0,0,0,0},
		{0,0,0,0}
	} };
	blocks[0] = block1;

	//Block 2
	Block block2 = {
	  { {0,0,0,0},
		{1,1,1,0},
		{0,0,1,0},
		{0,0,0,0}
	} };
	blocks[1] = block2;
	
	//Block 3
	Block block3 = {
	  { {0,0,0,0},
		{0,1,1,1},
		{0,1,0,0},
		{0,0,0,0}
	} };
	blocks[2] = block3;

	//Block 4
	Block block4 = {
	  { {0,0,0,0},
		{0,1,1,0},
		{1,1,0,0},
		{0,0,0,0}
	} };
	blocks[3] = block4;

	//Block 5
	Block block5 = {
	  { {0,0,0,0},
		{0,1,1,0},
		{0,0,1,1},
		{0,0,0,0}
	} };
	blocks[4] = block5;

	//Block 6
	Block block6 = {
	  { {0,0,0,0},
		{1,1,1,0},
		{0,1,0,0},
		{0,0,0,0}
	} };
	blocks[5] = block6;

	//Block 7
	Block block7 = {
	  { {0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	} };
	blocks[6] = block7;
}

Block GetBlock(int index)
{
	return blocks[index];
}
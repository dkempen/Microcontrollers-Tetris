/*
 * Game.h
 *
 * Created: 27-2-2019 15:01:41
 *  Author: Aspire V3-772G-747a8
 */ 


#ifndef GAME_H_
#define GAME_H_

/*
	Holds the game logic, 
	like resetting the player block after a collision
*/

void InitGame(void);

void RunGame(void);

/*
Spawns a new, random block
*/
void SpawnNewBlock(void);



#endif /* GAME_H_ */
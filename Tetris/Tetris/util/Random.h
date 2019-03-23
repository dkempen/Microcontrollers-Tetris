/*
 * Random.h
 *
 * Created: 13-3-2019 19:00:37
 *  Author: Ian
 */ 


#ifndef RANDOM_H_
#define RANDOM_H_


/*
	Initializes the timer that will provide the seeds
*/
void InitRandom(void);

/*
	Returns the current seed
*/
int GetSeed(void);




#endif /* RANDOM_H_ */
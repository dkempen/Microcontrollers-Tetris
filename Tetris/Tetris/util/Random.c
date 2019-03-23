/*
 * Random.c
 *
 * Created: 13-3-2019 19:00:28
 *  Author: Ian
 */ 

#include "Random.h"
#include "avr/io.h"




void InitRandom(){
	TCCR0 |= ((1 << CS10) | (1 << CS11));
}

int GetSeed(){
	return TCNT0;
}

/*
 * EasyBuzz.h
 *
 * Created: 27-Feb-19 11:06:39
 * Author: Daan
 */ 

#ifndef EASYBUZZ_H_
#define EASYBUZZ_H_

// Defines for identifying the song that needs to be played
#define SONG_TEST	0
#define SONG_TETRIS	1

// Struct that holds a note (frequency and length)
typedef struct
{
	double frequency;	// The frequency in ms of the note
	double length;		// length is defined as a multiplier value based on the length of a quarter note as value 1
} note_struct;

void easybuzz_init(void);
void easybuzz_update(void);
void easybuzz_play_loop(int);
void easybuzz_play_effect(int);
void easybuzz_stop_loop(void);
void easybuzz_test(void);

#endif /* EASYBUZZ_H_ */

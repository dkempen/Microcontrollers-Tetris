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
//#define SONG_TETRIS	1

void easybuzz_init(void);
void easybuzz_test(void);
void easybuzz_play(int);
void easybuzz_stop(void);

#endif /* EASYBUZZ_H_ */

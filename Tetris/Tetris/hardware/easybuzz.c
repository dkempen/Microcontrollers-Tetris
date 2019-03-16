/*
 * EasyBuzz.c
 *
 * Created: 27-Feb-19 11:05:13
 * Author: Daan
 */

#define F_CPU 8000000L

// Ignore pragma warnings, because Atmel doesn't like code regions for some reason
#pragma GCC diagnostic ignored "-Wunknown-pragmas"

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "EasyBuzz.h"
#include "../util/LinkedList.h"

#pragma region defines
// Defines for array lengths
#define SONG_COUNT		2

#define SCALE_LENGTH	12
#define SCALE_COUNT		4

// Note lengths
#define FULL			4.0
#define HALF_DOT		3.0
#define HALF			2.0
#define QUARTER_DOT		1.5
#define QUARTER			1.0
#define EIGHTH_DOT		0.75
#define EIGHTH			0.5
#define SIXTEENTH_DOT	0.375
#define SIXTEENTH		0.25

#define NOTE_WAIT		20	// Amount of ms that all notes get shortened by to seperate the notes

// Notes (as in the placement in the array)
#define C	0
#define Cs	1
#define D	2
#define Ds	3
#define E	4
#define F	5
#define Fs	6
#define G	7
#define Gs	8
#define A	9
#define As	10
#define B	11

// Scales (as in the placement in the array)
#define S4	0
#define S5	1
#define S6	2
#define S7	3

// Note struct is defined in the header for access by the LinkedList

// Struct that holds a song (bpm and a note linked list (the pointer to the head))
typedef struct
{
	int bpm;
	node *first_note; // Head of the linked list
} song_struct;

// This 2d array holds the tone frequencies for each note in lists of scales
int scales[SCALE_COUNT][SCALE_LENGTH] =
{ // C	  Cs   D	Ds	 E	  F	   Fs	G	 Gs	  A	   As	B
	{262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494 },	// Scale 4
	{523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988 },	// Scale 5
	{1046,1108,1174,1244,1318,1397,1480,1568,1662,1760,1865,1975},	// Scale 6
	{2093,2217,2349,2489,2637,2794,2960,3136,3322,3520,3729,3951}	// Scale 7
};

int rest = 0;	// Is used for a rest in a song, is called the same way as a normal note with &rest

// Song array that holds all the playable songs in song structs (called by index from defines in the header file)
song_struct songs[SONG_COUNT];

// Used for stopping the currently playing song (to be implemented)
int stop_command;

// Main functions
void easybuzz_init_songs(void);

// Helper functions
void easybuzz_play_note(note_struct, int);
void easybuzz_init_song(int *, node **, int);
void easybuzz_add_note(node **, double, double);
int  easybuzz_get_duration(double, int);
void easybuzz_wait(int);

// Low level functions (hardware)
void easybuzz_pwm_init(void);
void easybuzz_pwm_set_frequency(int);
void easybuzz_pwm_off(void);
#pragma endregion defines

#pragma region main_fuctions
// Initializes the hardware and songs for the EasyBuzz (called once at startup)
void easybuzz_init()
{
	// TODO: init hardware
	stop_command = 0;
	easybuzz_pwm_init();
	easybuzz_init_songs();
}

void easybuzz_test()
{
	easybuzz_init();
	easybuzz_play(SONG_TETRIS);
}

void easybuzz_init_songs(void)
{
	int s = -1;
	node *n;

	// Test (octave)
	easybuzz_init_song(&s, &n, 200);
	easybuzz_add_note(&n, scales[S4][C], QUARTER);
	easybuzz_add_note(&n, scales[S4][D], QUARTER);
	easybuzz_add_note(&n, scales[S4][E], QUARTER);
	easybuzz_add_note(&n, scales[S4][F], QUARTER);
	easybuzz_add_note(&n, scales[S4][G], QUARTER);
	easybuzz_add_note(&n, scales[S4][A], QUARTER);
	easybuzz_add_note(&n, scales[S4][B], QUARTER);
	easybuzz_add_note(&n, scales[S5][C], QUARTER);
	songs[s].first_note = n;

	// Tetris Theme
	easybuzz_init_song(&s, &n, 150);
	easybuzz_add_note(&n, scales[S5][E], QUARTER);
	easybuzz_add_note(&n, scales[S4][B], EIGHTH);
	easybuzz_add_note(&n, scales[S5][C], EIGHTH);
	
	easybuzz_add_note(&n, scales[S5][D], QUARTER);
	easybuzz_add_note(&n, scales[S5][C], EIGHTH);
	easybuzz_add_note(&n, scales[S4][B], EIGHTH);
	
	easybuzz_add_note(&n, scales[S4][A], QUARTER_DOT);
	easybuzz_add_note(&n, scales[S5][C], EIGHTH);
	
	easybuzz_add_note(&n, scales[S5][E], QUARTER);
	easybuzz_add_note(&n, scales[S4][B], EIGHTH);
	easybuzz_add_note(&n, scales[S5][C], EIGHTH);
	
	easybuzz_add_note(&n, scales[S4][B], QUARTER_DOT);
	easybuzz_add_note(&n, scales[S5][C], EIGHTH);
	
	easybuzz_add_note(&n, scales[S5][D], QUARTER);
	easybuzz_add_note(&n, scales[S5][E], QUARTER);

	easybuzz_add_note(&n, scales[S5][C], QUARTER);
	easybuzz_add_note(&n, scales[S4][A], EIGHTH);
	easybuzz_add_note(&n, rest,			 EIGHTH);
	
	easybuzz_add_note(&n, scales[S4][A], HALF);
	
	
	
	easybuzz_add_note(&n, rest,			 EIGHTH);
	easybuzz_add_note(&n, scales[S5][D], QUARTER);
	easybuzz_add_note(&n, scales[S4][F], EIGHTH);
	
	easybuzz_add_note(&n, scales[S5][A], QUARTER);
	easybuzz_add_note(&n, scales[S5][G], EIGHTH);
	easybuzz_add_note(&n, scales[S5][F], EIGHTH);
	
	easybuzz_add_note(&n, scales[S5][E], QUARTER_DOT);
	easybuzz_add_note(&n, scales[S5][C], EIGHTH);
	
	easybuzz_add_note(&n, scales[S5][E], QUARTER);
	easybuzz_add_note(&n, scales[S5][D], EIGHTH);
	easybuzz_add_note(&n, scales[S5][C], EIGHTH);
	
	easybuzz_add_note(&n, scales[S4][B], QUARTER);
	easybuzz_add_note(&n, scales[S4][B], EIGHTH);
	easybuzz_add_note(&n, scales[S5][C], EIGHTH);
	
	easybuzz_add_note(&n, scales[S5][D], QUARTER);
	easybuzz_add_note(&n, scales[S5][E], QUARTER);
	
	easybuzz_add_note(&n, scales[S5][C], QUARTER);
	easybuzz_add_note(&n, scales[S4][A], EIGHTH);
	easybuzz_add_note(&n, rest,			 EIGHTH);
	
	easybuzz_add_note(&n, scales[S4][A], HALF);
	songs[s].first_note = n;
}

// Plays a song from the songlist (given an index). Blocking for now, to be updated...
void easybuzz_play(int song_index)
{
	// TODO: add a song queue
	// TODO: place this in a thread and check first if there is already a song playing

	stop_command = 0;
	node *current_node = songs[song_index].first_note;
	int bpm = songs[song_index].bpm;

	while (1)
	{
		// TODO: check if the same can be achieved with thread library logic
		// If the stop command has been given (1), stop playing and set the command to 0 again
		if (stop_command != 0)
		{
			stop_command = 0;
			return;
		}

		// check if current_node == NULL, then the song is finished (current_node gets shifted automatically)
		if (current_node == NULL)
			return;
		note_struct note = llist_get(&current_node);

		// Play the next note of the song
		easybuzz_play_note(note, bpm);
	}
}

// Stops the current playing song (after a note is completed)
void easybuzz_stop()
{
	// TODO: check if the same can be achieved with thread library logic
	stop_command = 1;
}
#pragma endregion main_fuctions

#pragma region helper_functions
// Plays a given note (blocking) and waits in the case of a rest
void easybuzz_play_note(note_struct note, int bpm)
{
	// If the note is a rest, just wait the length of the note
	if (note.frequency == 0)
	{
		easybuzz_wait(easybuzz_get_duration(note.length, bpm) + NOTE_WAIT);
		return;
	}

	// Else, set the pwm frequency and wait the lenth of the note
	easybuzz_pwm_set_frequency((int)note.frequency);
	easybuzz_wait(easybuzz_get_duration(note.length, bpm));
	easybuzz_pwm_off();
	easybuzz_wait(NOTE_WAIT);
}

// Gets the time in milliseconds that a note should play for, given the bpm and the multiplier (where the quarter note is 1)
int easybuzz_get_duration(double multiplier, int bpm)
{
	return (int)(60000.0 / bpm * multiplier - NOTE_WAIT);
}

// Initializes the song for the current song struct (sets bpm, and creates a linked list)
void easybuzz_init_song(int *song_index, node **head_node, int bpm)
{
	(*song_index)++;
	song_struct song = { .bpm = bpm };
	songs[*song_index] = song;
	node* head = llist_create();
	*head_node = head;
	songs[*song_index].first_note = head;
}

// Adds a note on the end of the note linked list of a song given the song index, last node pointer, and the note fields
void easybuzz_add_note(node **last_node, double frequency, double length)
{
	note_struct note = {.frequency = frequency, .length = length };
	llist_add_last(last_node, note);
}

// Sleep method that sleeps for the amount of given ms
void easybuzz_wait(int ms)
{
	// TODO: check if the same can be achieved with thread library logic
	for (int tms = 0; tms < ms; tms++)
		_delay_ms(1);			// library function (max 30 ms at 8MHz)
}
#pragma endregion helper_functions

#pragma region low_level_functions
void easybuzz_pwm_init()
{
	DDRB = 0xFF;
	TCCR1A = 0b10000010;		// compare output at OC1A  (=PB5)
	TCCR1B = 0b00011000;		// fast PWM, TOP=ICR1, prescaler=8, RUN
}

void easybuzz_pwm_set_frequency(int frequency)
{
	TCCR1B |= (1 << CS11);		// Turn on the 8 times prescaler (which starts the timer)
	int ms = (int)(1.0 / frequency * 1000000.0);
	ICR1	= ms;		// TOP value for counter
	OCR1A	= ms / 2;	// compare value in between
}

void easybuzz_pwm_off()
{
	TCCR1B |= (0 << CS11);		// Turn off the prescaler (which stops the timer)
	TCCR1B = 0b00011000;		// fast PWM, TOP=ICR1, prescaler=8, NO RUN
}
#pragma endregion low_level_functions

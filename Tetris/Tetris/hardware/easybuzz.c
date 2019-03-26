/*
 * EasyBuzz.c
 *
 * Created: 27-Feb-19 11:05:13
 * Author: Daan
 */

// Ignore pragma warnings, because Atmel doesn't like code regions for some reason
#pragma GCC diagnostic ignored "-Wunknown-pragmas"

#include <avr/io.h>
#include <stdio.h>

#include "EasyBuzz.h"
#include "../util/LinkedList.h"

#pragma region defines
// Defines for array lengths
#define SONG_COUNT		4

#define SCALE_LENGTH	12
#define SCALE_COUNT		5

// Logic constants for the update function
#define TRUE			1
#define FALSE			0
#define NONE		   -1

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

// Amount of ms that all notes get shortened by to separate the notes
#define NOTE_WAIT		20

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
#define S3	0
#define S4	1
#define S5	2
#define S6	3
#define S7	4

// Struct that holds a song (bpm and a note linked list (the pointer to the head))
typedef struct
{
	int bpm;
	node *first_note; // Head of the linked list
} song_struct;

// This 2d array holds the tone frequencies for each note in lists of scales
int scales[SCALE_COUNT][SCALE_LENGTH] =
{ // C	  Cs   D	Ds	 E	  F	   Fs	G	 Gs	  A	   As	B
	{131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247 },	// Scale 3
	{262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494 },	// Scale 4
	{523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988 },	// Scale 5
	{1046,1108,1174,1244,1318,1397,1480,1568,1662,1760,1865,1975},	// Scale 6
	{2093,2217,2349,2489,2637,2794,2960,3136,3322,3520,3729,3951}	// Scale 7
};

// Is used for a rest in a song, is called the same way as a normal note
int rest = 0;

// Song array that holds all the playable songs in song structs (called by index from defines in the header file)
song_struct songs[SONG_COUNT];

// Variables that hold the currently playing loop and effect for the update function
int loop_index;
node *loop_node;
int	loop_bpm;
int loop_counter;

int effect_index;
node *effect_node;
int effect_bpm;
int effect_counter;

// Main functions
void easybuzz_init_songs(void);

// Helper functions
void easybuzz_loop_update(int);
void easybuzz_effect_update(void);
void easybuzz_init_song(int *, node **, int);
void easybuzz_add_note(node **, double, double);
int  easybuzz_get_duration(double, int);

// Low level functions (hardware)
void easybuzz_init_pwm(void);
void easybuzz_pwm_set_frequency(int);
void easybuzz_pwm_off(void);
#pragma endregion defines

#pragma region main_fuctions
// Initializes the hardware and songs for the EasyBuzz (called once at startup)
void easybuzz_init()
{
	// Initialize the update logic variables
	loop_index =	NONE;
	loop_node =		NULL;
	loop_bpm =		NONE;
	loop_counter =	0;
	
	effect_index =	NONE;
	effect_node =	NULL;
	effect_bpm =	NONE;
	effect_counter= 0;

	// Initialize the hardware and songs
	easybuzz_init_pwm();
	easybuzz_init_songs();
}

// Creates all the song structs with notes and saves them in the songs array
void easybuzz_init_songs(void)
{
	int s = -1;
	node *n;

	// Menu
	#pragma region
	easybuzz_init_song(&s, &n, 130);
	easybuzz_add_note(&n, scales[S4][D], EIGHTH);
	easybuzz_add_note(&n, scales[S4][As], EIGHTH);
	easybuzz_add_note(&n, scales[S4][G], EIGHTH);
	easybuzz_add_note(&n, scales[S4][G], SIXTEENTH);
	easybuzz_add_note(&n, scales[S4][D], EIGHTH);
	easybuzz_add_note(&n, scales[S4][D], SIXTEENTH);
	easybuzz_add_note(&n, scales[S4][A], EIGHTH);
	easybuzz_add_note(&n, scales[S4][F], EIGHTH);
	easybuzz_add_note(&n, scales[S4][F], SIXTEENTH);

	easybuzz_add_note(&n, scales[S4][D], EIGHTH);
	easybuzz_add_note(&n, scales[S4][D], SIXTEENTH);
	easybuzz_add_note(&n, scales[S4][A], EIGHTH);
	easybuzz_add_note(&n, scales[S4][F], EIGHTH);
	easybuzz_add_note(&n, scales[S4][F], SIXTEENTH);
	easybuzz_add_note(&n, scales[S4][C], EIGHTH);
	easybuzz_add_note(&n, scales[S4][C], EIGHTH);
	easybuzz_add_note(&n, scales[S4][E], EIGHTH);
	easybuzz_add_note(&n, scales[S4][E], SIXTEENTH);
	easybuzz_add_note(&n, scales[S4][F], EIGHTH);

	songs[s].first_note = n;
	#pragma endregion

	// Tetris Theme
	#pragma region 
	easybuzz_init_song(&s, &n, 150);
	easybuzz_add_note(&n, scales[S4][E], QUARTER);
	easybuzz_add_note(&n, scales[S3][B], EIGHTH);
	easybuzz_add_note(&n, scales[S4][C], EIGHTH);
	
	easybuzz_add_note(&n, scales[S4][D], QUARTER);
	easybuzz_add_note(&n, scales[S4][C], EIGHTH);
	easybuzz_add_note(&n, scales[S3][B], EIGHTH);
	
	easybuzz_add_note(&n, scales[S3][A], QUARTER_DOT);
	easybuzz_add_note(&n, scales[S4][C], EIGHTH);
	
	easybuzz_add_note(&n, scales[S4][E], QUARTER);
	easybuzz_add_note(&n, scales[S3][B], EIGHTH);
	easybuzz_add_note(&n, scales[S4][C], EIGHTH);
	
	easybuzz_add_note(&n, scales[S3][B], QUARTER_DOT);
	easybuzz_add_note(&n, scales[S4][C], EIGHTH);
	
	easybuzz_add_note(&n, scales[S4][D], QUARTER);
	easybuzz_add_note(&n, scales[S4][E], QUARTER);

	easybuzz_add_note(&n, scales[S4][C], QUARTER);
	easybuzz_add_note(&n, scales[S3][A], EIGHTH);
	easybuzz_add_note(&n, rest,			 EIGHTH);
	
	easybuzz_add_note(&n, scales[S3][A], HALF);
	
	
	
	easybuzz_add_note(&n, rest,			 EIGHTH);
	easybuzz_add_note(&n, scales[S4][D], QUARTER);
	easybuzz_add_note(&n, scales[S4][F], EIGHTH);
	
	easybuzz_add_note(&n, scales[S4][A], QUARTER);
	easybuzz_add_note(&n, scales[S4][G], EIGHTH);
	easybuzz_add_note(&n, scales[S4][F], EIGHTH);
	
	easybuzz_add_note(&n, scales[S4][E], QUARTER_DOT);
	easybuzz_add_note(&n, scales[S4][C], EIGHTH);
	
	easybuzz_add_note(&n, scales[S4][E], QUARTER);
	easybuzz_add_note(&n, scales[S4][D], EIGHTH);
	easybuzz_add_note(&n, scales[S4][C], EIGHTH);
	
	easybuzz_add_note(&n, scales[S3][B], QUARTER);
	easybuzz_add_note(&n, scales[S3][B], EIGHTH);
	easybuzz_add_note(&n, scales[S4][C], EIGHTH);
	
	easybuzz_add_note(&n, scales[S4][D], QUARTER);
	easybuzz_add_note(&n, scales[S4][E], QUARTER);
	
	easybuzz_add_note(&n, scales[S4][C], QUARTER);
	easybuzz_add_note(&n, scales[S3][A], EIGHTH);
	easybuzz_add_note(&n, rest,			 EIGHTH);
	
	easybuzz_add_note(&n, scales[S3][A], HALF);
	songs[s].first_note = n;
	#pragma endregion

	// Row clear
	#pragma region
	easybuzz_init_song(&s, &n, 100);
	easybuzz_add_note(&n, rest,			 EIGHTH);
	easybuzz_add_note(&n, scales[S4][C], SIXTEENTH);
	easybuzz_add_note(&n, scales[S4][G], SIXTEENTH);
	easybuzz_add_note(&n, scales[S5][C], QUARTER);
	easybuzz_add_note(&n, rest,			 EIGHTH);
	songs[s].first_note = n;
	#pragma endregion

	// Game over
	#pragma region
	easybuzz_init_song(&s, &n, 120);
	easybuzz_add_note(&n, rest,			 EIGHTH);
	easybuzz_add_note(&n, scales[S4][D], SIXTEENTH);
	easybuzz_add_note(&n, scales[S4][D], SIXTEENTH);
	easybuzz_add_note(&n, scales[S5][D], EIGHTH);
	easybuzz_add_note(&n, scales[S4][A], EIGHTH);
	easybuzz_add_note(&n, rest,			 EIGHTH);
	songs[s].first_note = n;
	#pragma endregion
}

// Update function that handles the loop and effect logic (needs to be called every 1 ms)
void easybuzz_update()
{
	// check if a sound effect needs to play
	if (effect_index != NONE)
		easybuzz_effect_update();
	
	// check if a loop needs to play
	if (loop_index != NONE && effect_index == NONE)
		easybuzz_loop_update(TRUE);
	
	// check if a loop needs to tick in the background but not play
	if (loop_index != NONE && effect_index != NONE)
		easybuzz_loop_update(FALSE);
}

// Plays a song on loop
void easybuzz_play_loop(int song_index)
{
	// If the loop is already playing, do nothing
	if (loop_index == song_index)
		return;
	
	loop_index = song_index;
 	loop_node = songs[song_index].first_note;
	loop_bpm = songs[song_index].bpm;
	loop_counter = 0;
}

// Plays a song from the songlist (given an index)
void easybuzz_play_effect(int song_index)
{
	effect_index = song_index;
	effect_node = songs[song_index].first_note;
	effect_bpm = songs[song_index].bpm;
	effect_counter = 0;
	easybuzz_pwm_off();
}

// Stops the loop (sound effects still get played)
void easybuzz_stop_loop()
{
	// Reset the logic variables
	loop_index =	NONE;
	loop_node =		NULL;
	loop_bpm =		NONE;
	loop_counter =	0;
	
	// Stop the playing sound
	easybuzz_pwm_off();
}
#pragma endregion main_fuctions

#pragma region helper_functions
void easybuzz_loop_update(int needs_to_play)
{
	note_struct note = loop_node->data;
	int length = easybuzz_get_duration(note.length, loop_bpm);
	
	// If the counter is 0 and needs_to_play is TRUE and the note is not a rest, then set the pwm
	if (loop_counter == 0 && needs_to_play == TRUE && note.frequency != 0)
	{
		easybuzz_pwm_set_frequency((int) note.frequency);
	}
	// If the counter is more then the length of the note, stop the pwm
	else if (loop_counter == length && needs_to_play == TRUE)
	{
		easybuzz_pwm_off();
	}
	// If the counter is more then the length of the note + the note wait, go to the next node
	else if (loop_counter >= length + NOTE_WAIT)
	{
		loop_counter = 0;
		loop_node = loop_node->next;
		if (loop_node == NULL)
			loop_node = songs[loop_index].first_note;
		return;
	}
	
	// Increment the loop ms counter
	loop_counter++;
}

void easybuzz_effect_update()
{
	note_struct note = effect_node->data;
	int length = easybuzz_get_duration(note.length, effect_bpm);
	
	// If the counter is 0 and the note is not a rest, then set the pwm
	if (effect_counter == 0 && note.frequency != 0)
	{
		easybuzz_pwm_set_frequency((int) note.frequency);
	}
	// If the counter is more then the length of the note, stop the pwm
	else if (effect_counter == length)
	{
		easybuzz_pwm_off();
	}
	// If the counter is more then the length of the note + the note wait, go to the next node
	else if (effect_counter >= length + NOTE_WAIT)
	{
		effect_counter = 0;
		effect_node = effect_node->next;
		
		// If the end of the effect is reached, stop the effect and reset the logic
		if (effect_node == NULL)
		{
			effect_index = NONE;
			effect_bpm = NONE;
			effect_counter = 0;
		}
		return;
	}
	
	// Increment the effect ms counter
	effect_counter++;
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

// Gets the time in milliseconds that a note should play for, given the bpm and the multiplier (where the quarter note is 1)
int easybuzz_get_duration(double multiplier, int bpm)
{
	return (int)(60000.0 / bpm * multiplier - NOTE_WAIT);
}

// Adds a note on the end of the note linked list of a song given the song index, last node pointer, and the note fields
void easybuzz_add_note(node **last_node, double frequency, double length)
{
	note_struct note = {.frequency = frequency, .length = length };
	llist_add(last_node, note);
}
#pragma endregion helper_functions

#pragma region low_level_functions
void easybuzz_init_pwm()
{
	DDRB = 0xFF;
	TCCR1A = 0b10000010;		// compare output at OC1A  (=PB5)
	TCCR1B = 0b00011000;		// fast PWM, TOP=ICR1
}

void easybuzz_pwm_set_frequency(int frequency)
{
	int ms = (int)(1.0 / frequency * 1000000.0); // Convert hertz to microseconds
	
	TCCR1B |= (1 << CS11);		// Turn on the 8 times prescaler (which starts the timer)
	ICR1	= ms;				// TOP value for counter
	OCR1A	= ms / 2;			// compare value in between
}

void easybuzz_pwm_off()
{
	TCCR1B &= ~(1 << CS11);		// Turn off the prescaler (which stops the timer)
}
#pragma endregion low_level_functions

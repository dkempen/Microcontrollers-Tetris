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

#include "EasyBuzz.h"

#pragma region defines
// Defines for array lengths
#define MAX_SONG_LENGTH 10
#define SONG_COUNT		2

#define SCALE_LENGTH	12
#define SCALE_COUNT		4

// Note lengths
#define FULL			4
#define HALF_DOT		3
#define HALF			2
#define QUARTER_DOT		1.5
#define QUARTER			1
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

// Struct that holds a note (frequency and length)
typedef struct
{
	const int *frequency;	// It's a pointer because it needs to get the value from the constant scales array
	const double length;	// length is defined as a multiplier value based on the length of a quarter note as value 1
} note_struct;

// Struct that holds a song (bpm, a note array and the size of that array)
typedef struct
{
	const int size;
	const int bpm;
	const note_struct notes[MAX_SONG_LENGTH];
} song_struct;

// This 2d array holds the tone frequencies for each note in lists of scales
const int scales[SCALE_COUNT][SCALE_LENGTH] =
{ // C	  Cs   D	Ds	 E	  F	   Fs	G	 Gs	  A	   As	B
	{262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494 },	// Scale 4
	{523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988 },	// Scale 5
	{1046,1108,1174,1244,1318,1397,1480,1568,1662,1760,1865,1975},	// Scale 6
	{2093,2217,2349,2489,2637,2794,2960,3136,3322,3520,3729,3951}	// Scale 7
};

const int rest = 0;	// Is used for a rest in a song, is called the same way as a normal note with &rest

// Song array that holds all the playable songs in song structs (called by index from defines in the header file)
const song_struct songs[SONG_COUNT] =
{
	{	// Test song (scale)
		7,
		100,
		{
			{&scales[S4][C], QUARTER},	// C4
			{&scales[S4][D], QUARTER},	// D4
			{&scales[S4][E], QUARTER},	// E4
			{&scales[S4][F], QUARTER},	// F4
			{&scales[S4][G], QUARTER},	// G4
			{&scales[S4][A], QUARTER},	// A4
			{&scales[S4][B], QUARTER}	// B4
		}
	},
};

// Used for stopping the currently playing song (to be implemented)
int stop_command;

// Helper functions
void easybuzz_play_note(note_struct, int);
int  easybuzz_get_duration(double, int);
void easybuzz_wait(int);

// Low level functions (hardware)
void easybuzz_pwm_init(void);
void easybuzz_pwm_set_frequency(int);
void easybuzz_pwm_off(void);
#pragma endregion defines

#pragma region main_fuctions
// Initializes the hardware for the EasyBuzz (called once at startup)
void easybuzz_init()
{
	// TODO: init hardware
	stop_command = 0;
	easybuzz_pwm_init();
}

// Plays a song from the songlist (given an index). Blocking for now, to be updated...
void easybuzz_play(int song_index)
{
	// TODO: add a song queue
	// TODO: place this in a thread and check first if there is already a song playing
	
	stop_command = 0;
	song_struct song = songs[song_index];
	int size = song.size;
	int bpm  = song.bpm;
	
	for(int i = 0; i < size; i++)
	{
		// TODO: check if the same can be achieved with thread library logic
		// If the stop command has been given (1), stop playing and set the command to 0 again
		if (stop_command != 0)
		{
			stop_command = 0;
			return;
		}
		
		// Play the next note of the song
		easybuzz_play_note(song.notes[i], bpm);
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
	if (*note.frequency == 0)
	{
		easybuzz_wait(easybuzz_get_duration(note.length, bpm) + NOTE_WAIT);
		return;
	}
	
	// Else, set the pwm frequency and wait the lenth of the note
	easybuzz_pwm_set_frequency(*note.frequency);
	easybuzz_wait(easybuzz_get_duration(note.length, bpm));
	easybuzz_pwm_off();
	easybuzz_wait(NOTE_WAIT);
}

// Gets the time in milliseconds that a note should play for, given the bpm and the multiplier (where the quarter note is 1)
int easybuzz_get_duration(double multiplier, int bpm)
{
	return (int) (60000 / bpm * multiplier - NOTE_WAIT);
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
	// TODO: control hardware
}

void easybuzz_pwm_set_frequency(int frequency)
{
	// TODO: control hardware
}

void easybuzz_pwm_off()
{
	// TODO: control hardware
}
#pragma endregion low_level_functions

#pragma region old_code
void timer1Init(void);

#define TIMER1_PRESCALER (uint8_t) 8

const uint16_t A4_FREQ = 440;
const uint16_t C5_FREQ = 523;
const uint16_t D6_FREQ = 1175;
#define A4 (F_CPU / (A4_FREQ * TIMER1_PRESCALER * 2) - 1)
#define C5 (F_CPU / (C5_FREQ * TIMER1_PRESCALER * 2) - 1)
#define D6 (F_CPU / (D6_FREQ * TIMER1_PRESCALER * 2) - 1)

void easybuzz_test()
{
	// 	DDRE = 0xFF;				// set PORTA for output
	// 	timer1Init();
	// 	while (1)
	// 	{
	// 		DDRE = ICR1;
	// 		wait(1);
	// 	}
	DDRE = 0xFF;				// set PORTA for output

	// Set OC1A as output pin
	DDRE = (1 << PINB1);

	// Set Timer1, mode CTC, toggle on compare, prescale 8
	//TCCR1A = (1 << COM1A0);
	//TCCR1B = (1 << WGM12)|(1 << CS10);
	TCCR1A = 0b10000010;		// compare output at OC1A  (=PB5)
	TCCR1B = 0b00011010;		// fast PWM, TOP=ICR1, prescaler=8, RUN

	while (1)
	{
		// play A4 for 0.5 sec
		ICR1 = A4*2;
		OCR1A = A4;
		easybuzz_wait(500);

		// play C5 for 0.5 sec
		ICR1 = C5*2;
		OCR1A = C5;
		easybuzz_wait(500);

		// play D6 for 0.5 sec
		ICR1 = D6*2;
		OCR1A = D6;
		easybuzz_wait(500);
	}
}

#define INTERVAL	2273		// kamertoon = a’ = A4= 440 Hz

// Initialize timer 1: fast PWM at OC1A
void timer1Init( void )
{
	ICR1	= INTERVAL;			// TOP value for counter
	OCR1A	= INTERVAL/2;		// compare value in between
	TCCR1A = 0b10000010;		// compare output at OC1A  (=PB5)
	TCCR1B = 0b00011010;		// fast PWM, TOP=ICR1, prescaler=8, RUN
}
#pragma endregion old_code

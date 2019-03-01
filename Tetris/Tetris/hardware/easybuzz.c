/*
 * EasyBuzz.c
 *
 * Created: 27-Feb-19 11:05:13
 * Author: Daan
 */

#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include "EasyBuzz.h"

void timer1Init(void);
void wait_easy_buzz(int);

#define TIMER1_PRESCALER (uint8_t) 8

const uint16_t A4_FREQ = 440;
const uint16_t C5_FREQ = 523;
const uint16_t D6_FREQ = 1175;
#define A4 (F_CPU / (A4_FREQ * TIMER1_PRESCALER * 2) - 1)
#define C5 (F_CPU / (C5_FREQ * TIMER1_PRESCALER * 2) - 1)
#define D6 (F_CPU / (D6_FREQ * TIMER1_PRESCALER * 2) - 1)

// void easybuzz_test()
// {
// 	DDRE = 0xFF;
// 	timer1Init();
// 	wait(10000);
// }

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
		wait_easy_buzz(500);

		// play C5 for 0.5 sec
		ICR1 = C5*2;
		OCR1A = C5;
		wait_easy_buzz(500);

		// play D6 for 0.5 sec
		ICR1 = D6*2;
		OCR1A = D6;
		wait_easy_buzz(500);
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

void wait_easy_buzz(int ms)
{
	for (int tms=0; tms<ms; tms++)
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
}

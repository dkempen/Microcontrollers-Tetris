/*
 * DotMatrix.c
 *
 * Created: 20-Feb-19 15:12:54
 * Author: Daan
 */ 

#define F_CPU 8000000L // TODO: remove together with test function

// Ignore pragma warnings, because Atmel doesn't like code regions for some reason
#pragma GCC diagnostic ignored "-Wunknown-pragmas"

#include <avr/io.h>
#include <util/delay.h>

#include "DotMatrix.h"

// I2C address of the 2 displays
#define D0_I2C_ADDR	((0x70 + 0) << 1)
#define D1_I2C_ADDR	((0x70 + 4) << 1)

// Function declarations
void twi_init(void);
void matrix_init_display(int);
void matrix_clear_display(int);
void matrix_fill_display(int);

void wait(int);
void draw_row(int, int, int);
void shift_data(int *);

void twi_start(void);
void twi_stop(void);
void twi_tx(unsigned char);

#pragma region main_fuctions
// Initializes both of the matrix displays
void matrix_init()
{
	matrix_init_display(D0_I2C_ADDR);
	matrix_init_display(D1_I2C_ADDR);
}

// Initializes the maxtrix display with the given address
void matrix_init_display(int address)
{
	twi_init();		// Init TWI interface

	// Init HT16K22. Page 32 datasheet
	twi_start();
	twi_tx(address);	// Display I2C addres + R/W bit
	twi_tx(0x21);		// Internal osc on (page 10 HT16K33)
	twi_stop();

	twi_start();
	twi_tx(address);	// Display I2C address + R/W bit
	twi_tx(0xA0);		// HT16K33 pins all output
	twi_stop();

	twi_start();
	twi_tx(address);	// Display I2C address + R/W bit
	twi_tx(0xE3);		// Display Dimming 4/16 duty cycle
	twi_stop();

	twi_start();
	twi_tx(address);	// Display I2C address + R/W bit
	twi_tx(0x81);		// Display OFF - Blink On
	twi_stop();
}

// Clears both of the maxtrix displays
void matrix_clear()
{
	matrix_clear_display(D0_I2C_ADDR);
	matrix_clear_display(D1_I2C_ADDR);
}

// Clears the maxtrix display with the given address
void matrix_clear_display(int address)
{
	for (int y = 0; y < 8; y ++)
		draw_row(address, y, 0);
}

// Fills both of the maxtrix displays
void matrix_fill()
{
	matrix_fill_display(D0_I2C_ADDR);
	matrix_fill_display(D1_I2C_ADDR);
}

// Fills the maxtrix display with the given address
void matrix_fill_display(int address)
{
	for (int y = 0; y < 8; y ++)
		draw_row(address, y, 0xFF);
}

/* Draws the game field to both of the matrix displays (D0 is the top display, D1 is the bottom display)
 * Field must consist of 0 (off) and 1 (on), and must be constructed like this: field[x][y] (without exceeding the size constraints) */
void matrix_draw_game_field(int field[FIELD_WIDTH][FIELD_HEIGHT])
{
	int x;
	int y;
	int data;
	
	// Draw each row of the game field, from top left (0, 0) with rows as the y-axis
	for (y = 0; y < FIELD_HEIGHT; y++)
	{
		// Create data for an entire row by looping through the array
		data = 0;
		for (x = 0; x < FIELD_WIDTH; x++)
			data |= (1 * field[x][y]) << x;
		
		// Draw the row to the corresponding display
		if (y < 8)
			draw_row(D0_I2C_ADDR, y, data);
		else
			draw_row(D1_I2C_ADDR, y - 8, data);
	}
}
#pragma endregion

#pragma region helper_fuctions
// row (from 0 - 8) data (from 0 - 8 bit of a byte)
void draw_row(int address, int row, int data)
{
	shift_data(&data);
	
	twi_start();
	twi_tx(address);	// Display I2C addres + R/W bit
	twi_tx(row * 2);	// Address
	twi_tx(data);		// data
	twi_stop();
}

// Change row data because the bits on the display are offset by 1 bit
void shift_data(int *data)
{
	if (*data & 1)	// If bit 1 is set, shift everything to the right and set bit 8 to 1
		*data = (*data - 1) / 2 + (1 << 7);
	else			// If bit 1 is not set, just shift everything to the right
		*data /= 2;
}

// Temporary wait method (TODO: remove with test method)
void wait(int ms)
{
	for (int i=0; i<ms; i++)
	_delay_ms(1);		// library function (max 30 ms at 8MHz)
}

// Temporary test method (TODO: remove with wait method)
void matrix_test()
{
	matrix_init();
	
	int y = 0;
	int x = 0;
	
	while (1)
	{
		matrix_clear();
		
		// Loop through all the leds individually
		int data;
		for (y = 0; y < 16; y++)
		{
			data = 0;
			for (x = 0; x < 8; x++)
			{
				data |= 1 << x;
				if (y < 8)
					draw_row(D0_I2C_ADDR, y, data);
				else
					draw_row(D1_I2C_ADDR, y - 8, data);
				wait(50);
			}
		}
	}
}
#pragma endregion

#pragma region low_level_fucntions
void twi_init(void)
{
	TWSR = 0;
	TWBR = 32;	 // TWI clock set to 100kHz, prescaler = 0
}

void twi_start(void)
{
	TWCR = (0x80 | 0x20 | 0x04);
	while( 0x00 == (TWCR & 0x80) );
}

void twi_stop(void)
{
	TWCR = (0x80 | 0x10 | 0x04);
}

void twi_tx(unsigned char data)
{
	TWDR = data;
	TWCR = (0x80 | 0x04);
	while( 0 == (TWCR & 0x80) );
}
#pragma endregion

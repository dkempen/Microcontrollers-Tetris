/*
 * matrix.c
 *
 * Created: 20-Feb-19 15:12:54
 *  Author: Daan
 */ 

#define F_CPU 8000000L

// I2C address of display
#define D0_I2C_ADDR	((0x70 + 0) << 1)
#define D1_I2C_ADDR	((0x70 + 4) << 1)

#include <avr/io.h>
#include <util/delay.h>

void twi_init(void);
void twi_start(void);
void twi_stop(void);
void twi_tx(unsigned char);

void wait(int);
void led_row(int, int);
void shift_data(int *);

void matrix_init()
{
	twi_init();		// Init TWI interface

	// Init HT16K22. Page 32 datasheet
	twi_start();
	twi_tx(D0_I2C_ADDR);	// Display I2C addres + R/W bit
	twi_tx(0x21);	// Internal osc on (page 10 HT16K33)
	twi_stop();

	twi_start();
	twi_tx(D0_I2C_ADDR);	// Display I2C address + R/W bit
	twi_tx(0xA0);	// HT16K33 pins all output
	twi_stop();

	twi_start();
	twi_tx(D0_I2C_ADDR);	// Display I2C address + R/W bit
	twi_tx(0xE3);	// Display Dimming 4/16 duty cycle
	twi_stop();

	twi_start();
	twi_tx(D0_I2C_ADDR);	// Display I2C address + R/W bit
	twi_tx(0x81);	// Display OFF - Blink On
	twi_stop();
}

void matrix_clear()
{
	for (int i = 0; i < 8; i ++)
		led_row(i, 0);
}

void matrix_write(unsigned char *field)
{
	
}

void matrix_test()
{
	matrix_init();
	matrix_clear(); 
	
	int i = 0;
	int j = 0;
	
	while (1)
	{
		// Loop through all the leds individually	
		int data;
		for (i = 0; i < 8; i++)
		{
			data = 0;
			for (j = 0; j < 8; j++)
			{
				data |= 1 << j;
				led_row(i, data);
				wait(50);
			}
		}
		matrix_clear();
	}
}

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

void wait( int ms )
{
	for (int i=0; i<ms; i++)
		_delay_ms(1);		// library function (max 30 ms at 8MHz)
}

// row (from 0 - 8) data (from 0 - 8 bit of a byte)
void led_row(int address, int data)
{
	shift_data(&data);
	
	twi_start();
	twi_tx(D0_I2C_ADDR);		// Display I2C addres + R/W bit
	twi_tx(address * 2);// Address
	twi_tx(data);		// data
	twi_stop();
}

// Change data because the bits are offset by 1 bit
void shift_data(int *data)
{
	if (*data & 1)
		*data = (*data - 1) / 2 + (1 << 7);
	else
		*data /= 2;
}

/*
 * matrix.c
 *
 * Created: 20-Feb-19 15:12:54
 *  Author: Daan
 */ 

#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>

void test()
{
	twi_init();		// Init TWI interface

	// Init HT16K22. Page 32 datasheet
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit
	twi_tx(0x21);	// Internal osc on (page 10 HT16K33)
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xA0);	// HT16K33 pins all output
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0xE3);	// Display Dimming 4/16 duty cycle
	twi_stop();

	twi_start();
	twi_tx(0xE0);	// Display I2C address + R/W bit
	twi_tx(0x81);	// Display OFF - Blink On
	twi_stop();
	
	int i = 0;
	int j = 0;
	
	while (1)
	{
		/*for (i = 0; i < 8 * 2; i += 2)
		{
			twi_start();
			twi_tx(0xE0);	// Display I2C addres + R/W bit
			twi_tx(i);	// Address
			twi_tx(0x00);	// data
			twi_stop();
		}

		wait(500);
		
		for (j = 0; j < 8 * 2; j += 2)
		{
		twi_start();
		twi_tx(0xE0);	// Display I2C addres + R/W bit
		twi_tx(j);	// Address
		twi_tx(0xFF);	// data
		twi_stop();
		}

		wait(500);*/
		
		for (i = 0; i < 8 * 2; i += 2)
		{
			for (j = 0; j < 8; j++)
			{
				//led_row(i, 0b10000000); // displays 10000000 needs to display 00000001
				//led_row(i, 0b01000000); // displays 00000001 needs to display 00000010
				  led_row(i, 0b00000001); // displays 01000000 needs to display 10000000
				wait(50);
			}
		}
		
		for (i = 0; i < 8 * 2; i += 2)
		{
			led_row(i, 0x00);
		}
	}
}

void twi_init(void)
/* 
short:			Init AVR TWI interface and set bitrate
inputs:			
outputs:	
notes:			TWI clock is set to 100 kHz
Version :    	DMK, Initial code
*******************************************************************/
{
	TWSR = 0;
	TWBR = 32;	 // TWI clock set to 100kHz, prescaler = 0
}

void twi_start(void)
/* 
short:			Generate TWI start condition
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
*******************************************************************/
{
	TWCR = (0x80 | 0x20 | 0x04);
	while( 0x00 == (TWCR & 0x80) );
}

void twi_stop(void)
/* 
short:			Generate TWI stop condition
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
*******************************************************************/
{
	TWCR = (0x80 | 0x10 | 0x04);
}

void twi_tx(unsigned char data)
/* 
short:			transmit 8 bits data
inputs:		
outputs:	
notes:			
Version :    	DMK, Initial code
*******************************************************************/
{
	TWDR = data;
	TWCR = (0x80 | 0x04);
	while( 0 == (TWCR & 0x80) );
}

void wait( int ms )
{
	for (int i=0; i<ms; i++)
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
}

void led_row(int address, int data)
{
	/*if (data & (1 << 7))
	{
		data = data - (1 << 7);
		data = data * 2 + 1;
	}
	data = data * 2;*/
		
	twi_start();
	twi_tx(0xE0);	// Display I2C addres + R/W bit
	twi_tx(address);	// Address
	twi_tx(data);	// data
	twi_stop();
}

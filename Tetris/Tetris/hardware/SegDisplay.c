/*
 * SegDisplay.c
 *
 * Created: 5-3-2019 14:22:50
 *  Author: Max van Noordennen
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "SegDisplay.h"


#define BIT(x)		( 1<<x )
#define DDR_SPI		DDRB					// spi Data direction register
#define PORT_SPI	PORTB					// spi Output register
#define SPI_SCK		1						// PB1: spi Pin System Clock
#define SPI_MOSI	2						// PB2: spi Pin MOSI
#define SPI_MISO	3						// PB3: spi Pin MISO
#define SPI_SS		0						// PB0: spi Pin Slave Select

void SegDisplay_Init()
{
	DDRB = 0x01;
	SegDisplay_masterInit();
	SegDisplay_DriverInit();
}

void SegDisplay_masterInit()
{
	DDR_SPI = 0xff;
	// All pins output: MOSI, SCK, SS, SS_display as output
	DDR_SPI &= ~BIT(SPI_MISO);
	// 	except: MISO input
	PORT_SPI |= BIT(SPI_SS);
	// SS_ADC == 1: deselect slave
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);
}

// Write a byte from master to slave
void SegDisplay_write(unsigned char data)
{
	SPDR = data;
	// Load byte to Data register --> starts transmission
	while( !(SPSR & BIT(SPIF)) );
	// Wait for transmission complete
}

// Write a byte from master to slave and read a byte from slave
char SegDisplay_writeRead(unsigned char data)
{
	SPDR = data;
	// Load byte to Data register --> starts transmission
	while( !(SPSR & BIT(SPIF)) );
	// Wait for transmission complete
	data = SPDR;
	// New received data (eventually, MISO) in SPDR
	return data;
	// Return received byte
}

// Select device on pinnumer PORTB
void SegDisplay_slaveSelect(unsigned char chipNumber)
{
	PORTB &= ~BIT(chipNumber);
}

// Deselect device on pinnumer PORTB
void SegDisplay_slaveDeSelect(unsigned char chipNumber)
{
	PORTB |= BIT(chipNumber);
}

// Initialize the driver chip 
void SegDisplay_DriverInit()
{
	SegDisplay_slaveSelect(0);
	// Select display chip
	SegDisplay_write(0x09);
	// Register 09: Decode Mode
	SegDisplay_write(0xFF);
	// All digit mode
	SegDisplay_slaveDeSelect(0);
	// Deselect display chip

	SegDisplay_slaveSelect(0);
	// Select dispaly chip
	SegDisplay_write(0x0A);
	// Register 0A: Intensity
	SegDisplay_write(0x01);
	// Sets the intensity
	SegDisplay_slaveDeSelect(0);
	// Deselect display chip

	SegDisplay_slaveSelect(0);
	// Select display chip
	SegDisplay_write(0x0B);
	// Register 0B: Scan-limit
	SegDisplay_write(0x04);
	// Sets all individual displays to on
	SegDisplay_slaveDeSelect(0);
	// Deselect display chip

	SegDisplay_slaveSelect(0);
	// Select display chip
	SegDisplay_write(0x0C);
	// Register 0B: Shutdown register
	SegDisplay_write(0x01);
	//Sets display to Display on
	SegDisplay_slaveDeSelect(0);
	// Deselect display chip
}


// Set display on ('normal operation')
void SegDisplay_displayOn()
{
	SegDisplay_slaveSelect(0);
	// Select display chip
	SegDisplay_write(0x0C);
	// Register 0B: Shutdown register
	SegDisplay_write(0x01);
	// Sets the display on
	SegDisplay_slaveDeSelect(0);
	// Deselect display chip
}

// Set display off ('shut down')
void SegDisplay_displayOff()
{
	SegDisplay_slaveSelect(0);
	// Select display chip
	SegDisplay_write(0x0C);
	// Register 0B: Shutdown register
	SegDisplay_write(0x00);
	// 	Sets the display off
	SegDisplay_slaveDeSelect(0);
	// Deselect display chip
}

void SegDisplay_writeWord (unsigned char adress, unsigned char data)
{
	SegDisplay_slaveSelect(0);
	// Select display chip
	SegDisplay_write(adress);
	// 	digit adress: (digit place)
	SegDisplay_write(data);
	//  writes the data on the assigned adress
	SegDisplay_slaveDeSelect(0);
	// Deselect display chip
}

void SegDisplay_writeLedDisplay(int value)
{
	if (value < 0)
	{
		int absonum = abs(value);
		SegDisplay_writeWord(0x01,absonum%10);
		SegDisplay_writeWord(0x02,(absonum/10)%10);
		SegDisplay_writeWord(0x03,(absonum/100)%10);
		SegDisplay_writeWord(0x04,0x0A);
	} else // positive number
	{
		SegDisplay_writeWord(0x01,value%10);
		SegDisplay_writeWord(0x02,(value/10)%10);
		SegDisplay_writeWord(0x03,(value/100)%10);
		SegDisplay_writeWord(0x04,(value/1000)%10);
	}
	
}

void SegDisplay_writeLedScore(int score)
{
	SegDisplay_writeLedDisplay(score);
}	

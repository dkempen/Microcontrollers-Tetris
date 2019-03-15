/*
 * SegDisplay.c
 *
 * Created: 5-3-2019 14:22:50
 *  Author: Max van Noordennen
 */ 

#include <avr/io.h>
#include <util/delay.h>

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
	// or: SPCR = 0b11010010;
	// Enable spi, MasterMode, Clock rate fck/64, bitrate=125kHz
	// Mode = 0: CPOL=0, CPPH=0;
}

// Write a byte from master to slave
void spi_write(unsigned char data)
{
	SPDR = data;
	// Load byte to Data register --> starts transmission
	while( !(SPSR & BIT(SPIF)) );
	// Wait for transmission complete
}

// Write a byte from master to slave and read a byte from slave
// nice to have; not used here
char spi_writeRead(unsigned char data)
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
void spi_slaveSelect(unsigned char chipNumber)
{
	PORTB &= ~BIT(chipNumber);
}

// Deselect device on pinnumer PORTB
void spi_slaveDeSelect(unsigned char chipNumber)
{
	PORTB |= BIT(chipNumber);
}

// Initialize the driver chip (type MAX 7219)
void SegDisplay_DriverInit()
{
	spi_slaveSelect(0);
	// Select display chip (MAX7219)
	spi_write(0x09);
	// Register 09: Decode Mode
	spi_write(0xFF);
	// 	-> 1's = BCD mode for all digits
	spi_slaveDeSelect(0);
	// Deselect display chip

	spi_slaveSelect(0);
	// Select dispaly chip
	spi_write(0x0A);
	// Register 0A: Intensity
	spi_write(0x01);
	//  -> Level 4 (in range [1..F])
	spi_slaveDeSelect(0);
	// Deselect display chip

	spi_slaveSelect(0);
	// Select display chip
	spi_write(0x0B);
	// Register 0B: Scan-limit
	spi_write(0x04);
	// 	-> 1 = Display digits 0..1
	spi_slaveDeSelect(0);
	// Deselect display chip

	spi_slaveSelect(0);
	// Select display chip
	spi_write(0x0C);
	// Register 0B: Shutdown register
	spi_write(0x01);
	// 	-> 1 = Normal operation
	spi_slaveDeSelect(0);
	// Deselect display chip
}


// Set display on ('normal operation')
void SegDisplay_displayOn()
{
	spi_slaveSelect(0);
	// Select display chip
	spi_write(0x0C);
	// Register 0B: Shutdown register
	spi_write(0x01);
	// 	-> 1 = Normal operation
	spi_slaveDeSelect(0);
	// Deselect display chip
}

// Set display off ('shut down')
void SegDisplay_displayOff()
{
	spi_slaveSelect(0);
	// Select display chip
	spi_write(0x0C);
	// Register 0B: Shutdown register
	spi_write(0x00);
	// 	-> 1 = Normal operation
	spi_slaveDeSelect(0);
	// Deselect display chip
}

void SegDisplay_writeWord (unsigned char adress, unsigned char data)
{
	spi_slaveSelect(0);
	// Select display chip
	spi_write(adress);
	// 	digit adress: (digit place)
	spi_write(data);
	// 	digit value: i (= digit place)
	spi_slaveDeSelect(0);
	// Deselect display chip
}

void SegDisplay_writeLedDisplay(int value)
{
	if (value < 0)
	{
		int absonum = abs(value);
		spi_writeWord(0x01,absonum%10);
		spi_writeWord(0x02,(absonum/10)%10);
		spi_writeWord(0x03,(absonum/100)%10);
		spi_writeWord(0x04,0x0A);
	} else // positive number
	{
		spi_writeWord(0x01,value%10);
		spi_writeWord(0x02,(value/10)%10);
		spi_writeWord(0x03,(value/100)%10);
		spi_writeWord(0x04,(value/1000)%10);
	}
	
}

void SegDisplay_writeLedScore(int score)
{
	writeLedDisplay(score);
}	

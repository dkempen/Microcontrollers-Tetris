/*
 * lcd.c
 *
 * Created: 5-3-2019 19:14:25
 *  Author: Max van Noordennen
 */ 

#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

// write lcd command
void lcd_command( unsigned char byte)
{
	PORTC = byte & 0xF0;
	PORTC |= 0x08;
	
	_delay_ms(2);
	PORTC = 0x04;
	
	PORTC = (byte & 0x0F) << 4;
	PORTC |= 0x08;
	
	_delay_ms(2);
	PORTC = 0x00;
};

// writes a char to lcd
void lcd_write_char(unsigned char byte)
{
	PORTC = byte & 0xF0;
	PORTC = PORTC | 0x0C;

	_delay_ms(2);
	PORTC = 0x04;
	PORTC = (byte & 0x0F) << 4;
	PORTC = PORTC | 0x0C;

	_delay_ms(2);
	PORTC = 0x00;
}

// init the lcd
void lcd_init()
{
	DDRC = 0xFF;
	PORTC = 0x00;

	// Cursor Home
	lcd_command(0x02); // sets the DDRAM to location 0
	//Function set
	lcd_command(0x28);// mode: 
					  //4 bits interface data
					  //2 lines 
					  //5x8 dots
	// display ON/OFF
	lcd_command(0x0C);//mode: 
					  //display on 
					  //cursor off 
					  //blinking off
	// entry set 
	lcd_command( 0x06 );//mode: 
						//cursor to right 
						//no shift
	
	// Set DDRAM adress: 
	lcd_command(0x80); //mode: 
					   //0 
					   //first position
					   //line 1
	lcd_clear();
}

// writes string on lcd
void lcd_write_string(char *str)
{
	for(; *str; str++){
		lcd_write_char(*str);
	}
}

// sets the cursor on lcd
void lcd_set_cursor(int position)
{
	
	if(position >= 16)
	{
		lcd_command(0xc0 + (position - 16));
	}
	else
	{
		lcd_command(0x80 + position);
	}
	
}
// clears the lcd
 void lcd_clear()
 {
	 lcd_command(0x01);
 }

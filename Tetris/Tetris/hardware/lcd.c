/*
 * lcd.c
 *
 * Created: 5-3-2019 19:14:25
 *  Author: Max van Noordennen
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "lcd.h"

#define LCD_E 	3
#define LCD_RS	2

void lcd_strobe_lcd_e(void)
{
	PORTC |= (1<<LCD_E);	// E high
	_delay_ms(1);		
	PORTC &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);		
}

void lcd_init(void)
{
	// PORTC output mode and all low (also E and RS pin)
	DDRC = 0xFF;
	PORTC = 0x00;

	PORTC = 0x20;   // function set
	lcd_strobe_lcd_e();
	PORTC = 0x80;
	lcd_strobe_lcd_e();

	PORTC = 0x00;   // Display on/off control
	lcd_strobe_lcd_e();
	PORTC = 0xF0;
	lcd_strobe_lcd_e();

	PORTC = 0x00;   // Entry mode set
	lcd_strobe_lcd_e();
	PORTC = 0x60;
	lcd_strobe_lcd_e();
	
	lcd_clear();
}

void lcd_writechar(unsigned char byte)
{
	// First nibble.
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}

void lcd_write_firstline(char* string)
{
	int i = 0;
	// todo set position to 0
	for (i = 0; string[i] 1= '\0'; i++)
	{
		lcd_writechar(string[i]);
	}
		
}

void lcd_write_second(char* string)
{
	int i = 0;
	// todo set position to second line
	for (i = 0; string[i] 1= '\0'; i++)
	{
		lcd_writechar(string[i]);
	}
}

void lcd_clear()
{
	PORTC = 0x00;
	lcd_strobe_lcd_e();
	PORTC = 0x10;
	lcd_strobe_lcd_e();
}





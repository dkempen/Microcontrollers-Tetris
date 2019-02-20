/*
 * ldc.c
 *
 * Created: 13-Feb-19 16:53:57
 *  Author: Daan
 */

#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "lcd.h"

#define LCD_E 	3
#define LCD_RS	2

static unsigned char charset[] =
{
	0x1D, 0x05, 0x05, 0x1F, 0x14, 0x14, 0x17, 0x00,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
};

void lcd_strobe_lcd_e(void)
{
	PORTC |= (1<<LCD_E);	// E high
	_delay_ms(1);			// nodig
	PORTC &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);			// nodig?
}

void lcd_init(void)
{
	// PORTC output mode and all low (also E and RS pin)
	DDRC = 0xFF;
	PORTC = 0x00;

	// Step 2 (table 12)
	//PORTC = 0x20;	// function set
	//lcd_strobe_lcd_e();

	// Step 3 (table 12)
	PORTC = 0x20;   // function set
	lcd_strobe_lcd_e();
	PORTC = 0x80;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Display on/off control
	lcd_strobe_lcd_e();
	PORTC = 0xF0;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Entry mode set
	lcd_strobe_lcd_e();
	PORTC = 0x60;
	lcd_strobe_lcd_e();
	
	lcd_clear();
}

void lcd_clear()
{
	PORTC = 0x00;
	lcd_strobe_lcd_e();
	PORTC = 0x10;
	lcd_strobe_lcd_e();
	lcd_fillCGrom(charset);
}

void lcd_write_string(char *str)
{
	for(;*str; str++)
		lcd_write_data(*str);
}

void lcd_write_data(unsigned char byte)
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

void lcd_write_command(unsigned char byte)
{
	// First nibble.
	PORTC = byte;
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();
}

void lcd_set_cursor(int position)
{
	if (position >= 0 && position < 16)
		lcd_write_command(position + 128);
	else if (position < 32)
		lcd_write_command(position + 192 - 16);
}

void lcd_fillCGrom(unsigned char* charmap)
{
	lcd_write_command(0x40); // adres 0 van CG-RAM
	unsigned int sz =  sizeof(charmap) / sizeof(char);
	for (int ch = 0; ch < sz ; ch++)
		lcd_write_data(charmap[ch]); // schrijf data in CG-RAM
}

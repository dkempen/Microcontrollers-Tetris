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

void lcd_clear()
{
	PORTC = 0x00;
	lcd_strobe_lcd_e();
	PORTC = 0x10;
	lcd_strobe_lcd_e();
}

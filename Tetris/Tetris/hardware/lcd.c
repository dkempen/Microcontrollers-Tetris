/*
 * lcd.c
 *
 * Created: 5-3-2019 19:14:25
 *  Author: Max van Noordennen
 */ 

#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "EasyBuzz.h"

#include "lcd.h"

#define LCD_E 	3
#define LCD_RS	2

// used for custom chars
static unsigned char charset[] =
{
	
};

void lcd_strobe_lcd_e(void)
{
	PORTC |= (1<<LCD_E);	// Enable high
	_delay_ms(1);		
	PORTC &= ~(1<<LCD_E);  	// Enable low
	_delay_ms(1);		
}

void lcd_init(void)
{
	// PORTC output mode and all low, as well as Enable pin and Register select pin
	DDRC = 0xFF;
	PORTC = 0x00;

	//_delay_ms(30);

	//_delay_ms(10);
	PORTC = 0b00000010;
	//lcd_strobe_lcd_e();
	_delay_ms(15);
	
	PORTC = 0x20;
	lcd_strobe_lcd_e();	
	
	// Sets Data length, number of display lines and character font
	PORTC = 0x20;   // function set
					// Data is sent or received in 4 bit length
					// Sets numbers of lines to 2
					// Font is set to 5x 7 dots
	lcd_strobe_lcd_e();
	PORTC = 0x80;						
	lcd_strobe_lcd_e();
	
	// Controls display of characters and cursor
	PORTC = 0x00;   // Display on/off control
	lcd_strobe_lcd_e();
	PORTC = 0xF0;	// The display is on
					// The cursor is displayed
					// The character at the cursor position blinks
	lcd_strobe_lcd_e();
	
	// Sets the cursor move direction and specify to shift or not shift the display
	PORTC = 0x00;   // Entry mode set
	lcd_strobe_lcd_e();
	PORTC = 0x60;	// Specifies the increment 1 = incement 0 = derement
					// The display will be shifted to left when 1 en increment is 1,
					// if decrement then it will shift to the right
	lcd_strobe_lcd_e();
	
	lcd_clear();
}

// Clears the display
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
	//Loop for 16 characters
	int i = 0;
	for(;i < 16; i++)
	lcd_write_data(*(str + i));
}

void lcd_write_line1(char *str){
	lcd_set_cursor(0);
	lcd_write_string(str);
}

void lcd_write_line2(char *str){
	lcd_set_cursor(16);
	lcd_write_string(str);
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


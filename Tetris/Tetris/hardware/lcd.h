/*
 * lcd.h
 *
 * Created: 5-3-2019 19:15:53
 *  Author: Max van Noordennen
 */ 


#ifndef LCD_H_
#define LCD_H_

/*
	Function is used for initializing lcd screen,
	This lcd screen is initialized in 4-bit
	When 4- bit is selected, the data must be sent or received in pairs of 4-bit each.
	The most-significant 4 bits are sent of received first.
*/
void lcd_init(void);

/*
	Clears all display and returns the cursor to the home position
*/
void lcd_clear(void);

/*
	This function is used to set the Enable pin to and low
*/
void lcd_strobe_lcd_e(void);

/*
	Writes to the screen
	Note: cannot take strings larger than 16 characters
*/
void lcd_write_string(char *str);

/*
	Write to the first line of the screen [cannot be longer than 16 characters]
*/
void lcd_write_line1(char *str);

/*
	Write to the second line of the screen [cannot be longer than 16 characters]
*/
void lcd_write_line2(char *str);

/*
	Writes the data for a single char
	input: unsigned char byte
*/
void lcd_write_data(unsigned char byte);

/*
	Writes a command to lcd
	input: unsigned char byte
*/
void lcd_write_command(unsigned char byte);

/*
	Function for setting the cursor to wanted spot 
	input: int
*/
void lcd_set_cursor(int);

/*
	Function for writing data to GC ram
	input: unsigned char* charmap
*/
void lcd_fillCGrom(unsigned char* charmap);


#endif /* LCD_H_ */
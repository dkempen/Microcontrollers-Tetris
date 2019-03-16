/*
 * lcd.h
 *
 * Created: 5-3-2019 19:15:53
 *  Author: Max van Noordennen
 */ 


#ifndef LCD_H_
#define LCD_H_

void lcd_init(void);
void lcd_clear(void);
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
void lcd_write_data(unsigned char byte);
void lcd_write_command(unsigned char byte);
void lcd_set_cursor(int);
void lcd_fillCGrom(unsigned char* charmap);


#endif /* LCD_H_ */
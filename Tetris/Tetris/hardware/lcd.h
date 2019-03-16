/*
 * lcd.h
 *
 * Created: 5-3-2019 19:15:53
 *  Author: Max van Noordennen
 */ 


#ifndef LCD_H_
#define LCD_H_

void lcd_clear(void);
void lcd_writechar(unsigned char byte);
void lcd_strobe_lcd_e(void);
void lcd_write_secondline(char* string);
void lcd_write_firstline(char* string);
void lcd_set_cursor(int position);
void lcd_init(void);
void lcd_write_command(unsigned char byte);
void lcd_write_data(unsigned char byte);
void lcd_fillCGrom(unsigned char* charmap);



#endif /* LCD_H_ */
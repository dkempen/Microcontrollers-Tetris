/*
 * lcd.h
 *
 * Created: 13-Feb-19 16:54:18
 *  Author: Daan
 */ 

void lcd_init(void);
void lcd_clear(void);
void lcd_strobe_lcd_e(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_command(unsigned char byte);
void lcd_set_cursor(int);
void lcd_fillCGrom(unsigned char* charmap);

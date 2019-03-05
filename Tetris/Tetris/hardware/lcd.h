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



#endif /* LCD_H_ */
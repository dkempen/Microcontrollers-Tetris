/*
 * lcd.h
 *
 * Created: 5-3-2019 19:15:53
 *  Author: Max van Noordennen
 */ 


#ifndef LCD_H_
#define LCD_H_


/*
 *  Function is used for initializing lcd screen,
 *	This lcd screen is initialized in 4-bit
 *	When 4- bit is selected, the data must be sent or received in pairs of 4-bit each.
 *	The most-significant 4 bits are sent of received first.
 *	input: unsigned char byte
 */
void lcd_command( unsigned char byte);

/*
 * This function writes a character on the display
 *input: unsigned char byte
 */
void lcd_write_char(unsigned char byte);


/**
 *  This function is used for initing the display
 */
void lcd_init();


/**
 * This function displays a string on the display
 * input: char *str
 */
void lcd_write_string(char *str);

/**
 *  This function sets the cursor on the position
 *  input: int position
 */
void lcd_set_cursor(int position);

/**
 *  This function clears the display
 */
void lcd_clear(void);


#endif /* LCD_H_ */
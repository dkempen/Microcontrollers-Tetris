/*
 * SegDisplay.h
 *
 * Created: 5-3-2019 14:24:40
 *  Author: Max van Noordennen
 */ 


#ifndef SEGDISPLAY_H_
#define SEGDISPLAY_H_

/*
	Initializes the Segment Display
*/
void SegDisplay_Init(void);

/*
	Initializes all the slaves
*/
void SegDisplay_masterInit(void);

/*
	Initializes the chip, and setting all wanted mode's
*/
void SegDisplay_DriverInit(void);

/*
	Sets the display to on
*/
void SegDisplay_displayOn(void);

/*
	Sets the display to off
*/
void SegDisplay_Off(void);

/*
	Writes a word on the Segment display
	
	@param unsigned char adress - this parameter is for setting the adress where the data needs to be written
	
	@param unsigned char data - this parameter is the data that needs to be written on the given adress
*/
void SegDispay_writeWord (unsigned char adress, unsigned char data);

/*
	Writes the desired number on the Segment display
	
	@param int value - this parameter sets the desired value on the display
*/
void SegDisplay_writeLedDisplay(int value);

/*
	Writes to score on the Segment display
*/
void SegDisplay_writeLedScore(int score);



#endif /* SEGDISPLAY_H_ */
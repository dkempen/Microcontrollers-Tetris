/*
 * SegDisplay.h
 *
 * Created: 5-3-2019 14:24:40
 *  Author: Max van Noordennen
 */ 


#ifndef SEGDISPLAY_H_
#define SEGDISPLAY_H_

void SegDisplay_Init(void);
void SegDisplay_masterInit(void);
void SegDisplay_DriverInit(void);
void SegDisplay_displayOn(void);
void SegDisplay_Off(void);
void SegDispay_writeWord (unsigned char adress, unsigned char data);
void SegDisplay_writeLedDisplay(int value);
void SegDisplay_writeLedScore(int score);



#endif /* SEGDISPLAY_H_ */
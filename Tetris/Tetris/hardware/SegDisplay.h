/*
 * SegDisplay.h
 *
 * Created: 5-3-2019 14:24:40
 *  Author: Max van Noordennen
 */ 


#ifndef SEGDISPLAY_H_
#define SEGDISPLAY_H_

void SegDisplay_Init(void);
void spi_masterInit(void);
void spi_write(unsigned char data);
char spi_writeRead(unsigned char data);
void spi_slaveSelect(unsigned char chipNumber);
void spi_slaveDeSelect(unsigned char chipNumber);
void displayDriverInit(void);
void displayOn(void);
void displayOff(void);
void spi_writeWord (unsigned char adress, unsigned char data);
void writeLedDisplay(int value);
void writeLedScore(int score);



#endif /* SEGDISPLAY_H_ */
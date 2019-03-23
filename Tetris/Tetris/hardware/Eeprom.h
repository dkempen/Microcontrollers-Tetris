/*
 * Eeprom.h
 *
 * Created: 20-3-2019 13:35:50
 *  Author: Ian
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

/*
	Writes the high scores into non-volatile memory
	
	@param highScores - The high scores that are to be written into non-volatile memory
	@param size - The amount of high scores that will be written
*/
void WriteHighScores(int *highScores, int size);

/*
	Reads the high scores from non-volatile memory
	
	@param highScores - An empty object that will store the high scores that are read from non-volatile memory
	@param size - The amount of high scores that will be read
*/
void ReadHighScores(int *highScores, int size);




#endif /* EEPROM_H_ */
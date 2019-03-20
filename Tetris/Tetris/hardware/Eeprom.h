/*
 * Eeprom.h
 *
 * Created: 20-3-2019 13:35:50
 *  Author: Aspire V3-772G-747a8
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

/*
	Writes the highscores into non-volatile memory
*/
void WriteHighScores(int *highScores, int size);

/*
	Reads the highscores from non-volatile memory
*/
void ReadHighScores(int *highScores, int size);




#endif /* EEPROM_H_ */
/*
 * DotMatrix.h
 *
 * Created: 20-Feb-19 15:13:11
 * Author: Daan
 */ 

#ifndef DOT_MATRIX_H_
#define DOT_MATRIX_H_

#define FIELD_WIDTH		8	// Temporary defines for the size of the game field
#define FIELD_HEIGHT	16	// TODO: get defines from game logic

void matrix_init(void);
void matrix_test(void);
void matrix_clear(void);
void matrix_fill(void);
void matrix_draw_game_field(int [FIELD_WIDTH][FIELD_HEIGHT]);

#endif /* DOT_MATRIX_H_ */

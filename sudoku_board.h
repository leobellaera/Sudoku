#ifndef _SUDOKU_BOARD_H_
#define _SUDOKU_BOARD_H_

#include "cell.h"

typedef struct{
	cell_t cells[9][9];
} sudoku_board_t;

void sudoku_board_init(sudoku_board_t* board, 
	int matrix[9][9]);

int sudoku_board_put(sudoku_board_t* board, 
	int number, int row, int column);

int sudoku_board_verify(sudoku_board_t* board);

void sudoku_board_restart(sudoku_board_t* board);

void sudoku_board_get(sudoku_board_t* board, 
	int matrix[9][9]);

#endif

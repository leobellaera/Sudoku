#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include "cell.h"

typedef struct sudoku {
	cell_t board[9][9];
} sudoku_t;

void sudoku_init(sudoku_t* sudoku, int matrix[9][9]);

int sudoku_put(sudoku_t* sudoku, int number, int row, int column);

int sudoku_verify(sudoku_t* sudoku);

void sudoku_restart(sudoku_t* sudoku);

void sudoku_show_board(sudoku_t* sudoku, int matrix[9][9]);

#endif
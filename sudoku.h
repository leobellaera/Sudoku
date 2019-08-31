#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include "column.h"
#include "row.h"
#include "sector.h"

typedef struct sudoku {
	row_t rows[9];
	column_t columns[9];
	sector_t sectors[3][3]; //sectors matrix
} sudoku_t;

int sudoku_init(sudoku_t* sudoku, int **matrix); //Necesitaremos un parser que cuando levante el archivo lo convierta a una matriz de enteros

int sudoku_put(sudoku_t* sudoku, int number, int row, int column);

int sudoku_verify(sudoku_t* sudoku);

void sudoku_restart(sudoku_t* sudoku);

#endif
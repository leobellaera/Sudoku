#ifndef _SUDOKU_MATRIX_OPERATOR_
#define _SUDOKU_MATRIX_OPERATOR_

void matrix_get_column(int** sudoku_matrix, int* ptr, int column);

void matrix_get_row(int** sudoku_matrix, int* ptr, int row);

void get_sector(int** sudoku_matrix, int** ptr, int i, int j);

int get_sector_row(int matrix_row);

int get_sector_column(int matrix_column);

#endif

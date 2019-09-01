#ifndef _SUDOKU_MATRIX_OPERATOR_
#define _SUDOKU_MATRIX_OPERATOR_

void matrix_get_column(int sudoku_matrix[9][9], int* ptr, int column);

void matrix_get_row(int sudoku_matrix[9][9], int* ptr, int row);

void matrix_get_sector(int sudoku_matrix[9][9], int ptr[3][3], int i, int j);

int get_sector_row(int matrix_row);

int get_sector_column(int matrix_column);

#endif

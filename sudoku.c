#include "sudoku.h"
#include <stdlib.h>
#include "sudoku_matrix_operator.h"

sector_t* sudoku_get_sector(sudoku_t* sudoku, int row, int column);

int get_sector_index(int i);

void columns_init(sudoku_t* sudoku, int matrix[9][9]);

void rows_init(sudoku_t* sudoku, int matrix[9][9]);

void sectors_init(sudoku_t* sudoku, int matrix[9][9]);


void sudoku_init(sudoku_t* sudoku, int matrix[9][9]){
	columns_init(sudoku, matrix);
	rows_init(sudoku, matrix);
	sectors_init(sudoku, matrix);
}

void columns_init(sudoku_t* sudoku, int matrix[9][9]) {
	int aux[9];
	for (int i = 0; i < 9; i++) {
		matrix_get_column(matrix, aux, i);
		column_init(&sudoku->columns[i], aux);
	}
}

void rows_init(sudoku_t* sudoku, int matrix[9][9]) {
	int aux[9];
	for (int i = 0; i < 9; i++) {
		matrix_get_row(matrix, aux, i);
		row_init(&sudoku->rows[i], aux);
	}
}

void sectors_init(sudoku_t* sudoku, int matrix[9][9]) {
	int aux_matrix[3][3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			matrix_get_sector(matrix, aux_matrix, i, j);
			sector_init(&sudoku->sectors[i][j], aux_matrix);
		}
	}
}

int sudoku_put(sudoku_t* sudoku, int number, int row, int column) {
	if (row_add_number(&sudoku->rows[row], number, column) == 1) { //cell is unmodifiable
		return 1;
	}
	column_add_number(&sudoku->columns[column], number, row);

	int sector_row = get_sector_column(column);
	int sector_column = get_sector_row(row);
	sector_add_number(sudoku_get_sector(sudoku, row, column), number, sector_row, sector_column);
	
	return 0;
}

int sudoku_verify(sudoku_t* sudoku) {
	int i;
	for (i = 0; i < 9; i++) {
		if (!row_is_valid(&sudoku->rows[i]) || !column_is_valid(&sudoku->columns[i])) {
			return 1;
		}
	}
	for (i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (!sector_is_valid(&sudoku->sectors[i][j])) {
				return 1;
			}
		}
	}
	return 0;
}

void sudoku_restart(sudoku_t* sudoku) {
	int i;
	int j;
	for (i=0; i<9; i++) {
		row_restart_cells(&sudoku->rows[i]);
		column_restart_cells(&sudoku->columns[i]);
	}
	for (i=0; i<3; i++) {
		for (j=0; j<3; j++) {
			sector_restart_cells(&sudoku->sectors[i][j]);
		}
	}
}

sector_t* sudoku_get_sector(sudoku_t* sudoku, int row, int column) {
	return &sudoku->sectors[get_sector_index(row)][get_sector_index(column)];
}

int get_sector_index(int i) {
	if (i<=2) return 0;
	else if (i>2 && i<=5) return 1;
	else return 2;
}
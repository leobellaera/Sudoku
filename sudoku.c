#include "sudoku.h"
#include <stdlib.h>


//forward declarations
sector_t* sudoku_get_sector(sudoku_t* sudoku, int row, int column);
int get_index(int number);

int sudoku_init(sudoku_t* sudoku, int **matrix){
	//int i;
	//for (i=0; i<9)..
		//row_init(matrix[i])
		//sector_init(ma)
}

int put(sudoku_t* sudoku, int number, int row, int column) {
	if (row_add_number(&sudoku->rows[row], number, column) == 1) { //cell is unmodifiable
		return 1;
	}
	column_add_number(&sudoku->column[column], number, row);
	sector_add_number(sudoku_get_sector(sudoku, row, column), number);
	return 0;
}

int verify(sudoku_t* sudoku) {
	int i = 0;
	for (i; i<9; i++) {
		if (!row_is_valid(&sudoku->rows[i]) || !column_is_valid(&sudoku->columns[i])) {
			return 1;
		}
	}
	for (i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			if (!sector_is_valid(&sudoku->sectors[i][j])){
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

int get_index(int number) {
	if (number<=2) return 0;
	else if (number>2 && number<=5) return 1;
	else if (number>5) return 2;
}

sector_t* sudoku_get_sector(sudoku_t* sudoku, int row, int column) {
	return &sudoku->sectors[get_index(row)],get_index(column)];
}
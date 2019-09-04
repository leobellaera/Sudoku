#include "sudoku.h"
#include <stdbool.h>
#include <stdio.h>

bool row_is_valid(sudoku_t* sudoku, int row_index);
bool column_is_valid(sudoku_t* sudoku, int column_index);
bool sector_is_valid(sudoku_t* sudoku, int sector_number);
void put_sector_cells_in_array(sudoku_t* sudoku, int sector_number, cell_t* array);

void sudoku_init(sudoku_t* sudoku, int matrix[9][9]){
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int numb = matrix[i][j];
			if (numb == 0) {
				cell_init(&sudoku->board[i][j], numb, true);
			} else {
				cell_init(&sudoku->board[i][j], numb, false);
			}
		}
	}
}


int sudoku_put(sudoku_t* sudoku, int number, int row, int column) {
	cell_t* cell = &sudoku->board[row - 1][column - 1];
	if (!cell_is_modifiable(cell)) {
		return 1;
	}
	cell_set_number(cell, number);
	return 0;
}

int sudoku_verify(sudoku_t* sudoku) {
	int i;
	for (i = 0; i < 9; i++) {
		if (!row_is_valid(sudoku, i) || !column_is_valid(sudoku, i)) {
			return 1;
		}
	}
	for (i = 0; i < 3; i++) {
		if (!sector_is_valid(sudoku, i)) {
			return 1;
		}
	}
	return 0;
}

bool row_is_valid(sudoku_t* sudoku, int row_index) {
	int j;
	for (int i = 0; i < 9; i++) {
        for (j = i + 1; j < 9; j++) {
        	if (!cell_is_valid(&sudoku->board[row_index][i], &sudoku->board[row_index][j])) {
        		return false;
        	}
        }
   	}
   	return true;
}

bool column_is_valid(sudoku_t* sudoku, int column_index) {
	int j;
	for (int i = 0; i < 9; i++) {
        for (j = i + 1; j < 9; j++) {
        	if (!cell_is_valid(&sudoku->board[i][column_index], &sudoku->board[j][column_index])) {
        		return false;
        	}
        }
   	}
   	return true;
}

bool sector_is_valid(sudoku_t* sudoku, int sector_number) {
	int i, j;
	cell_t aux[9];
	put_sector_cells_in_array(sudoku, sector_number, aux);
	for (i = 0; i < 9; i++) {
        for (j = i + 1; j < 9; j++) {
        	if (!cell_is_valid(&aux[i], &aux[j])) {
        		return false;
        	}
        }
    }
    return true;
}

void put_sector_cells_in_array(sudoku_t* sudoku, int sector_number, cell_t* array) {
	int idx = sector_number * 3;
	int final_idx = idx + 3;
	int actual_pos = 0;
	for (int i = idx; i < final_idx; i++) {
		for (int j = idx; j < final_idx; j++) {
			array[actual_pos] = sudoku->board[i][j];
			actual_pos++;
		}
	}
}

void sudoku_restart(sudoku_t* sudoku) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cell_restart(&sudoku->board[i][j]);
		}
	}
}

void sudoku_show_board(sudoku_t* sudoku, int matrix[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			matrix[i][j] = cell_get_number(&sudoku->board[i][j]);
		}
	}
}
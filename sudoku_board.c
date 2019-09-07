#include "sudoku_board.h"
#include <stdbool.h>
#include <stdio.h>

bool row_is_valid(sudoku_board_t* board, int row_index);
bool column_is_valid(sudoku_board_t* board, int column_index);
bool sector_is_valid(sudoku_board_t* board, int sector_number);
void put_sector_cells_in_array(sudoku_board_t* board, 
	int sector_number, cell_t* array);

void sudoku_board_init(sudoku_board_t* board, int matrix[9][9]){
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int numb = matrix[i][j];
			if (numb == 0) {
				cell_init(&board->cells[i][j], numb, true);
			} else {
				cell_init(&board->cells[i][j], numb, false);
			}
		}
	}
}


int sudoku_board_put(sudoku_board_t* board, int number, 
	int row, int column) {
	cell_t* cell = &board->cells[row - 1][column - 1];
	if (cell_set_number(cell, number) == 1) {
		return 1;
	}
	return 0;
}

int sudoku_board_verify(sudoku_board_t* board) {
	int i;
	for (i = 0; i < 9; i++) {
		if (!row_is_valid(board, i) || !column_is_valid(board, i)) {
			return 1;
		}
	}
	for (i = 0; i < 3; i++) {
		if (!sector_is_valid(board, i)) {
			return 1;
		}
	}
	return 0;
}

bool row_is_valid(sudoku_board_t* board, int row_index) {
	int j;
	for (int i = 0; i < 9; i++) {
        for (j = i + 1; j < 9; j++) {
        	if (!cell_is_valid(&board->cells[row_index][i], 
        		&board->cells[row_index][j])) {
        		return false;
        	}
        }
   	}
   	return true;
}

bool column_is_valid(sudoku_board_t* board, int column_index) {
	int j;
	for (int i = 0; i < 9; i++) {
        for (j = i + 1; j < 9; j++) {
        	if (!cell_is_valid(&board->cells[i][column_index], 
        		&board->cells[j][column_index])) {
        		return false;
        	}
        }
   	}
   	return true;
}

bool sector_is_valid(sudoku_board_t* board, int sector_number) {
	int i, j;
	cell_t aux[9];
	put_sector_cells_in_array(board, sector_number, aux);
	for (i = 0; i < 9; i++) {
        for (j = i + 1; j < 9; j++) {
        	if (!cell_is_valid(&aux[i], &aux[j])) {
        		return false;
        	}
        }
    }
    return true;
}

void put_sector_cells_in_array(sudoku_board_t* board, 
	int sector_number, cell_t* array) {
	int idx = sector_number * 3;
	int final_idx = idx + 3;
	int actual_pos = 0;
	for (int i = idx; i < final_idx; i++) {
		for (int j = idx; j < final_idx; j++) {
			array[actual_pos] = board->cells[i][j];
			actual_pos++;
		}
	}
}

void sudoku_board_restart(sudoku_board_t* board) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cell_restart(&board->cells[i][j]);
		}
	}
}

void sudoku_board_get(sudoku_board_t* board, int matrix[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			matrix[i][j] = cell_get_number(&board->cells[i][j]);
		}
	}
}

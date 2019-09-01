#include "sudoku_matrix_operator.h"

int transform_sector_index(int i);

void matrix_get_column(int sudoku_matrix[9][9], int* ptr, int column) {
	for (int i = 0; i < 9; i++) {
		ptr[i] = sudoku_matrix[i][column];
	}
}

void matrix_get_row(int sudoku_matrix[9][9], int* ptr, int row) {
	for (int i = 0; i < 9; i++) {
		ptr[i] = sudoku_matrix[row][i];
	}
}

void matrix_get_sector(int sudoku_matrix[9][9], int ptr[3][3], int i, int j) {
	int n = i*3;
	int m = j*3;
	for (int k = 0; k < 3; k++) {
		for (int l = 0; l < 3; l++) {
			ptr[k][l] = sudoku_matrix[n+k][m+l];
		}
	}
}

int get_sector_row(int matrix_row) {
	return transform_sector_index(matrix_row);
}

int get_sector_column(int matrix_column) {
	return transform_sector_index(matrix_column);
}

int transform_sector_index(int i) {
	if ((i%3) == 0) {
		return 0;
	}
	else if (i == 1 || i == 4 || i == 7) {
		return 1;
	}
	else {
		return 2;
	}
}
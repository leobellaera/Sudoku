#include "sudoku_matrix_loader.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define ERROR 1
#define SUCCESS 0
#define MATRIX_FILE_PATH "board.txt"
#define BUFFER_SIZE 19

#define MATRIX_LOAD_ERROR_MSG "Error while reading matrix data\n"

int load_file_in_matrix(FILE* file, int matrix[9][9]);
void load_line_in_matrix(const char* buffer, int* matrix_row);
FILE* open_file();

int load_sudoku_matrix(int matrix[9][9]) {
	FILE* matrix_file = open_file();
	if (!matrix_file) {
		return ERROR;
	}
	if (load_file_in_matrix(matrix_file, matrix) == ERROR) {
		return 1;
	}
	return 0;
}

int load_file_in_matrix(FILE* file, int matrix[9][9]){	
	char buffer[BUFFER_SIZE];
	int i = 0;
	while (fgets(buffer, BUFFER_SIZE, file)) {
		load_line_in_matrix(buffer, matrix[i]);
		i++;
	}
	fclose(file);
	if (i < 8) {
		fprintf(stderr, MATRIX_LOAD_ERROR_MSG);
		return ERROR;
	}
	return SUCCESS;
}

FILE* open_file() {
	FILE* matrix_file = fopen(MATRIX_FILE_PATH, "r");
	if (!matrix_file) {
		fprintf(stderr, MATRIX_LOAD_ERROR_MSG);
		return NULL;
	}
	return matrix_file;
}

void load_line_in_matrix(const char* buffer, int* matrix_row) {
	int i = 0;
	for (int j = 0; j <= 16; j+=2) {
		matrix_row[i] = buffer[j] - '0'; //ascii code fix
		i++;
	}
}

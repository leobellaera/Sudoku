#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define BOARD_REPR_SIZE 723

void add_sector_separator(char* buffer);
void add_normal_separator(char* buffer);
void add_matrix_row(char* buffer, int matrix[9][9], int row_index);
void iterate_row_representation(char* row_representation, int* row, int len);

char* assemble_board_representation(int matrix[9][9]) {
	char* board_representation = malloc(sizeof(char)*BOARD_REPR_SIZE);
	int matrix_row_index = 0;
	for (int i = 0; i < 19; i++) {
		int actual_index = i*38;
		if (i % 6 == 0) {
			add_sector_separator(&board_representation[actual_index]);
		}
		else if (i % 2 == 0) {
			add_normal_separator(&board_representation[actual_index]);
		}
		else {
			add_matrix_row(&board_representation[actual_index], matrix, matrix_row_index);
			matrix_row_index += 1;
		}
	}
	board_representation[722] = '\0';
	return board_representation;
}

void add_sector_separator(char* buffer) {
	char sector_separator[] = "U===========U===========U===========U\n";
	size_t len = strlen(sector_separator);
	for (int i = 0; i < len; i++) {
		buffer[i] = sector_separator[i];
	}
}

void add_normal_separator(char* buffer) {
	char normal_separator[] = "U---+---+---U---+---+---U---+---+---U\n";
	size_t len = strlen(normal_separator);
	for (int i = 0; i < len; i++) {
		buffer[i] = normal_separator[i];
	}
}

void add_matrix_row(char* buffer, int matrix[9][9], int row_index) {
	char row_representation[] = "U   |   |   U   |   |   U   |   |   U\n";
	size_t len = strlen(row_representation);
	iterate_row_representation(row_representation, matrix[row_index], len);
	for (int i = 0; i < len; i++) {
		buffer[i] = row_representation[i];
	}
}


void iterate_row_representation(char* row_representation, int* row, int len) {
	int i = 2;
	int j = 0;
	char aux[2];
	while (i < len) {
		if (row[j] != 0) {
			snprintf(aux, 2, "%d", row[j]);
			row_representation[i] = aux[0];
		}
		i += 4;
		j++;
	}
}
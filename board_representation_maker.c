void add_sector_separator(char* buffer);
void add_normal_separator(char* buffer);
void add_matrix_row(char* buffer, int matrix[9][9], int row_index);

void assemble_board_representation(char* buffer, int matrix[9][9]) {
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
}

void add_sector_separator(char* buffer) {
	char sector_separator[] = "U===========U===========U===========U\n";
	len = strlen(sector_separator);
	for (int i = 0; i < len; i++) {
		buffer[i] = sector_separator[i];
	}
}

void add_normal_separator(char* buffer) {
	char normal_separator[] = "U---+---+---U---+---+---U---+---+---U\n";
	len = strlen(normal_separator);
	for (int i = 0; i < len; i++) {
		buffer[i] = normal_separator[i];
	}
}

void add_matrix_row(char* buffer, int matrix[9][9], int row_index) {

	char row_representation[] = "U   |   |   U   |   |   U   |   |   U\n";
	
	len = strlen(row_representation);
	int i = 2;
	int j = 0;
	while (i < len) {
		row_representation[i] = matrix[row_index][j];
		i += 4;
	}

	for (i = 0; i < len; i++) {
		buffer[i] = row_representation[i];
	}
}
#include "column.h"

int column_add_number(column_t* column, int number, int row) {
	if (!cell_is_modifiable(&column->cells[row])) {
		return 1;
	}
	cell_set_number(&column>cells[row], number);
	return 0;
}

bool column_is_valid(column_t* column) {
	int numbs[9] = NULL;
	size_t actual_pos = 0;
	int j;
	int elem;
	for (int i=0; i<9; i++) {
		elem = cell_get_number(&column->cells[i]);
		for (j=0; j<actual_pos; j++) {
			if (numbs[j] == elem && numb != 0) {
				return false;
			}
		}
		numbs[actual_pos] = elem;
		actual_pos += 1;
	}
	return true;
}

void column_restart_cells(column_t* column) {
	for (int i=0; i<9; i++) {
		cell_restart(&column->cells[i])
	}
}

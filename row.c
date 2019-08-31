#include "row.h"

int row_add_number(row_t* row, int number, int column) {
	if (!cell_is_modifiable(&row->cells[column])) {
		return 1;
	}
	cell_set_number(&row->cells[column], number);
	return 0;
}

bool row_is_valid(row_t* row) {
	int numbs[9] = NULL;
	size_t actual_pos = 0;
	int j;
	int numb;
	for (int i=0; i<9; i++) {
		numb = cell_get_number(&row->cells[i]);
		for (j=0; j<actual_pos; j++) {
			if (numbs[j] == numb && numb!= 0) {
				return false;
			}
		}
		numbs[actual_pos] = numb;
		actual_pos += 1;
	}
	return true;
}

void row_restart_cells(row_t* row) {
	for (int i=0; i<9; i++) {
		cell_restart(&row->cells[i])
	}
}

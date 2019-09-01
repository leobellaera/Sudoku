#include "row.h"

void row_init(row_t* row, int* elements) {
	int elem;
	for (int i=0; i<9; i++) {
		elem = elements[i];
		if (elem == 0) {
			cell_init(&row->cells[i], elem, true);
		} else {
			cell_init(&row->cells[i], elem, false);
		}
	}
}

int row_add_number(row_t* row, int number, int pos) {
	if (!cell_is_modifiable(&row->cells[pos])) {
		return 1;
	}
	cell_set_number(&row->cells[pos], number);
	return 0;
}

bool row_is_valid(row_t* row) {
	int j;
	for (int i = 0; i < 9; i++) {
        for (j = i + 1; j < 9; j++) {
        	if (!cell_is_valid(&row->cells[i], &row->cells[j])) {
        		return false;
        	}
        }
   	}
   	return true;
}

void row_restart_cells(row_t* row) {
	for (int i=0; i<9; i++) {
		cell_restart(&row->cells[i]);
	}
}

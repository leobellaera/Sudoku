#include "column.h"

void column_init(column_t* column, int* elements) {
	int elem;
	for (int i=0; i<9; i++) {
		elem = elements[i];
		if (elem == 0) {
			cell_init(&column->cells[i], elem, true);
		} else {
			cell_init(&column->cells[i], elem, false);
		}
	}
}

int column_add_number(column_t* column, int number, int pos) {
	if (!cell_is_modifiable(&column->cells[pos])) {
		return 1;
	}
	cell_set_number(&column->cells[pos], number);
	return 0;
}

bool column_is_valid(column_t* column){
	int i, j;
	for (i = 0; i < 9; i++) {
        for (j = i + 1; j < 9; j++) {
        	if (!cell_is_valid(&column->cells[i], &column->cells[j])) {
        		return false;
        	}
        }
   	}
   	return true;
}

void column_restart_cells(column_t* column) {
	for (int i=0; i<9; i++) {
		cell_restart(&column->cells[i]);
	}
}

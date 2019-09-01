#include "sector.h"

//forward declaration
bool sector_row_is_valid(int row);

void sector_init(sector_t* sector, int** elements) {
	int elem;
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			elem = elements[i][j];
			if (elem == 0) {
				cell_init(&sector->cells[i][j], elem, true);
			} else {
				cell_init(&sector->cells[i][j], elem, false);
			}
		}
	}
}

int sector_add_number(sector_t* sector, int number, int row, int column) {
	if (!cell_is_modifiable(&sector->cells[row][column])){
		return 1;
	}
	cell_set_number(&sector->cells[row][column], number);
	return 0;
}

bool sector_is_valid(sector_t* sector) {
	int i, j, k;
	for(i = 0; i < 3; i++) {
		if (!sector_row_is_valid(i)) {
			return false;
		}
	}
	return true;
}

void sector_restart_cells(sector_t* sector) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cell_restart(&sector->cells[i][j]);
		}
	}
}

bool sector_row_is_valid(int row) {
	int j;
	for (int i = 0; i < 3; i++) {
        for (j = i + 1; j < 3; j++) {
        	if (!cell_is_valid(&sector->cells[row][i]), &sector->cells[row][j]) {
        		return false;
        	}
        }
   	}
   	return true;
}
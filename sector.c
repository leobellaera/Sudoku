#include "sector.h"

//forward declaration
bool sector_row_is_valid(sector_t* sector, int row);
void sector_put_cells_in_array(sector_t* sector, cell_t* array);
#include <stdio.h> //BORRAR!!!

void sector_init(sector_t* sector, int elements[3][3]) {
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
	int i, j;
	cell_t aux[9];
	sector_put_cells_in_array(sector, aux);
	for (i = 0; i < 9; i++) {
        for (j = i + 1; j < 9; j++) {
        	if (!cell_is_valid(&aux[i], &aux[j])) {
        		return false;
        	}
        }
    }
    return true;
}

void sector_put_cells_in_array(sector_t* sector, cell_t* array) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			array[i + j] = sector->cells[i][j];
		}
	}
}

void sector_restart_cells(sector_t* sector) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cell_restart(&sector->cells[i][j]);
		}
	}
}

void sector_print(sector_t* sector){
	for (int i = 0; i < 3; i ++) {
		for (int j = 0; j < 3; j++) {
			printf("%d ", cell_get_number(&sector->cells[i][j]));
		}
		printf("\n");
	}
}
#include "cell.h"

bool cell_is_modifiable(cell_t* cell){
	return cell->modifiable;
}

void cell_set_number(cell_t* cell, int numb){
	cell->number = numb;
}

int cell_get_number(cell_t* cell){
	return cell->number
}

void cell_restart(cell_t* cell){
	if (cell->modifiable) {
		cell->number = 0;
	}
}

void cell_set_unmodifiable(cell_t* cell){
	cell->modifiable = false;
}
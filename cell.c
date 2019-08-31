#include "cell.h"

void cell_init(cell_t* cell, int number, bool modifiable) {
	cell->modifiable = modifiable;
	cell->number = number;
}

bool cell_is_modifiable(cell_t* cell) {
	return cell->modifiable;
}

void cell_set_number(cell_t* cell, int numb) {
	cell->number = numb;
}

int cell_get_number(cell_t* cell) {
	return cell->number;
}

bool is_valid(cell_t* cell_a, cell_t* cell_b) {
	return (cell_a->number != cell_b->number || cell_a->number == 0);
}


void cell_restart(cell_t* cell) {
	if (cell->modifiable) {
		cell->number = 0;
	}
}
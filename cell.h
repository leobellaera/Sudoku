#ifndef _CELL_H_
#define _CELL_H_

#include <stdbool.h>

typedef struct cell {
	bool modifiable;
	int number;
} cell_t;

bool cell_is_modifiable(cell_t* cell);

void cell_set_number(cell_t* cell, int numb);

int cell_get_number(cell_t* cell);

void cell_restart(cell_t* cell);

void cell_set_unmodifiable(cell_t* cell);

#endif
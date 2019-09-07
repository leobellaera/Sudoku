#ifndef _CELL_H_
#define _CELL_H_

#include <stdbool.h>

typedef struct cell {
	bool modifiable;
	int number;
} cell_t;

void cell_init(cell_t* cell, int number, bool modifiable);

int cell_set_number(cell_t* cell, int numb);

int cell_get_number(cell_t* cell);

bool cell_is_valid(cell_t* cell_a, cell_t* cell_b);

void cell_restart(cell_t* cell);

#endif

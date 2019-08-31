#ifndef _COLUMN_H_
#define _COLUMN_H_

#include <stdbool.h>

typedef struct column {
	cell_t cells[9];
} column_t;

int column_add_number(column_t* column, int number, int row);

bool column_is_valid(column_t* column);

void column_restart_cells(column_t* column);

#endif
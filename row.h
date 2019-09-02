#ifndef _ROW_H_
#define _ROW_H_

#include <stdbool.h>
#include "cell.h"

typedef struct row {
	cell_t cells[9];
} row_t;

void row_init(row_t* row, int* elements);

int row_add_number(row_t* row, int number, int pos);

bool row_is_valid(row_t* row);

void row_restart_cells(row_t* row);

void row_show_cells(row_t* row, int* ptr);

#endif
#ifndef _SECTOR_H_
#define _SECTOR_H_

#include <stdbool.h>
#include "cell.h"

typedef struct sector {
	cell_t cells[3][3];
} sector_t;

void sector_init(sector_t* sector, int *elements);

int sector_add_number(sector_t* sector, int number, int row, int column);

bool sector_is_valid(sector_t* sector);

void sector_restart_cells(sector_t* sector);

#endif
#ifndef _SUDOKU_INTERFACE_H_
#define _SUDOKU_INTERFACE_H_

#include "client_interface.h"
#include "server_interface.h"

typedef struct {
	bool server_mode;
	client_interface_t client_interface;
	server_interface_t server_interface;
} sudoku_interface_t;

int sudoku_interface_init(sudoku_interface_t* sudoku_interface, 
	int argc, char* argv[]);

int sudoku_interface_execute(sudoku_interface_t* sudoku_interface);

#endif

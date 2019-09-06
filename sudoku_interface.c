#include "sudoku_interface.h"
#include <stdbool.h>
#include "string.h"

#include <stdio.h>

#define SUCCESS 0
#define ERROR 1
#define EXIT 2

int check_arguments(int argc, char* argv[]);
int init_mode_executed(sudoku_interface_t* sudoku_interface, char* argv[]);

int sudoku_interface_init(sudoku_interface_t* sudoku_interface, int argc, char* argv[]){
	if (check_arguments(argc, argv) == ERROR) {
		return ERROR;
	}
	if (init_mode_executed(sudoku_interface, argv) == ERROR) {
		return ERROR;
	}
	return SUCCESS;
}


int init_mode_executed(sudoku_interface_t* sudoku_interface, char* argv[]) {
	if (strcmp(argv[1], "server") == 0) {
		if (server_interface_init(&sudoku_interface->server_interface, argv[2]) == ERROR) {
			return ERROR;
		}
		sudoku_interface->server_mode = true;
	} else {
		if (client_interface_init(&sudoku_interface->client_interface, argv[2], argv[3]) == ERROR) {
			return ERROR;
		}
		sudoku_interface->server_mode = false;
	}
	return SUCCESS;
}


int sudoku_interface_execute(sudoku_interface_t* sudoku_interface) {
	if (sudoku_interface->server_mode == true) {
		if (server_interface_process(&sudoku_interface->server_interface) == ERROR) {
			return ERROR;
		}
	} else {
		int state = client_interface_process(&sudoku_interface->client_interface);
		if (state == ERROR) {
			return ERROR;
		}
		else if (state == EXIT) {
			return EXIT;
		}
	}
	return SUCCESS;
}

int check_arguments(int argc, char* argv[]) {
	return SUCCESS;
}
#include "server_interface.h"
#include "sudoku_matrix_loader.h"

#define ERROR 1
#define SUCCESS 0

int server_interface_init(server_interface_t* self, const char* port) {
	int matrix[9][9];
	if (load_sudoku_matrix(matrix) == ERROR) {
		return ERROR;
	}
	sudoku_init(&self->sudoku, matrix);
	if (server_init(&self->server, port) == ERROR) {
		return ERROR;
	}
	if (server_accept_client(&self->server) == ERROR) {
		server_release(&self->server);
		return ERROR;
	}
	server_protocol_init(&self->protocol, &self->server, &self->sudoku);
	return SUCCESS;
}

int server_interface_process(server_interface_t* self) {
	if (server_protocol_process(&self->protocol)) {
		server_release(&self->server);
		return ERROR;
	}
	return SUCCESS;
}
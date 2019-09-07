#include "server_interface.h"
#include "sudoku_matrix_loader.h"

#define ERROR 1
#define SUCCESS 0

int server_interface_init(server_interface_t* self, const char* port) {
	int matrix[9][9];
	if (load_sudoku_matrix(matrix) == ERROR) {
		return ERROR;
	}
	sudoku_board_init(&self->board, matrix);
	if (server_socket_init(&self->skt, port) == ERROR) {
		return ERROR;
	}
	if (server_socket_accept_client(&self->skt) == ERROR) {
		server_socket_release(&self->skt);
		return ERROR;
	}
	server_protocol_init(&self->protocol, &self->skt, &self->board);
	return SUCCESS;
}

int server_interface_process(server_interface_t* self) {
	if (server_protocol_process(&self->protocol)) {
		server_socket_release(&self->skt);
		return ERROR;
	}
	return SUCCESS;
}

#ifndef _SERVER_PROTOCOL_H
#define _SERVER_PROTOCOL_H

#include "sudoku.h"
#include "server_socket.h"

typedef struct {
	server_socket_t* skt;
	sudoku_t* sudoku;
} server_protocol_t;

void server_protocol_init(server_protocol_t* protocol, 
	server_socket_t* skt, sudoku_t* sudoku);

int server_protocol_process(server_protocol_t* protocol);

#endif

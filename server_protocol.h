#ifndef _SERVER_PROTOCOL_H
#define _SERVER_PROTOCOL_H

#include "sudoku.h"
#include "server.h"

typedef struct {
	server_t sv;
	sudoku_t sudoku;
} server_protocol_t;

int server_protocol_init(server_protocol_t* protocol, const char* port, int matrix[9][9]);

int server_protocol_process(server_protocol_t* protocol);

#endif
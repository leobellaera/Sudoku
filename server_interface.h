#ifndef _SERVER_INTERFACE_H_
#define _SERVER_INTERFACE_H_

#include "server_protocol.h"
#include "server.h"
#include "sudoku.h"

typedef struct {
	sudoku_t sudoku;
	server_t server;
	server_protocol_t protocol;
} server_interface_t;

int server_interface_init(server_interface_t* self, const char* port);

int server_interface_process(server_interface_t* self);

#endif
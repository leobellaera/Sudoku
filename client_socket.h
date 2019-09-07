#ifndef _CLIENT_SOCKET_H_
#define _CLIENT_SOCKET_H_

#include "socket.h"

typedef struct client {
	socket_t skt;
} client_socket_t;

int client_socket_init(client_socket_t* self, const char* host, 
	const char* service);

int client_socket_recv_message(client_socket_t* self, char* buf, int size);

int client_socket_send_message(client_socket_t* self, char* buf, int size);

void client_socket_release(client_socket_t* self);

#endif

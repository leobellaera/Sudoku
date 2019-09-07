#ifndef _SERVER_H_
#define _SERVER_H_

#include "socket.h"

typedef struct server {
	socket_t sv_skt;
	socket_t peer_skt;
} server_socket_t;

int server_socket_init(server_socket_t* self, const char* port);

int server_socket_accept_client(server_socket_t* self);

int server_socket_recv_message(server_socket_t* self, char* buf, int size);

int server_socket_send_message(server_socket_t* self, char* buf, int size);

void server_socket_release(server_socket_t* self);

#endif

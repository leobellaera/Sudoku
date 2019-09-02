#ifndef _SERVER_H_
#define _SERVER_H_

#include "socket.h"

typedef struct server {
	socket_t sv_skt;
	socket_t peer_skt;
} server_t;

int server_init(server_t* sv, const char* port);

int server_accept_client(server_t* sv);

int server_recv_message(server_t* sv, char* buf, int size);

int server_send_message(server_t* sv, char* buf, int size);

void server_release(server_t* sv); //destroy

#endif
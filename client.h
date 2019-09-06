#ifndef _CLIENT_H
#define _CLIENT_H

#include "socket.h"

typedef struct client {
	socket_t skt;
} client_t;

int client_init(client_t* client, const char* host, const char* service);

int client_recv_message(client_t* client, char* buf, int size);

int client_send_message(client_t* client, char* buf, int size);

void client_release(client_t* client);



#endif
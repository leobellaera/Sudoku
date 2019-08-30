#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <stdbool.h>

typedef struct socket {
	int fd;
	//bool client;  //1 for client, 0 for server.
} socket_t;

void socket_init(socket_t* socket);

void socket_release(socket_t* socket);

int socket_connect(socket_t* socket, const char* host, const char* service);

int socket_bind_and_listen(socket_t* socket, const char* service, int listen_amount);

int socket_accept_client(socket_t* sv_skt, socket_t* peer_skt);

int socket_recv_message(socket_t* socket, char *buf, int size);

int socket_send_message(socket_t* socket, char *buf, int size);

int socket_accept(socket_t* socket);

#endif
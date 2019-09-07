#ifndef _CLIENT_PROTOCOL_H_
#define _CLIENT_PROTOCOL_H_

#include "client_socket.h"

typedef struct {
	client_socket_t* skt;
} client_protocol_t;

void client_protocol_init(client_protocol_t* protocol, client_socket_t* skt);

int client_protocol_send_message(client_protocol_t* protocol, char* command);

char* client_protocol_recv_answer(client_protocol_t* protocol);

#endif

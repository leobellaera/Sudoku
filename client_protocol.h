#ifndef _CLIENT_PROTOCOL_H_
#define _CLIENT_PROTOCOL_H_

#include "client.h"

typedef struct {
	client_t client;
} client_protocol_t;

int client_protocol_init(client_protocol_t* protocol, const char* host, const char* service);

int client_protocol_process_input(client_protocol_t* protocol);

#endif
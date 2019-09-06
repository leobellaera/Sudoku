#ifndef _CLIENT_INTERFACE_H
#define _CLIENT_INTERFACE_H

#include "client.h"
#include "client_protocol.h"

typedef struct {
	client_t client;
	client_protocol_t protocol;
	
} client_interface_t;

int client_interface_init(client_interface_t* client_interface, const char* host, const char* service);

int client_interface_process(client_interface_t* client_interface);


#endif
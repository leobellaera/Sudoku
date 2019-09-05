#ifndef _USER_INTERFACE_H
#define _USER_INTERFACE_H

#include "client.h"
#include "client_protocol.h"

typedef struct {
	client_t client;
	client_protocol_t protocol;
	
} user_interface_t;

int user_interface_init(user_interface_t* user_interface, const char* host, const char* service);

int user_interface_process(user_interface_t* user_interface);


#endif
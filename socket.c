#include "socket.h"
#define _POSIX_C_SOURCE 200112L

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include <string.h>
#include <stdio.h>
#include <errno.h>

#include <stdbool.h>

void socket_addr_iterate(socket_t* skt, struct addrinfo* result);
int socket_getaddrinfo(struct addrinfo **result, const char* host, const char* service, bool pasive);

void socket_init(socket_t* socket) {
	socket->fd = -1; //initialize to invalid fd
}

void socket_release(socket_t* skt) {
	shutdown(skt->fd, SHUT_RDWR);
	close(skt->fd);
}

int socket_connect(socket_t* skt, const char* host, const char* service) {
	struct addrinfo *result = NULL;
	int s = socket_getaddrinfo(&result, host, service, false);

	if (s != 0) { 
    	printf("Error in getaddrinfo: %s\n", gai_strerror(s));
    	return 1;
    }

    socket_addr_iterate(skt, result);
    if (skt->fd == -1) {
    	return 1;
    } 
	freeaddrinfo(result);
	return 0;
}

int socket_bind_and_listen(socket_t* skt, const char* service, int listen_amount) {
	struct addrinfo *ptr = NULL;

	int s = socket_getaddrinfo(&ptr, NULL, service, true);
	if (s != 0) {
    	printf("Error in getaddrinfo: %s\n", gai_strerror(s));
    	return 1;
   	}

    skt->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
	if (skt->fd == -1) {
      printf("Error: %s\n", strerror(errno));
      freeaddrinfo(ptr);
      return 1;
	}

	s = bind(skt->fd, ptr->ai_addr, ptr->ai_addrlen);
   	if (s == -1) {
    	printf("Error: %s\n", strerror(errno));
    	close(skt->fd);
    	freeaddrinfo(ptr);
    	return 1;
	}

	freeaddrinfo(ptr);

	s = listen(skt->fd, listen_amount);

	if (s == -1) {
		printf("Error: %s\n", strerror(errno));
    	close(skt->fd);
    	return 1;
	}

	return 0;
}

int socket_accept_client(socket_t* sv_skt, socket_t* peer_skt) {
	peer_skt->fd = accept(sv_skt->fd, NULL, NULL);
	if (peer_skt->fd == -1){
		printf("Error: %s\n", strerror(errno));
		return 1;
	}
	return 0;
}


int socket_recv_message(socket_t* skt, char *buf, int size){
	int received = 0;
	int s = 0;
	bool valid_skt = true;

	while (received < size && valid_skt) {
		s = recv(skt->fd, &buf[received], size-received, MSG_NOSIGNAL);

		if (s == 0) { //the socket was closed
			valid_skt = false;
		}
		else if (s == -1) { //error
			valid_skt = false;
		}
		else {
         received += s;
		}
	}

	if (valid_skt) {
		return received;
	}
	else {
		return -1;
	}
}

int socket_send_message(socket_t* skt, char *buf, int size){

	int sent = 0;
	int s = 0;
	bool valid_skt = true;

	while (sent < size && valid_skt) {
		s = send(skt->fd, &buf[sent], size-sent, MSG_NOSIGNAL);

		if (s == 0) {
			valid_skt = false;
		}
		else if (s == -1) {
			valid_skt = false;
		}
		else {
			sent += s;
		}
	}

	if (valid_skt) {
		return sent;
	}
	else {
		return -1;
	}
}

void socket_addr_iterate(socket_t* skt, struct addrinfo* result) {
	struct addrinfo* ptr;
	bool connection_established = false;
	int s;
	for (ptr = result; ptr != NULL && connection_established == false; ptr = ptr->ai_next) {
		skt->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (skt->fd == -1) {
			printf("Error: %s\n", strerror(errno));
		}
		else {
			s = connect(skt->fd, ptr->ai_addr, ptr->ai_addrlen);
        	if (s == -1) {
            	printf("Error: %s\n", strerror(errno));
            	close(skt->fd);
        	}
			connection_established = (s != -1); //are we connected now?
		}
	}
	
}

int socket_getaddrinfo(struct addrinfo **addrinfo_ptr, const char* host, const char* service, bool passive) {
	struct addrinfo hints;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if (passive){
		hints.ai_flags = AI_PASSIVE;
		return getaddrinfo(NULL, service, &hints, addrinfo_ptr);
	}
	else {
		hints.ai_flags = 0;
		return getaddrinfo(host, service, &hints, addrinfo_ptr);
	}
}
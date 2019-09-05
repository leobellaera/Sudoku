#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "protocol_message_maker.h"

#define RESET_COMMAND_CODE 'R'
#define PUT_COMMAND_CODE 'P'
#define VERIFY_COMMAND_CODE 'V'
#define GET_COMMAND_CODE 'G'

char* build_g_message();
char* build_r_message();
char* build_v_message();
char* build_p_message(char* command);
char* init_message(int len);

char* build_protocol_message(char* command) {
	if (strcmp("get", command) == 0) {
		return build_g_message(command);
	}
	else if (strcmp("reset", command) == 0) {
		return build_r_message(command);
	}
	else if (strcmp("verify", command) == 0) {
		return build_v_message(command);
	}
	else {
		return build_p_message(command);
	}
}

char* build_g_message() {
	char* message = init_message(1);
	message[0] = GET_COMMAND_CODE;
	return message;
}

char* build_r_message() {
	char* message = init_message(1);
	message[0] = RESET_COMMAND_CODE;
	return message;
}

char* build_v_message() {
	char* message = init_message(1);
	message[0] = VERIFY_COMMAND_CODE;
	return message;
}

char* build_p_message(char* command) { //command format: "put x in y,z"
	char* message = init_message(4);
	message[0] = PUT_COMMAND_CODE;
	message[1] = command[9];
	message[2] = command[11];
	message[3] = command[4];
	return message;
}

char* init_message(int len) {
	char* mes = malloc(sizeof(char)*len + 1);
	mes[len] = '\0';
	return mes;
}	

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "protocol_message_maker.h"

#define RESET_COMMAND_MES 'R'
#define PUT_COMMAND_MES 'P'
#define VERIFY_COMMAND_MES 'V'
#define GET_COMMAND_MES 'G'

#define GET_COMMAND "get"
#define RESET_COMMAND "reset"
#define VERIFY_COMMAND "verify"
#define PUT_COMMAND "put"

#define PUT_COMMAND_NUMB_POS 4
#define PUT_COMMAND_IDX_A_POS 9
#define PUT_COMMAND_IDX_B_POS 11

char* build_get_message();
char* build_reset_message();
char* build_verify_message();
char* build_put_message(char* command);
char* init_message(int len);

char* build_protocol_message(char* command) {
	if (strcmp(GET_COMMAND, command) == 0) {
		return build_get_message(command);
	}
	else if (strcmp(RESET_COMMAND, command) == 0) {
		return build_reset_message(command);
	}
	else if (strcmp(VERIFY_COMMAND, command) == 0) {
		return build_verify_message(command);
	}
	else {
		return build_put_message(command);
	}
}

char* build_get_message() {
	char* message = init_message(1);
	message[0] = GET_COMMAND_MES;
	return message;
}

char* build_reset_message() {
	char* message = init_message(1);
	message[0] = RESET_COMMAND_MES;
	return message;
}

char* build_verify_message() {
	char* message = init_message(1);
	message[0] = VERIFY_COMMAND_MES;
	return message;
}

char* build_put_message(char* command) { //command format: "put x in y,z"
	char* message = init_message(4);
	message[0] = PUT_COMMAND_MES;
	message[1] = command[PUT_COMMAND_IDX_A_POS];
	message[2] = command[PUT_COMMAND_IDX_B_POS];
	message[3] = command[PUT_COMMAND_NUMB_POS];
	return message;
}

char* init_message(int len) {
	char* mes = malloc(sizeof(char)*len + 1);
	mes[len] = '\0';
	return mes;
}	

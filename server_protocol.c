#include "server_protocol.h"
#include <string.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <board_representation_maker.h>

//forward declarations
int process_message(server_protocol_t* protocol, char message);
int process_p_message(server_protocol_t* protocol);
int process_g_message(server_protocol_t* protocol);
int process_r_message(server_protocol_t* protocol);
int process_v_message(server_protocol_t* protocol);
int show_board_to_client(server_protocol_t* protocol);
int send_message_to_client(server_protocol_t* protocol, char* mes);
int send_unmodifiable_cell_message(server_protocol_t* protocol);
int send_modifiable_cell_message(server_protocol_t* protocol);
int send_invalid_board_message(server_protocol_t* protocol);
int send_valid_board_message(server_protocol_t* protocol);
uint32_t calculate_str_len(char* str);

int server_protocol_init(server_protocol_t* protocol, const char* port, int matrix[9][9]) {
	sudoku_init(&protocol->sudoku, matrix);
	int server_init = server_init(&protocol->sv, port);
	if (server_init) {
		return 1;
	}
	return 0;
}

int server_protocol_process(server_protocol_t* protocol) {
	char buffer;
	if (server_recv_message(&protocol->sv, &buffer, 1)) {
		server_release(&protocol->sv);
		return 1;
	}
	if (process_message(protocol, buffer)) {
		server_release(&protocol->sv);
		return 1;
	}
	return 0;
}

int process_message(server_protocol_t* protocol, char message) {
	if (message == 'P') {
		return process_p_message(protocol);
	}
	else if (message == 'G') {
		return process_g_message(protocol);
	}
	else if (message == 'R') {
		return process_r_message(protocol);
	}
	else {
		return process_v_message(protocol);
	}
}


int process_p_message(server_protocol_t* protocol) {
	char buffer[3];
	if (server_recv_message(&protocol->sv, buffer, 3)) {
		return 1;
	}
	int valid_cell = sudoku_put(&protocol->sudoku, buffer[2], buffer[0], buffer[1]);
	if (valid_cell == 1) {
		return send_unmodifiable_cell_message(protocol);
	} else {
		return send_modifiable_cell_message(protocol);
	}
}

int send_unmodifiable_cell_message(server_protocol_t* protocol) {
	char mes[] = "La celda indicada no es modificable\n​";
	return send_message_to_client(protocol, mes);
}

int send_modifiable_cell_message(server_protocol_t* protocol) {
	return show_board_to_client(protocol);
}

int process_g_message(server_protocol_t* protocol) {
	return show_board_to_client(protocol);
}

int process_r_message(server_protocol_t* protocol) {
	sudoku_reset(&protocol->sudoku);
	return show_board_to_client(protocol);
}

int process_v_message(server_protocol_t* protocol) {
	if (sudoku_verify(&protocol->sudoku)) {
		return send_invalid_board_message(protocol);
	}
	return send_valid_board_message(protocol);
}

int send_invalid_board_message(server_protocol_t* protocol) {
	char mes[] = "Board state is invalid\n";
	return send_message_to_client(protocol, mes);
}

int send_valid_board_message(server_protocol_t* protocol) {
	char mes[] = "OK\n";
	return send_message_to_client(protocol, mes);
}


int send_message_to_client(server_protocol_t* protocol, char* mes) {
	uint32_t mes_len = htonl(calculate_str_len(mes));
	int length = snprintf( NULL, 0, "%d", mes_len);
	char* buffer = malloc( length + 1 );
	snprintf(buffer, length + 1, "%d", mes_len);

	if (server_send_message(&protocol->sv, buffer, 4) == 1) {
		return 1;
	}
	for (int i = 0; i < mes_len; i++) {
		if (server_send_message(&protocol->sv, &buffer[i], 1) == 1) {
			return 1;
		}
	}
	free(buffer);
	return 0;
}

int show_board_to_client(server_protocol_t* protocol) {
	int matrix[9][9];
	sudoku_show_board(&protocol->sudoku, matrix);
	char board_representation[722];
	assemble_board_representation(board_representation, matrix);
	return send_message_to_client(protocol, board_representation);
}
	

uint32_t calculate_str_len(char* str) {
	uint32_t len = 0;
	int i = 0;
	while (str[i] != '\0') {
		len += 1;
		i++;
	}
}
#include <stdio.h>
#include "sudoku.h"
#include "board_representation_maker.h"
#include <stdlib.h>
#include <string.h>

int main() {
	int m[9][9] = {
        {0,0,1,0,0,0,0,3,5},
        {0,0,0,0,0,0,0,0,0},
        {6,0,0,0,0,0,0,0,0},
        {1,0,0,0,4,0,0,0,0},
        {2,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,2,0,0,0},
        {0,0,0,0,0,4,0,0,0}
	};

	sudoku_t sudoku;
	sudoku_init(&sudoku, m);
	if (sudoku_put(&sudoku, 6, 1, 1)) {
		printf("CELDA NO MODIFICABLE!\n");
	}

	if (sudoku_verify(&sudoku)) {
		printf("NO CUMPLE REGLAS!\n");
	}
	else {
		printf("CUMPLE REGLAS!\n");
	}


	printf("\n");
	int aux[9][9];
	sudoku_show_board(&sudoku, aux);
	char* board = assemble_board_representation(aux);
	printf("%s\n", board);
	free(board);

	return 0;
}
//variaaveis declaradas no main
extern unsigned int nodesExpanded;
extern unsigned int nodesGenerated;
extern unsigned int solutionLength;
extern double runtime;


void goalStateF(State * const goalState) {
    goalState->action = NOT_APPLICABLE;
    goalState->board[0][0] = 0 + '0';
    goalState->board[0][1] = 1 + '0';
    goalState->board[0][2] = 2 + '0';
    goalState->board[1][0] = 3 + '0';
    goalState->board[1][1] = 4 + '0';
    goalState->board[1][2] = 5 + '0';
    goalState->board[2][0] = 6 + '0';
    goalState->board[2][1] = 7 + '0';
    goalState->board[2][2] = 8 + '0';
}

void inputState(State * const state) {
    state->action = NOT_APPLICABLE;
    char row, col;
    int symbol;

    // flags for input validation
    char isNumUsed[9] = { 0 };

    for(row = 0; row < 3; ++row) {
        for(col = 0; col < 3; ++col) {
            printf("    board[%i][%i]: ", row, col);

            // to prevent scanning newline from the input stream
            scanf("%i", &symbol);

            // check if input is a blank character or is a number greater than 0 and less than 9
            if(symbol >= 0 && symbol < 9) {
                // check if input is repeated
                if(!isNumUsed[symbol]) {
                    state->board[row][col] = symbol + '0';
                    isNumUsed[symbol] = 1;
                }
                else {
                    printf("    ERRO\n", symbol);
                    --col;
                }
            }
            else {
                printf("    ERRO: Digite numeros de 0 a 8.\n");
                --col;
            }
        }
    }
    printf("\n");
}

/**
 * DESCRIPTION: This displays contents of `board` to the standard output
**/
void printBoard(char const board[][3]) {
    char row, col;

    for(row = 0; row < 3; ++row) {
        printf("+---+---+---+\n");
        for(col = 0; col < 3; ++col) {
            printf("| %c ", board[row][col]);
        }
        printf("|\n");
    }
    printf("+---+---+---+\n");
}

/**
 * DESCRIPTION:
 *    This function interprets numerical instructions of the move to make,
 *    to it's verbal counterpart to be displayed to the screen.
 * PARAMETER:
 *    solution - the solution path consisting a list of nodes from the root
 *               to the goal
**/
void printSolution(struct SolutionPath *path) {
	//check if solution exists
    if(!path) {
        printf("Sem solucao.\n");
        return;
    }

	//if the initial state is already the goal state
	if(!path->next) {
		printf("Atencao! O estado inicial = Estado final.\n");
		return;
	}


    printf(
        "DETALHES:\n"
        " - Nr movimentos : %i\n"
        " - Nos expandidos  : %i\n"
        " - Nos gerados : %i\n"
        " - Runtime (Tempo)         : %g milliseconds\n"
        " - Memory used     : %i bytes\n", //only counting allocated `Node`s
        solutionLength, nodesExpanded, nodesGenerated, runtime, nodesGenerated * sizeof(Node));
}

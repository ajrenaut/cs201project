#include "game.h"
#include "enums.h"

//TODO: tutorial video.

int runGame(int gameMode, int width, int height) {
	int playerOne, playerTwo;
	Node **board = buildBoard(width, height);

	playerOne = PLAYER;
	playerTwo = gameMode;
	printBoard(board, width, height);
	int gameStatus = RUNNING;
	int turnCounter = 0;
	while(gameStatus == RUNNING) {
		if (turnCounter >= (width * height)) {
			gameStatus = GAME_TIED;
			break;
		}
		if (turnCounter % 2 == 0) {
			gameStatus = takeTurn(RED, playerOne, board, width, height);
			turnCounter++;
		}
		else if (turnCounter % 2 == 1) {
			gameStatus = takeTurn(BLUE, playerTwo, board, width, height);
			turnCounter++;
		}
		printBoard(board, width, height);
	}

	for (int i = 0; i < height; i++) {
		free(board[i]);
	}
	free(board);
	return gameStatus;
}

/*
 * Because the graph of the board is guaranteed to be a rectangular grid, the
 * board is generated and stored as a 2D array of the occupancies. Adjacent
 * nodes can easily be calculated as needed by moving 1 index in a direction
 * (or two in the case of diagonals).
 */
Node** buildBoard(int width, int height) {
	Node **board = (Node **)malloc(height * sizeof(Node*));
	for (int i = 0; i < height; i++) {
		board[i] = (Node *)malloc(width * sizeof(Node));
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			board[i][j].status = EMPTY;
		}
	}

	return board;
}

void printBoard(Node **board, int width, int height) {
	for (int i = 0; i < height; i++) {
		printf("|");
		for (int j = 0; j < width; j++) {
			switch (board[i][j].status) {
				case EMPTY:
					printf(" O |");
					break;
				case RED:
					printf("RED|");
					break;
				case BLUE:
					printf("BLU|");
					break;
			}
		}
		printf("\n\n");
	}
	printf("|");

	// Formatting of the bottom row of numbers varies to accommodate large boards
	//
	for (int i = 0; i < width; i++) {
		if (i < 9) printf(" %d |", i+1);
		else if (i < 99) printf("%d |", i+1);
		else if (i < 999) printf("%d|", i+1);
	}
	printf("\n\n");
	return;
}

int takeTurn(int color, int playerType, Node **board, int width, int height) {
	char playerColorString[4];
	switch (color) {
	case RED :
		strcpy(playerColorString, "RED");
		break;
	case BLUE :
		strcpy(playerColorString, "BLUE");
		break;
	}
	printf("\n%s's player's turn!\n", playerColorString);

	int boardWidth = width;
	int boardHeight = height;
	int columnNum = 0;
	int rowNum = 0;
	int newGameStatus = 0;
	switch (playerType) {
	case PLAYER :
		printf("\nEnter a column number between 1 and %d to place a piece.", boardWidth);
		printf("\nColumn: ");
		columnNum = readInt();
		while(columnNum < 1 || columnNum > boardWidth
				|| (board[0][columnNum-1].status != EMPTY)) {
			if (columnNum < 1 && columnNum != -2) {
				printf("Input not recognized.\n"
						"Enter a column number between 1 and %d to place a piece.", boardWidth);
				printf("\nColumn: ");
			}
			else if (board[0][columnNum-1].status != EMPTY) {
				printf("That column is full.\n"
						"Enter a column number between 1 and %d to place a piece.", boardWidth);
				printf("\nColumn: ");
			}
			columnNum = readInt();
		}

		printf("\n%s places a piece in column %d.\n\n", playerColorString, columnNum);
		columnNum--; // Adjusting from 1 based indexing to 0 based indexing.
		rowNum = placePiece(board, color, columnNum, height);
		newGameStatus = checkVictory(board, color, columnNum, rowNum, boardWidth, boardHeight);
		if (newGameStatus == GAME_OVER) {
			switch (color) {
			case RED :
				return RED_WIN;
				break;
			case BLUE :
				return BLUE_WIN;
				break;
			}
		}
		break;
	case AI :
		columnNum = aiRoutine(board, width, height);
		rowNum = placePiece(board, color, columnNum, height);
		newGameStatus = checkVictory(board, color, columnNum, rowNum, boardWidth, boardHeight);
		printf("\n%s places a piece in column %d.\n\n", playerColorString, columnNum+1);

		if (newGameStatus == GAME_OVER) {
			switch (color) {
			case RED :
				return RED_WIN;
				break;
			case BLUE :
				return BLUE_WIN;
				break;
			}
		}
		break;
	}
	return RUNNING;
}

int placePiece(Node **board, int color, int column, int height) {
	for (int rowNum = height-1; rowNum >= 0; rowNum--) {
		if (board[rowNum][column].status == EMPTY) {
			board[rowNum][column].status = color;
			return rowNum;
		}
	}
	return -1;
}

/*
 * Searches a node for lines of four by searching in a manner similar to a BFS.
 * The number of pieces in each straight line (upper diagonal, lower diagonal,
 * vertically, horizontally) is counted, and if there are four in a row, then
 * the function returns that the game is won. Otherwise, the game continues.
 */
int checkVictory(Node **board, int color, int column, int row, int boardWidth, int boardHeight) {
	int upperDiagFound = 1, lowerDiagFound = 1, verticalFound = 1, horizontalFound = 1;
	int distance = 1;

	while (row+distance < boardHeight) {
		if (color == searchDirection(board, row, column, distance, 0)) {
			verticalFound++;
		}
		else break;
		if (verticalFound == 4) return GAME_OVER;
		distance++;
	}
	distance = 1;

	while (row+distance < boardHeight && column+distance < boardWidth) {
		if (color == searchDirection(board, row, column, distance, distance)) {
			lowerDiagFound++;
		}
		else break;
		if (lowerDiagFound == 4) return GAME_OVER;
		distance++;
	}
	distance = 1;

	while (column+distance < boardWidth) {
		if (color == searchDirection(board, row, column, 0, distance)) {
			horizontalFound++;
		}
		else break;
		if (horizontalFound == 4) return GAME_OVER;
		distance++;
	}
	distance = 1;

	while (row-distance >= 0 && column+distance < boardWidth) {
		if (color == searchDirection(board, row, column, -distance, distance)) {
			upperDiagFound++;
		}
		else break;
		if (upperDiagFound == 4) return GAME_OVER;
		distance++;
	}
	distance = 1;

	while (row-distance >= 0) {
		if (color == searchDirection(board, row, column, -distance, 0)) {
			verticalFound++;
		}
		else break;
		if (verticalFound == 4) return GAME_OVER;
		distance++;
	}
	distance = 1;

	while (row-distance >= 0 && column-distance >= 0) {
		if (color == searchDirection(board, row, column, -distance, -distance)) {
			lowerDiagFound++;
		}
		else break;
		if (lowerDiagFound == 4) return GAME_OVER;
		distance++;
	}
	distance = 1;

	while (column-distance >= 0) {
		if (color == searchDirection(board, row, column, 0, -distance)) {
			horizontalFound++;
		}
		else break;
		if (horizontalFound == 4) return GAME_OVER;
		distance++;
	}
	distance = 1;

	while (row+distance < boardHeight && column-distance >= 0) {
		if (color == searchDirection(board, row, column, distance, -distance)) {
			upperDiagFound++;
		}
		else break;
		if (upperDiagFound == 4) return GAME_OVER;
		distance++;
	}

	return RUNNING;
}

int searchDirection(Node **board, int row, int column, int vertDist, int horizDist) {
	int foundStatus = board[row+vertDist][column+horizDist].status;
	return foundStatus;
}

/*
 * The AI follows a routine with the following priority:
 * 1. Find a winning move. If there is one, take it.
 * 2. Find a winning move for the opponent. If there is one, prevent it.
 * 3. Rule out moves that would immediately enable a winning move for the opponent.
 * 	  Choose from the remaining columns.
 * 4. Choose a random column and accept defeat.
 *
 * There are more in-depth AI algorithms possible but the thinking here is that
 * with a potential for extremely large board sizes, calculating many moves ahead
 * could potentially make the time it takes for the AI to act very long.
 */
int aiRoutine(Node **board, int width, int height) {
	time_t timeSeed;
	srand((unsigned) time(&timeSeed));
	int selectedColumn = 0;
	int *enabledMoveSpaces = (int*)malloc(width*sizeof(int));
	int possibleMoves = width;
	for (int i = 0; i < width; i++) {
		if (board[0][i].status == EMPTY) {
			enabledMoveSpaces[i] = 1;
		}
		else enabledMoveSpaces[i] = 0;
	}

	//First check to see if the AI can win in one move.
	for (int column = 0; column < width; column++) {
		for (int row = height-1; row >= 0; row--) {
			if (board[row][column].status == EMPTY) {
				if (checkVictory(board, BLUE, column, row, width, height) == GAME_OVER) {
					free(enabledMoveSpaces);
					return column;
				}
			}
		}
	}

	//Check to see if the AI can prevent an opponent's win by making a move.
	for (int column = 0; column < width; column++) {
		for (int row = height-1; row >= 0; row--) {
			if (column >= width) break;
			if (board[row][column].status == EMPTY) {
				if (checkVictory(board, RED, column, row, width, height) == GAME_OVER) {
					free(enabledMoveSpaces);
					return column;
				}
				break;
			}
		}
	}

	// Prevent the AI from making "bad" moves by filtering out moves that would
	// immediately enable an opponent's victory. A "bad move" is switched from
	// 1 to 0.
	for (int column = 0; column < width; column++) {
		for (int row = height-1; row > 0; row--) {
			if (board[row][column].status == EMPTY && (row-1 >= 0)) {
				if (checkVictory(board, RED, column, row-1, width, height) == GAME_OVER) {
					enabledMoveSpaces[column] = 0;
					possibleMoves--;
				}
			}
		}
	}

	if (possibleMoves > 0) {
		selectedColumn = rand() % width;
		while (enabledMoveSpaces[selectedColumn] == 0) {
			selectedColumn = rand() % width;
		}
		free(enabledMoveSpaces);
		return selectedColumn;
	}

	// Select a move at random from the remaining list of moves.
	// The AI has no safe moves left, so all moves are re-considered and one is
	// picked at random.
	for (int i = 0; i < width; i++) {
		if (board[0][i].status == EMPTY) {
			enabledMoveSpaces[i] = 1;
		}
	}
	selectedColumn = rand() % width;
	while (enabledMoveSpaces[selectedColumn] == 0) {
		selectedColumn = rand() % width;
	}
	free(enabledMoveSpaces);
	return selectedColumn;
}

/*
 * This function is used to filter out bad inputs and read integers. Source:
 * https://stackoverflow.com/questions/4072190/check-if-input-is-integer-type-in-c
 */
int readInt() {
	char s[80];
	int valid = 0;
	fgets (s, sizeof(s), stdin);
	int len = strlen(s);
	while (len > 0 && isspace(s[len-1])) len--; // Removes trailing whitespace
	if (len==0) {
		return -2; // -2 here means that an empty string was read.
	}
	if (len > 0) {
		valid = 1;
		for (int i = 0; i < len; ++i) {
			if (!isdigit(s[i])) {
				valid = 0;
				break;
			}
		}
	}

	// -1 is never a valid input so it is used to relay that the input was bad
	if (!valid) return -1;
	else {
		int intFound = atoi(s);
		return intFound;
	}
}

int readChar() {
	char s[160];
	int valid = 0;
	fgets (s, sizeof(s), stdin);
	int len = strlen(s);
	while (len > 0 && isspace(s[len-1])) len--; // Removes trailing whitespace
	if (len==0) {
		return -2; // -2 here means that an empty string was read.
	}
	if (len > 0) {
		valid = 1;
		for (int i = 0; i < len; ++i) {
			if (!isalpha(s[i])) {
				valid = 0;
				break;
			}
		}
	}

	// -1 is never a valid input so it is used to relay that the input was bad
	if (!valid || len > 1) return -1;
	else {
		s[0] = toupper(s[0]);
		return s[0];
	}
}

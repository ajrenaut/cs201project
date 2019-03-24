#include "game.h"
#include "enums.h"

//TODO: Piece tracker array. Counts number of pieces in each column. Prevents overflow of a column.
//TODO: Error catching (i.e. board size MINIMUM, bad dimensions, bad placement inputs, etc.
//TODO: ncurses implementation
//TODO: AI implementation
//TODO: Series of match tracker (keep track of score between players)
//TODO: Clean up ENUMS
//TODO: piece counter (track # of pieces, tie game if board fills but no winner.

//Error catching function: https://stackoverflow.com/questions/4072190/check-if-input-is-integer-type-in-c


void runGame() {

	int boardWidth, boardHeight, gameMode;
	int playerOne, playerTwo;
	Node **board;
	int *piecesInColumnTracker;

	printf("Welcome to Connect Four! Please select game mode.\n");
	printf("Enter 1 to play against the AI, or 2 to play against another player.");
	printf("Game mode: ");
	scanf("%d", &gameMode);
	playerOne = PLAYER;
	switch (gameMode) {
	case VS_AI :
		playerTwo = AI;
		break;
	case VS_PLAYER :
		playerTwo = PLAYER;
		break;
	}

	//Board dimensions must be 4x4 or greater to make game playable.
	printf("Okay! Please enter board dimensions: \n");
	printf("Board width: ");
	scanf("%d", &boardWidth);
	printf("Board height: ");
	scanf("%d", &boardHeight);
	printf("\nThe board will be %d x %d.\n\n", boardWidth, boardHeight);

	board = buildBoard(boardWidth, boardHeight);

	printBoard(board, boardWidth, boardHeight);
	int gameStatus = RUNNING;
	int turnCounter = 0;
	while(gameStatus == RUNNING) {
		if (turnCounter % 2 == 0) {
			gameStatus = takeTurn(RED, playerOne, board, boardWidth, boardHeight);
			turnCounter++;
		}
		else if (turnCounter % 2 == 1) {
			gameStatus = takeTurn(BLUE, playerTwo, board, boardWidth, boardHeight);
			turnCounter++;
		}
		printBoard(board, boardWidth, boardHeight);
	}

	switch (gameStatus) {
	case RED_WIN :
		printf("RED WINS!");
		break;
	case BLUE_WIN :
		printf("BLUE WINS!");
		break;
	}
	return;
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
					printf("(R)|");
					break;
				case BLUE:
					printf("(B)|");
					break;
			}
		}
		printf("\n\n");
	}
	printf("|");
	for (int i = 0; i < width; i++) {
		printf(" %d |", i+1);
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
	printf("\n%s's player's turn!", playerColorString);

	int boardWidth = width;
	int boardHeight = height;
	int columnNum = 0;
	int rowNum = 0;
	int newGameStatus = 0;
	switch (playerType) {
	case PLAYER :
		printf("\nEnter a column number between 1 and %d to place a piece.", boardWidth);
		printf("\nColumn: ");
		scanf("%d", &columnNum);

		// Check to see if the column entered exists, and has an empty space.
		while ((columnNum < 1) || (columnNum > boardWidth)
				|| (board[0][columnNum-1].status != EMPTY)) {
			printf("\n\nERROR: Number must be between 1 and %d, and the column"
					" must contain at least one empty space. Try again.\n", boardWidth);
			printf("Column: ");
			scanf("%d", &columnNum);
		}

		printf("\n%s places a piece in column %d.\n\n", playerColorString, columnNum);
		columnNum--;
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
		// TODO: AI Turn Steps
		/*
		 * Run ai option weighing routine.
		 * Generate deviation chance
		 * Place piece
		 * Check for victory
		 * Return game over if game is won, else break
		 */

		columnNum = aiRoutine(board, width, height);
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
 * Ai code
 */

int aiRoutine(Node **board, int width, int height) {
	time_t timeSeed;
	srand((unsigned) time(&timeSeed));
	//Check for move
	//Check to block
	//Pick random
	int selectedColumn = 0;
	selectedColumn = rand() % width;
	return selectedColumn;
}

#include "game.h"
#include "enums.h"

//TODO: Piece tracker array. Counts number of pieces in each column. Prevents overflow of a column.


 Node *createNode() {
	Node *newNode = malloc(sizeof(Node));
	newNode->status = EMPTY;

	newNode->top = NULL;
	newNode->topRight = NULL;
	newNode->right = NULL;
	newNode->botRight = NULL;
	newNode->bottom = NULL;
	newNode->botLeft = NULL;
	newNode->left = NULL;
	newNode->topLeft = NULL;

	return newNode;
}

void runGame() {

	int boardWidth, boardHeight, gameMode;
	int playerOne, playerTwo;
	Node *board;

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

	printf("Okay! Please enter board dimensions: \n");
	printf("Board width: ");
	scanf("%d", &boardWidth);
	printf("Board height: ");
	scanf("%d", &boardHeight);
	printf("\nThe board will be %d x %d.\n\n", boardWidth, boardHeight);

	board = buildBoard(boardWidth, boardHeight);

	printBoard(board, boardWidth);
	int gameStatus = RUNNING;
	int turnCounter = 0;
	while(gameStatus == RUNNING) {
		if (turnCounter % 2 == 0) {
			gameStatus = takeTurn(RED, playerOne, board, boardWidth);
			turnCounter++;
		}
		else if (turnCounter % 2 == 1) {
			gameStatus = takeTurn(BLUE, playerTwo, board, boardWidth);
			turnCounter++;
		}
		printBoard(board, boardWidth);
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

Node* buildBoard(int width, int height) {
	Node *bottomLeftNode;
	Node *startOfPreviousRow;
	for (int i = 0; i < height; i++) {
		Node *startOfNewRow = createNode();
		Node *currentNode = startOfNewRow;
		for (int j = 0; j < width-1 ; j++) {
			Node *nextNode = createNode();
			currentNode->right = nextNode;
			nextNode->left = currentNode;
			currentNode = nextNode;
		}
		if (i > 0) {
			Node *currentUpper = startOfNewRow;
			Node *currentLower = startOfPreviousRow;
			for (Node *currentZipNode = currentUpper; currentZipNode != NULL; currentZipNode = currentZipNode->right) {
				currentUpper->bottom = currentLower;
				currentUpper->botLeft = currentLower->left;
				currentUpper->botRight = currentLower->right;

				currentLower->top = currentUpper;
				currentLower->topLeft = currentUpper->left;
				currentLower->topRight = currentUpper->right;

				currentUpper = currentUpper->right;
				currentLower = currentLower->right;
			}
		}
		startOfPreviousRow = startOfNewRow;
	}

	bottomLeftNode = startOfPreviousRow;
	while(bottomLeftNode->left) {
		bottomLeftNode = bottomLeftNode->left;
	}
	while(bottomLeftNode->bottom) {
		bottomLeftNode = bottomLeftNode->bottom;
	}
	return bottomLeftNode;
}

void printBoard(Node *board, int width) {
	int boardWidth = width;
	Node *topLeft = board;
	while (topLeft->top) {
		topLeft = topLeft->top;
	}
	for (Node *curRow = topLeft; curRow != NULL ; curRow = curRow->bottom) {
		printf("|");
		for (Node *curNode = curRow; curNode != NULL; curNode = curNode->right) {
			switch (curNode->status) {
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
	for (int i = 0; i < boardWidth; i++) {
		printf(" %d |", i+1);
	}
	printf("\n\n");

	return;
}

int takeTurn(int color, int playerType, Node *board, int width) {
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
	int columnNum = 0;
	switch (playerType) {
	case PLAYER :
		printf("\nEnter a column number between 1 and %d to place a piece.", boardWidth);
		printf("\nColumn: ");
		scanf("%d", &columnNum);
		while (columnNum < 1 || columnNum > boardWidth) {
			printf("\n\nERROR: Number must be between 1 and %d. Try again.", boardWidth);
			printf("Column: ");
			scanf("%d", &columnNum);
		}
		printf("\n%s places a piece in column %d", playerColorString, columnNum);
		Node *placedPiece = placePiece(board, color, columnNum);
		int newGameStatus = checkVictory(placedPiece, color);
		if (newGameStatus == GAME_WON) {
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
		break;
	}
	return RUNNING;
}

Node* placePiece(Node *board, int color, int column) {
	Node *selectedNode = board;

	for (int i = 1; i < column; i++) {
		selectedNode = selectedNode->right;
	}

	while (selectedNode->status != EMPTY) {
		selectedNode = selectedNode->top;
	}

	selectedNode->status = color;
	return selectedNode;
}

/*
 * Takes a node, the player's color, and
 */
int probeDirection(Node* nodeToProbe, int color, int direction) {
	int numFoundInRow = 1;
	Node *currentNode = nodeToProbe;
	switch (direction) {
	case RIGHT :
	case LEFT :
		while(1) {
			currentNode = currentNode->right;
			if (currentNode == NULL) {
				break;
			}
			else if (currentNode->status != color) {
				break;
			}
			else if (currentNode->status == color) {
				numFoundInRow++;
			}

			if (numFoundInRow == 4) {
				return numFoundInRow;
			}
		}
		currentNode = nodeToProbe;
		while(1) {
			currentNode = currentNode->left;
				if (currentNode == NULL) {
					break;
				}
				else if (currentNode->status != color) {
					break;
				}
				else if (currentNode->status == color) {
					numFoundInRow++;
				}

				if (numFoundInRow == 4) {
					return numFoundInRow;
				}
		}
		break;
	case TOP:
	case BOTTOM:
		while(1) {
			currentNode = currentNode->bottom;
			if (currentNode == NULL) {
				break;
			}
			else if (currentNode->status != color) {
				break;
			}
			else if (currentNode->status == color) {
				numFoundInRow++;
			}
			if (numFoundInRow == 4) {
				return numFoundInRow;
			}
		}
		break;
	case TOP_LEFT:
	case BOTTOM_RIGHT:
		while(1) {
			currentNode = currentNode->topLeft;
			if (currentNode == NULL) {
				break;
			}
			else if (currentNode->status != color) {
				break;
			}
			else if (currentNode->status == color) {
				numFoundInRow++;
			}
				if (numFoundInRow == 4) {
				return numFoundInRow;
			}
		}
		currentNode = nodeToProbe;
		while(1) {
			currentNode = currentNode->botRight;
			if (currentNode == NULL) {
				break;
			}
			else if (currentNode->status != color) {
				break;
			}
			else if (currentNode->status == color) {
				numFoundInRow++;
			}
				if (numFoundInRow == 4) {
				return numFoundInRow;
			}
		}
		break;
	case TOP_RIGHT:
	case BOTTOM_LEFT:
		while(1) {
			currentNode = currentNode->topRight;
			if (currentNode == NULL) {
				break;
			}
			else if (currentNode->status != color) {
				break;
			}
			else if (currentNode->status == color) {
				numFoundInRow++;
			}
				if (numFoundInRow == 4) {
				return numFoundInRow;
			}
		}
		currentNode = nodeToProbe;
		while(1) {
			currentNode = currentNode->botLeft;
			if (currentNode == NULL) {
				break;
			}
			else if (currentNode->status != color) {
				break;
			}
			else if (currentNode->status == color) {
				numFoundInRow++;
			}
				if (numFoundInRow == 4) {
				return numFoundInRow;
			}
		}
		break;
	}
	return numFoundInRow;
}

/*
 *
 */
int probeSurrounding(Node* nodeToProbe, int color) {
	int maxInARow = 1;
	int currentRow = 1;

	currentRow = probeDirection(nodeToProbe, color, BOTTOM);
	if (currentRow > maxInARow) maxInARow = currentRow;
	currentRow = probeDirection(nodeToProbe, color, RIGHT);
	if (currentRow > maxInARow) maxInARow = currentRow;
	currentRow = probeDirection(nodeToProbe, color, TOP_LEFT);
	if (currentRow > maxInARow) maxInARow = currentRow;
	currentRow = probeDirection(nodeToProbe, color, TOP_RIGHT);
	if (currentRow > maxInARow) maxInARow = currentRow;

	return maxInARow;
}

/*
 *
 */
int checkVictory(Node* nodeToCheck, int color) {
	int maxInRow = probeSurrounding(nodeToCheck, color);
	if (maxInRow >= 4) {
		return GAME_WON;
	}
	else return RUNNING;
}

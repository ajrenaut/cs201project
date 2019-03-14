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
	switch gameMode {
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

	printBoard(board);
	int gameStatus = RUNNING;
	while(gameStatus == RUNNING) {
		int turnCounter = 0;
		if (turnCounter % 2 == 0)
			takeTurn(RED, playerOne, board);
		else if (turnCounter % 2 == 1) {
			takeTurn(BLUE, playerTwo, board);
		}
	}


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
	char playerColor[4];
	switch (color) {
	case RED :
		strcpy(playerColor, "RED");
		break;
	case BLUE :
		strcpy(playerColor, "BLUE");
		break;
	}
	printf("\n%s's player's turn!", playerColor)

	int boardWidth = width;
	int columnNum = 0;
	switch (playerType) {
	case PLAYER :
		printf("\nEnter a column number between 1 and %d to place a piece.", boardWidth)
		printf("\nColumn: ");
		scanf("%d", columnNum);
		while (columnNum < 1 || columnNum > boardWidth) {
			printf("\n\nERROR: Number must be between 1 and %d. Try again.", boardWidth);
			printf("Column: ");
			scanf("%d", columnNum);
		}
		printf("\n%s places a piece in column %d", columnNum);
		placePiece(board, playerColor, columnNum);

		// Check for victory.
		// Return GAME OVER if game is won, else break
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

void placePiece(Node *board, int color, int column) {
	Node *selectedNode = board;

	for (int i = 1; i < column; i++) {
		selectedNode = selectedNode->right;
	}

	while (selectedNode->status != EMPTY) {
		selectedNode = selectedNode->top;
	}

	selectedNode->status = color;
	return;
}

/*
 * Takes a node, the player's color, and
 */
int probeDirection(Node* inputNode, int color, int direction) {
	int numFoundInRow = 1;
	Node *nodeToProbe = inputNode;
	Node *currentNode = nodeToProbe;
	switch (direction) {
	case right :
	case left :
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
	case top:
	case bottom:

		break;
	case topLeft:
	case bottomRight:

		break;
	case topRight:
	case bottomLeft:

		break;
	}
	//Add total
	return numFoundInRow
}
int probeSurrounding(Node* board, int color, int column, int row = -1) {
	//Probe horizontally, vertically, and both diagonals
	int maxInARow = 1;
}
int checkVictory(Node*, int);

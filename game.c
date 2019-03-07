#include "game.h"
#include "enums.h"

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

void printBoard(Node *board) {
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
	printf("\n\n");

	return;
}

int takeTurn(int color, int playerType, Node *board) {
	switch (playerType) {
	case PLAYER :
		// TODO: Player Turn steps
		break;
	case AI :
		// TODO: AI Turn Steps
		break;
	}
	return RUNNING;
}

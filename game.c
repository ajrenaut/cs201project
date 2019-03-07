#include "game.h"

 Node *createNode() {
	Node *newNode = malloc(sizeof(Node));
	newNode->isEmpty = true;
	newNode->isRed = false;
	newNode->isBlue = false;

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
	enum { VS_AI = 1, VS_PLAYER = 2 };
	Node *board;
	printf("Welcome to Connect Four! Please select game mode.\n");
	printf("For 1 player versus AI, type 1. For player versus player, type 2.\n");
	printf("Game type: ");
	scanf("%d", &gameMode);
	while(gameMode!= VS_AI || gameMode != VS_PLAYER) {
		printf("Answer not recognized. Please enter 1 for vs. AI, or 2 for vs. another player.\n");
		printf("Game type: ");
		scanf("%d", &gameMode);
	}
	printf("Okay! Please enter board dimensions: \n");
	printf("Board width: ");
	scanf("%d", &boardWidth);
	printf("Board height: ");
	scanf("%d", &boardHeight);

	printf("\nAlright! Looks like you'll be playing against ");
	switch (gameMode) {
		case VS_AI :
			printf("the AI.");
			break;
		case VS_PLAYER :
			printf("another player.");
			break;
	}
	printf("\nThe board will be %d x %d.", boardWidth, boardHeight);
	//printf("\nIs all of that correct?");
	//printf("\nY/N: ");

	board = buildBoard(boardWidth, boardHeight);


	// testBoard(board);

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

/* void testBoard(Node *board) {
	int widthCount = 0, heightCount = 0;
	for (Node *curRow = board ; curRow != NULL ; curRow = curRow->top) {
		for (Node *curNode = curRow; curNode != NULL; curNode = curNode->right) {
			printf("%d,%d | ", widthCount, heightCount);
			widthCount++;
		}
		printf("\n\n");
		heightCount++;
		widthCount = 0;
	}


	return;
} */

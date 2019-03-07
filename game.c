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

void startgame() {
	int boardWidth, boardHeight;
	Node *board;
	printf("Enter width and height:");
	scanf("%d", &boardWidth);
	scanf("%d", &boardHeight);
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

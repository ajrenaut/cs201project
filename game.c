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
}

void startgame() {
	int boardWidth, boardHeight;
	Node *bottomLeftNode;
	printf("Enter width and height:");
	scanf("&d &d", boardWidth, boardHeight);
	bottomLeftNode = buildBoard(boardWidth, boardHeight);

}

Node* buildBoard(int width, int height) {
	Node *bottomLeftNode;
	Node *startOfPreviousRow;
	for (int i = 0; i < height; i++) {
		Node *startOfNewRow = createNode();
		Node *currentNode = startOfNewRow;
		for (int j = 0; j < width; j++)
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
				currentUpper->botleft = currentLower->left;
				currentUpper->botRight = currentLower->right;

				currentLower->top = currentUpper;
				currentLower->topleft = currentUpper->left;
				currentLower->topRight = currentUpper->right;

				currentUpper = currentUpper->left;
				currentLower = currentLower->left;
			}
		}
		startOfPreviousRow = startOfNewRow;
	}

	while(bottomLeftNode->left) {
		bottomLeftNode = bottomLeftNode->left;
	}
	while(bottomLeftNode->bottom) {
		bottomLeftNode = bottomLeftNode->bottom;
	}

	return bottomLeftNode;
}

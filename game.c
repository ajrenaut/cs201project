#include "game.h"

void startgame() {
	buildbo
}

Node* buildBoard() {
	Node *bottomLeftNode;
	for (int i = 0; i < 8; i++) {
		node *baseNode = malloc(sizeof(Node));
		for (int j = 0; j < 8; j++) {
			Node *newNode = malloc(sizeof(Node));
			baseNode.right = newNode;
			newNode.left = baseNode;
			baseNode = newNode;
		}
		if (i > 0) {
			// Connect new row to old lower rows
		}
	}
	return bottomLeftNode;
}

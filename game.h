#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node {
	bool isEmpty;
	bool isRed;
	bool isBlue;

	struct Node *top;
	struct Node *topRight;
	struct Node *right;
	struct Node *botRight;
	struct Node *bottom;
	struct Node *botLeft;
	struct Node *left;
	struct Node *topLeft;
} Node;

// Node functions
Node *createNode();

// Game functions
void startgame();
void playerturn();
void aiturn();
void endgame();

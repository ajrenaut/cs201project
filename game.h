#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct _node {
	bool isEmpty;
	bool isRed;
	bool isBlue;

	struct _node *top;
	struct _node *topRight;
	struct _node *right;
	struct _node *botRight;
	struct _node *bottom;
	struct _node *botLeft;
	struct _node *left;
	struct _node *topLeft;
} Node;

// Node functions
Node *createNode();

// Game functions
void runGame();
//void playerturn(int playerNum, Node *board);
//void aiturn(Node *board);
//void endgame();
Node *buildBoard(int, int);
void testBoard(Node*);

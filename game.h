#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
	int status;

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
void takeTurn(int, int, Node*, int);
void placePiece(Node*, int, int);
//void endgame();
Node *buildBoard(int, int);
void testBoard(Node*);
void printBoard(Node*, int);
int probeDirection(Node*, int, int);
int probeSurrounding(Node*, int, int);
int checkVictory(Node*, int);

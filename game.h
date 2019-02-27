#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void startgame();
void playerturn();
void aiturn();
void endgame();

typedef struct node {
	bool isEmpty = true;
	bool isRed = false;
	bool isBlue = false;

	struct Node *top = NULL;
	struct Node *topRight = NULL;
	struct Node *right = NULL;
	struct Node *botRight = NULL;
	struct Node *bottom = NULL;
	struct Node *botLeft = NULL;
	struct Node *left = NULL;
	struct Node *topLeft = NULL;
} Node;

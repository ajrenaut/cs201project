#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _node {
	int status;
} Node;


// Game functions
int runGame(int, int, int);
int takeTurn(int, int, Node **, int, int);
int placePiece(Node **, int, int, int);
//void endgame();
Node** buildBoard(int, int);
void testBoard(Node*);
void printBoard(Node**, int, int);
int checkVictory(Node **, int, int, int, int, int);
int searchDirection(Node **, int, int , int , int);
int aiRoutine(Node **, int, int);

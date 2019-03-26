#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct _node {
	int status;
} Node;

int runGame(int, int, int);
int takeTurn(int, int, Node **, int, int);
int placePiece(Node **, int, int, int);
Node** buildBoard(int, int);
void testBoard(Node*);
void printBoard(Node**, int, int);
int checkVictory(Node **, int, int, int, int, int);
int searchDirection(Node **, int, int , int , int);
int aiRoutine(Node **, int, int);
int readInt();
int readChar();

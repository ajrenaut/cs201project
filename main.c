#include "game.h"
#include "ai.h"
#include "enums.h"

int main() {
	int record[3] = {0, 0, 0};
	int gameResult, gameMode, boardWidth, boardHeight;
	char response[1];

	printf("Welcome to Connect Four! Please select game mode.\n");
	printf("Enter 1 to play against the AI, or 2 to play against another player.\n");
	printf("Game mode: ");
	scanf("%d", &gameMode);

	// Board dimensions must be 4x4 or greater to make game playable.
	// TODO: Sufficiently large boards should prompt a warning.
	printf("Okay! Please enter board dimensions: \n");
	printf("Board width: ");
	scanf("%d", &boardWidth);
	printf("Board height: ");
	scanf("%d", &boardHeight);
	printf("\nThe board will be %d x %d.\n\n", boardWidth, boardHeight);

	while(1) {
		gameResult = runGame(gameMode, boardWidth, boardHeight);
		switch (gameResult) {
		case RED_WIN :
			printf("RED WINS!\n");
			record[0]++;
			break;
		case BLUE_WIN :
			printf("BLUE WINS!\n");
			record[1]++;
			break;
		case GAME_TIED :
			printf("TIE GAME!\n");
			record[2]++;
			break;
		}
		gameResult = -1;
		strcpy(response, "X");

		//make input case insensitive
		printf("The new record is: %d - %d - %d\n", record[0], record[1], record[2]);
		printf("(Red wins - Blue wins - Ties)\n");
		printf("\nPlay again using same settings?\n(Y/N):");
		scanf("%s", response);
		if (strcmp(response,"Y")==0) {
			printf("\nOkay! Setting up a new game.\n\n");
		}
		else if (strcmp(response,"N")==0) {
			printf("\nPlay again with new settings?\n(Y/N):");
			scanf("%s", response);
			if (strcmp(response,"N")==0) {
				printf("\nThanks for playing!");
				return 0;
			}
			else if (strcmp(response,"Y")==0) {
				printf("Enter 1 to play against the AI, or 2 to play against another player.\n");
				printf("Game mode: ");
				scanf("%d", &gameMode);

				// TODO: Sufficiently large boards should prompt a warning.
				printf("Okay! Please enter board dimensions: \n");
				printf("Board width: ");
				scanf("%d", &boardWidth);
				printf("Board height: ");
				scanf("%d", &boardHeight);
				printf("\nThe board will be %d x %d.\n\n", boardWidth, boardHeight);
			}
		}
	}
	return 0;
}

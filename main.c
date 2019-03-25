#include "game.h"
#include "ai.h"
#include "enums.h"

int main() {
	int record[3] = {0, 0, 0};
	int gameResult, gameMode, boardWidth, boardHeight;
	int savedWidth, savedHeight, savedGameMode;
	char response[1];

	printf("Welcome to Connect Four! Please select game mode.\n");
	printf("Enter 1 to play against the AI, or 2 to play against another player.\n");
	printf("Game mode: ");
	scanf("%d", &gameMode);

	/*
	 * Boards with dimensions smaller than 4x4 are often unwinnable as they
	 * only allow for column or row victories. So, they are not valid input.
	 * Also, boards with widths >= than 20 and heights greater than 10
	 * are playable, but begin to display unpleasantly based on the size of
	 * the terminal in which the game is run. These warning boundaries are
	 * based on a standard 80x24 terminal.
	 * TODO: Sufficiently large boards should prompt a warning.
	 */
	printf("Okay! Please enter board dimensions: \n");
	printf("Board width: ");
	scanf("%d", &boardWidth);
	while(boardWidth < 4) {
		printf("\nBoard width should be 4 or greater to ensure a winnable game.\n");
		printf("Board width: ");
		scanf("%d", &boardWidth);
	}
	if (boardWidth >= 20) {
		printf("WARNING: Widths of 20 or greater may cause the display to"
				" become unwieldy or awkward.\n");
	}
	printf("Board height: ");
	scanf("%d", &boardHeight);
	while(boardHeight < 4) {
		printf("\nBoard height should be 4 or greater to ensure a winnable game.\n");
		printf("Board height: ");
		scanf("%d", &boardHeight);
	}
	if (boardHeight >= 10) {
		printf("WARNING: Heights of 10 or greater may cause the display to"
				" become unwieldy or awkward.\n");
	}
	printf("\nThe board will be %d x %d.\n\n", boardWidth, boardHeight);
	savedWidth = boardWidth;
	savedHeight = boardHeight;
	savedGameMode = gameMode;

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
		strcpy(response, "X");

		//TODO: make input case insensitive
		printf("The new record is: %d - %d - %d\n", record[0], record[1], record[2]);
		printf("(Red wins - Blue wins - Ties)\n");
		printf("\nPlay again using same settings?\n(Y/N):");
		scanf("%s", response);
		if (strcmp(response,"Y")==0) {
			printf("\nOkay! Setting up a new game.\n\n");
			boardWidth = savedWidth;
			boardHeight = savedHeight;
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

				// Here, the current win/loss/tie record is reset if the player
				// decides to change his or her opponent from AI to human or
				// vice versa.
				if (gameMode != savedGameMode) {
					record[0] = 0; record[1] = 0; record[2] = 0;
					savedGameMode = gameMode;
				}

				// TODO: Sufficiently large boards should prompt a warning.
				printf("Okay! Please enter board dimensions: \n");
				printf("Board width: ");
				scanf("%d", &boardWidth);
				while(boardWidth < 4) {
					printf("\nBoard width should be 4 or greater to ensure a winnable game.\n");
					printf("Board width: ");
					scanf("%d", &boardWidth);
				}
				printf("Board height: ");
				scanf("%d", &boardHeight);
				while(boardHeight < 4) {
					printf("\nBoard height should be 4 or greater to ensure a winnable game.\n");
					printf("Board height: ");
					scanf("%d", &boardHeight);
				}
				printf("\nThe board will be %d x %d.\n\n", boardWidth, boardHeight);
			}
		}
	}
	return 0;
}

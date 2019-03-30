all: main.c game.c
	gcc main.c game.c -std=c11 -o connectfour
debug: main.c game.c
	gcc main.c game.c -std=c11 -Wall -g -o debug
clean: 
	$ rm -f connectfour*
	$ rm -f debug*
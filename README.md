# Introduction

This program allows a user to play connect on a board size of their choice.

## Overview

This program allows a user to play games of Connect 4 against another human
or against a simple AI. The game board was implemented using a 2D array as a
graph with adjacencies calculated as needed by moving 1 node in any direction.
The reason the graph was implemented this way was because the graph is always
a rectangular grid with well-defined adjacencies (up/down, left/right, and
diagonals). Also, storing each node as an integer is memory efficient than
storing nodes with occupancy values and adjacency lists. This increase in
memory efficiency is important when the board size gets exceedingly large.

The other main aspect to the program is the AI. The AI follows a simple
routine outlined in the code. The AI definitely has some pitfalls that get
worse as the board grows larger, but it is capable of decent matches against
a casual player when playing on a reasonably sized board.

## Usage

The program should be fairly self-explanatory to use. See
[this video](https://youtu.be/d5Clew5sJ80) for a full walkthrough and
demonstration. Or, follow these steps:

1 ) Navigate to the directory in which the program's files were downloaded.

2 ) Use the makefile to compile the program with the following command:

	make

3 ) Run the "connectfour" program with the following command:

	./connectfour
	
4 ) Follow the instructions as prompted by the program to play the game.
Legal inputs are specified, and are limited to single integers or characters
depending on the prompt.

## Borrowed Code

The readChar() and readInt() functions both utilize the same code which was borrowed from
[this](https://stackoverflow.com/questions/4072190/check-if-input-is-integer-type-in-c)
Stack Overflow thread. The code allows my program to filter out bad inputs without crashing.

## Additonal Information and Links

Author		: Alex Renaut

Email		: ajrenaut@crimson.ua.edu

Video link	: https://youtu.be/d5Clew5sJ80

GitHub link	: https://github.com/ajrenaut/cs201project

Git link	: https://github.com/ajrenaut/cs201project.git

Author		: Alex Renaut
Project		: Connect 4
Video link	: N/A
GitHub link	: https://github.com/ajrenaut/cs201project
git link	: https://github.com/ajrenaut/cs201project.git

Overview:
	This program allows a user to play games of Connect 4 against another human
or against a simple AI. The game board was implemented using a 2D array as a
graph with adjacencies calculated as needed by moving 1 node in any direction.
The reason the graph was implemented this way was because the graph is always
a rectangular grid with well-defined adjacencies (up/down, left/right, and
diagonals). Also, storing each node as an integer is memory efficient than
storing nodes with occupancy values and adjacency lists. This slight increase
in memory efficiency is important when the board size gets exceedingly large.
	The other main aspect to the program is the AI. The AI follows a simple
routine outlined in the code. The AI definitely has some pitfalls that get
worse as the board grows larger, but it is capable of decent matches against
a casual player.

HOW TO USE:
1. Compile the program using the included makefile.
2. Run the "connectfour" executable from a terminal.
3. Follow the instructions as prompted. Legal inputs are specified and are
   limited to single integers or characters when applicable. For specifics:
   3a. Enter 1 to play against an AI, or 2 to play against another player.
   3b. Enter your desired board width as an integer greater than or equal to 4
   3c. Repeat the same for the board height.
   3d. Now you can place pieces by entering your desired column as an integer.
   3e. Place pieces until game over.
   3f. At the end of the game, respond to the prompted questions with either
       a Y or an N (yes or no, respectively), to indicate whether or not you
       wish to play the same game again.

The program should be fairly self-explanatory to use. See the video linked at
the top of the README for further demonstration.

Borrowed code: 
	The readInt() and readChar() functions use code borrowed from a thread on
Stack Overflow. The functions allowed me to filter out bad inputs to prevent
crashing. The general function was modified to include return codes as well as
read in single integers and characters specifically. A link to the source
thread can be found below.
	
https://stackoverflow.com/questions/4072190/check-if-input-is-integer-type-in-c

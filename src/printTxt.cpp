// Filename: printTxt.cpp
// Authors: Matty's Merry Militia
// This file will format and then update the terminal with the text


#include "../include/printTxt.h"


void print_terminal(VECTOR<STRING>& lines)
{
	// this function will clear the terminal screen
	// and then print out each line from a vector of strings

	COUT << "\033[2J";		// clear the screen
	COUT << "\033[0;0H";	// move cursor to top of terminal

	struct winsize w;	// create a struct winsize w, which will give terminal size
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); // obtain the size of the terminal window

	// print all the lines except for the last two
	for (unsigned int i = 0; i+2 < w.ws_row; i++) {
		if ( i < lines.size() ) {
			// print the line from the file
			printLine( lines.at(i) );
		} else {
			// print the dash
			printLine();
			// check if last line of printing
			// do not add a new line at end of terminal
			// this will need to be changed because 
			// it is very ugly and does not work with
			// files that are bigger than the terminal
			// size
		}
	}

	// print a highlight bar at the end
	highlightBar( w.ws_col );
	// print a message about the file
	fileStatus();

	COUT << "\033[0;0H"; // move cursor to top of terminal

	return;
}


void printLine( STRING& line )
{
	// this function will format and print a line
	// change this to add coloring later
	COUT << line << ENDL;
}

void printLine( void )
{
	// this function will print a dash
	// change this alongside the other things later
	COUT << "-" << ENDL;
}

void highlightBar( unsigned int row )
{
	// print a highlighted bar at the end of the text editor
	COUT << "\033[42m";
	// print spaces for the entire row
	for (unsigned int i = 0; i < row; i++)
		COUT << " ";
	COUT << "\033[m";
	COUT << ENDL;
}

void fileStatus( void )
{
	// useless right now
	COUT << "\033[m";
}

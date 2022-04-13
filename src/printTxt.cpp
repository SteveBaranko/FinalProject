// Filename: printTxt.cpp
// Authors: Matty's Merry Militia
// This file will format and then update the terminal with the text


#include "../include/printTxt.h"


void print_terminal(VECTOR<STRING>& lines)
{
	// this function will clear the terminal screen
	// and then print out each line from a vector of strings

	COUT << CLEAR_SCREEN;		// clear the screen
	COUT << CURS_TO_TOP;	// move cursor to top of terminal

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
	fileStatus( "file name", w.ws_row );

	COUT << CURS_TO_TOP; // move cursor to top of terminal

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

void highlightBar( unsigned int rowSz )
{
	// print a highlighted bar at the end of the text editor
	COUT << PNT_BAR_TO_END;
	// print spaces for the entire row
	for (unsigned int i = 0; i < rowSz; i++)
		COUT << " ";
	COUT << CLEAR_FORMAT;
	COUT << ENDL;
}

void fileStatus( unsigned int row )
{
	// useless right now
	COUT << "\033[" << row << ";0H";	
	COUT << CLEAR_FORMAT;
}
void fileStatus( STRING status, unsigned int row )
{
	// useless right now
	COUT << CSI << row << ";0H";	
	COUT << status;
	COUT << CLEAR_FORMAT;
	//COUT << "\033[m";
}
void cursPos( unsigned int x, unsigned int y )
{
	COUT << CSI << y << ";" << x << "H";
}
void scrollUp( unsigned int lines )
{
	COUT << CSI << lines << "S";
}
void scrollDown( unsigned int lines )
{
	COUT << CSI << lines << "T";
}


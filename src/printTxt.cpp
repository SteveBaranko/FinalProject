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

	for (unsigned int i = 0; i < lines.size(); i++)
		COUT << lines.at(i) << ENDL;

	return;
}

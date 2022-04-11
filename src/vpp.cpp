/*************************
 * Authors: Matty's Merry Militia
 * File Name: vpp.cpp
 * Date created: 4/9/2022
 * File Contents: This file contains the main function
*************************/

#include "../include/vppFunc.h"

int main(int argc, char* argv[]){

	enableRawMode();
	setHandlers();

	if (argc < 2) {
		// FIx this, testing printing to terminal
		// Eventually we will open an empty text
		// editor.
		COUT << "Too few arguments" << ENDL;
		return -1;
	}

	// eventually print error for not opening file
	if ( check_permissions( argv[1] ) < 0 ) {
		COUT << "ERROR: Cannot open file" << ENDL;
		return -1;
	}

	VECTOR<STRING> lines;
	IFSTREAM inFile( argv[1] );

	openFile( lines, inFile );

	print_terminal( lines );

	char c;

	while (1){
		CIN.get(c);
		if (c == 'q') break;
	}

	COUT << "\033[2J";		// clear the screen
	COUT << "\033[0;0H";	// move cursor to top of terminal


	return 0;
}

/*************************
 * Authors: Matty's Merry Militia
 * File Name: vpp.cpp
 * Date created: 4/9/2022
 * File Contents: This file contains the main function
*************************/

#include "../include/vppFunc.h"

int main(int argc, char* argv[]){

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

	open_file( lines, inFile );

	print_terminal( lines );

	return 0;
}

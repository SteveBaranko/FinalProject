// Filename: printTxt.h
// Authors: Matty's Merry Militia
// This file will contain the function declarations for printTxt.cpp



#ifndef printTxt_H
#define printTxt_H

// C++ libraries to include
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

// C libraries to include
#include<sys/ioctl.h>
#include<unistd.h>
#include<termios.h>

#define COUT std::cout
#define CIN std::cin
#define ENDL std::endl
#define STRING std::string
#define VECTOR std::vector
#define IFSTREAM std::ifstream
#define OFSTREAM std::ofstream

#define CLEAR_SCREEN "\033[2J"
#define CURS_TO_TOP "\033[0;0H"
#define PNT_BAR_TO_END "\033[042m"
#define CLEAR_FORMAT "\033[m"
#define ESC "\033"

void print_terminal(VECTOR<STRING>& lines);
void printLine( STRING& line );
void printLine( void );
void highlightBar( unsigned int rowSz );
void fileStatus( unsigned int row );
void fileStatus( STRING status, unsigned int row );

class Cursor
{
	private:
		unsigned int x;
		unsigned int y;

	public:
		Cursor( ): x( 0 ), y( 0 ) { }
		Cursor( unsigned int xIn, unsigned int yIn ): x( xIn ), y( yIn ) { }
		~Cursor( ) { }

		void updatePosition( unsigned int xIn, unsigned int yIn ) {
			x = xIn;
			y = yIn;
		}

		unsigned int getX( ) {
			return x;
		}

		unsigned int gety( ) {
			return y;
		}
	
};

class Terminal
{
	
	private:
		unsigned int row;
		unsigned int col;
		VECTOR< STRING > lines;
		STRING fileName;
		Cursor curr;
		
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
			//COUT << "\033[42m";
			COUT << PNT_BAR_TO_END;
			// print spaces for the entire row
			for (unsigned int i = 0; i < rowSz; i++)
				COUT << " ";
			//COUT << "\033[m";
			COUT << CLEAR_FORMAT;
			COUT << ENDL;
		}

		void fileStatus( unsigned int rowEnd )
		{
			// useless right now
			COUT << "\033[" << rowEnd << ";0H";	
			COUT << "\033[m";
		}

		void fileStatus( STRING status, unsigned int rowEnd )
		{
			// useless right now
			COUT << "\033[" << rowEnd << ";0H";	
			COUT << status;
			COUT << CLEAR_FORMAT;
			//COUT << "\033[m";
		}

		

	public:
		Terminal( ): row( 0 ), col( 0 ), lines( ), fileName( "" ), curr( ){ }
		Terminal( unsigned int rowIn, unsigned int colIn ): row( rowIn ), col( colIn ), lines ( ), fileName( "" ), curr( ) { }
		Terminal( unsigned int rowIn, unsigned int colIn, STRING fileIn ): row( rowIn ), col( colIn ), lines ( ), fileName( fileIn ), curr( ) { }
		~Terminal( ) { }

		
		void updateSize( unsigned int rowIn, unsigned int colIn ) {
			row = rowIn;
			col = colIn;
		}

		void updateTerminal() {
			COUT << CLEAR_SCREEN;		// clear the screen
			COUT << CURS_TO_TOP;	// move cursor to top of terminal
			for (unsigned int i = 0; i < (unsigned int) row-2; i++) {
				if ( i < lines.size() ) {
					printLine( lines.at(i) );
				} else {
					printLine();
				}
			}

			highlightBar( col );

			fileStatus( fileName, row );

			//COUT << "\033[0;0H";	// move cursor to top of terminal
			COUT << CURS_TO_TOP;
		}

		void openFile(IFSTREAM& inFile) {
			// this function will receive a file stream, read the lines of the 
			// file into a vector of strings passed by reference, then close
			// the file
			//
			// The function will take in the vector to be filled and the file to
			// read from
			STRING lineStr;
			char c;

			// continually get bytes from file
			// read them into the char c
			while ( inFile.get(c) ) {
				// check for newline
				if ( c == '\n' ) {
					// add line to vector lines
					lines.push_back(lineStr);
					// clear the string lineStr
					lineStr.clear();
					continue;
				}
				lineStr.push_back(c);
			}

			inFile.close();
		}

};

#endif

// Filename: printTxt.h
// Authors: Matty's Merry Militia
// This file will contain the function declarations for printTxt.cpp



#ifndef printTxt_H
#define printTxt_H

// C++ libraries to include
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<cctype>

// C libraries to include
#include<sys/ioctl.h>
#include<unistd.h>
#include<termios.h>
#include "defines.h"
#include "colors.h"
#include "../include/colorPrint.h"

void print_terminal(VECTOR<STRING>& lines);
void printLine( STRING& line );
void printLine( void );
void highlightBar( unsigned int rowSz );
void fileStatus( unsigned int row );
void fileStatus( STRING status, unsigned int row );

class Terminal
{
	
	private:
		unsigned int row;
		unsigned int col;
		VECTOR< STRING > lines;
		STRING fileName;
		unsigned int cursorX;
		unsigned int cursorY;
		unsigned int offset;
		bool open;
		bool dirty;
		unsigned int tabLen;
		
		void printLine( STRING& line )
		{

			Colors colors;
			
			STRING word;

			/*
			// Testing Cursor movement and lineSize()
			COUT << "\033[2K";
			COUT << line << " (lineSize: " << lineSize(line) << ")" << ENDL;
			return;
			*/
			

			VECTOR< STRING > words;
			unsigned int prevGrp;
			unsigned int currGrp;
			if ( line.empty() ) {
				COUT << "\033[2K";
				COUT << line;
				COUT << COLORS_NORMAL;
				COUT << ENDL;
				return;
			}
			bool first = true;
			prevGrp = charGroup( line.at(0) );
			word.push_back( line.at(0) );

			// add each word and spaces to vector 
			for ( char &i : line ) {
				if (first) { first = false; continue; }

				currGrp = charGroup( i );
				if ( prevGrp != currGrp ) {
					if ( !word.empty() )
						words.push_back( word );
					word.clear();
					word.push_back( i );
					prevGrp = currGrp;
					continue;
				}
				word.push_back( i );
			}
			if ( !word.empty() )
				words.push_back( word );

			// print each word to terminal
			unsigned int printSz = 0;
			bool comment = false;
			bool quotes = false;
			COUT << "\033[2K";
			for ( STRING &wrd : words ) {
				if ( wrd == "//" && !quotes ) {
					COUT << CSI << "38;2;205;0;0m"; // RED
					comment = true;
				}
				if ( wrd == "\"" && !comment ) {
					quotes = !quotes;
					// now in a " "
					if ( quotes ) {
						COUT << CSI << "38;2;0;180;0m";
					} else {
						COUT << wrd;
						COUT << COLORS_NORMAL;
						continue;
					}
				}
				if (wrd.at(0) == '\t') {
					for (unsigned int i = 0; i < (unsigned int) wrd.size(); i++) {
						for (unsigned int j = 0; j < (unsigned int) tabLen - (printSz % tabLen); j++) {
							COUT << " ";
						}
						printSz += tabLen - (printSz % tabLen);
					}
					//COUT << CSI << "38;2;100;0;100m";
					continue;
				}
				if ( colors.find( wrd ) == "" || comment || quotes )
					COUT << wrd;
				else
					COUT << CSI << colors.find( wrd ) << wrd << COLORS_NORMAL;
				if (wrd == "#include")
						COUT << CSI << "38;2;0;180;0m";
				printSz += (unsigned int) wrd.size();
			}

			COUT << COLORS_NORMAL;
			COUT << ENDL;

			return;
			// this function will format and print a line
			// change this to add coloring later
			// COUT << "\033[2K";
			// COUT << line << ENDL;
		}


		unsigned int charGroup( char& c )
		{
			switch (c) {
				case ' ':
					return 0;
				case '\t':
					return 1;
				case '/':
					return 2;
				case '*':
					return 2;
				case '(':
					return 3;
				case ')':
					return 3;
				case '[':
					return 3;
				case ']':
					return 3;
				case '{':
					return 3;
				case '}':
					return 3;
				case '<':
					return 3;
				case '>':
					return 3;
				case ':':
					return 3;
				case ';':
					return 3;
				case '"':
					return 4;
				default:
					return 5;
			}
		}

		void printLine( void )
		{
			// this function will print a dash
			// change this alongside the other things later
			COUT << "\033" << "[2K";
			COUT << "-" << ENDL;
		}

		void highlightBar( unsigned int rowSz )
		{
			// print a highlighted bar at the end of the text editor
			//COUT << "\033[42m";
			COUT << PNT_BAR_TO_END;
			// print fileName
			COUT << CSI << "38;2;10;10;10m";
			COUT << fileName;
			// print spaces for the rest row
			for (unsigned int i = (unsigned int) fileName.size(); i < rowSz; i++)
				COUT << " ";
			//COUT << "\033[m";
			COUT << CLEAR_FORMAT;
			COUT << ENDL;
		}

		void fileStatus( unsigned int rowEnd )
		{
			// useless right now
			COUT << "\033[" << rowEnd << ";0H";	
			COUT << "\033[2K";
			COUT << "\033[m";
		}

		void fileStatus( STRING status, unsigned int rowEnd )
		{
			// useless right now
			COUT << "\033[" << rowEnd << ";0H";	
			COUT << "\033[2K";
			COUT << status;
			COUT << CLEAR_FORMAT;
			//COUT << "\033[m";
		}

		unsigned int lineSize( STRING line )
		{
			// this function will give the size of the lines in
			// cursor units because not all characters have equal size
			// e.g. \t is longer than a \s
			if (line.size() == 0)
				return 0;
			unsigned int sz = 0;
			for (unsigned int i = 0; i < (unsigned int) line.size(); i++) {
				if ( line.at(i) == '\t' ) {
					sz += (unsigned int) tabLen - ( sz % tabLen );
					continue;
				}
				sz++;
			}
			return sz;
			//return (unsigned int) line.size();	
		}
		
		unsigned int cursStrPos( void )
		{
			unsigned int sz = 0;
			for (unsigned int i = 0; i < (unsigned int) lines.at(cursorY-1+offset).size(); i++) {
				if ( lines.at(cursorY-1+offset).at(i) == '\t') {
					sz += (unsigned int) tabLen - (sz % tabLen);
				} else {
					sz++;
				}
				if (sz == cursorX)
					return i;
				if (sz > cursorX)
					return (unsigned int) i;
			}
			return (unsigned int) lines.at(cursorY-1+offset).size()-1;
		}

		unsigned int cursLinePos( unsigned int ind )
		{
			// return the cursor position on screen given the char
			// of the cursor in the string
			unsigned int cursRow = (unsigned int) cursorY-1+offset;
			//unsigned int cursCol = (unsigned int) cursorX-1;
			unsigned int sz = 0;

			if ( ind > (unsigned int) lines.at(cursRow).size() )
				return lineSize( lines.at(cursRow) );

			for (unsigned int i = 0; i < ind; i++) {
				if ( lines.at(cursRow).at(i) == '\t') {
					sz += (unsigned int) tabLen - (sz % tabLen);
				} else {
					sz++;
				}
			}
			return sz;		
		}

	public:
		Terminal( ): row( 0 ), col( 0 ), lines( ), fileName( "" ), cursorX( 1 ), cursorY( 1 ), offset( 0 ), open( true ), dirty( false ), tabLen( 4 ){ }
		Terminal( unsigned int rowIn, unsigned int colIn ): row( rowIn ), col( colIn ), lines ( ), fileName( "" ), cursorX( 1 ), cursorY( 1 ), offset( 0 ), open( true ), dirty( false ), tabLen( 4 ){ }
		Terminal( unsigned int rowIn, unsigned int colIn, STRING fileIn ): row( rowIn ), col( colIn ), lines ( ), fileName( fileIn ), cursorX( 1 ), cursorY( 1 ), offset( 0 ), open( true ), dirty( false ), tabLen( 4 ) { }
		~Terminal( ) { }

		
		void updateSize( unsigned int rowIn, unsigned int colIn ) {
			row = rowIn;
			col = colIn;
		}

		void updateTerminal() {
			//COUT << CLEAR_SCREEN;		// clear the screen
			COUT << CURS_TO_TOP;	// move cursor to top of terminal
			for (unsigned int i = 0; i < (unsigned int) row-2; i++) {
				if ( i < (unsigned int) lines.size() - offset ) {
					printLine( lines.at(i+offset) );
				} else {
					printLine();
				}
			}

			highlightBar( col );

			//fileStatus( fileName, row );

			//COUT << "\033[0;0H";	// move cursor to top of terminal
			//COUT << CURS_TO_TOP;
			if (cursorX > (unsigned int) lineSize(lines.at(cursorY-1+offset)) + 1)
				COUT << "\033[" << cursorY << ";" << lineSize(lines.at(cursorY-1+offset))+1 << "H";
			else
				COUT << "\033[" << cursorY << ";" << cursorX << "H";

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
				// replace tabs with spaces, fix later
				/*
				if ( c == '\t' ) {
					lineStr.push_back(' ');
					lineStr.push_back(' ');
					continue;
				}
				*/
				lineStr.push_back(c);
			}

			inFile.close();
		}

		bool isOpen( ) {
			return open;
		}

		bool isDirty( ) {
			return dirty;
		}

		void addWarning( STRING warning )
		{
			// add warning to bottom of text editor
			fileStatus( warning, row);
			//fileStatus( fileName, row );
		}

		void close( ) {
			open = false;
		}

		void updateFilename( STRING fileIn ) {
			fileName = fileIn;
		}

		void cursRight( ) {
			// get current position in string, then move
			// the cursor to the next char in string
			unsigned int cursRow = (unsigned int) cursorY-1+offset;
			if (cursorX < (unsigned int) col)
				cursorX++;
			
			
			if ( !lines.at( cursRow ).empty() )
				if ( lines.at( cursRow ).at( cursStrPos() ) == '\t' )
					cursorX += (unsigned int) 1 + tabLen - (cursorX % tabLen);
					

			// limit cursor to right by line size
			if (cursorX > (unsigned int) lineSize(lines.at(cursorY-1+offset)) + 1)
				cursorX = (unsigned int) lineSize(lines.at(cursorY-1+offset)) + 2;
			// Using STRING.size() method instead of lineSize()
			//if (cursorX > (unsigned int) lines.at(cursorY-1+offset).size() )
				//cursorX = (unsigned int) lines.at(cursorY-1+offset).size() + 1;
			return;
			/*
			unsigned int cursRow = (unsigned int) cursorY-1+offset;
			STRSTREAM ss;
			if ( !lines.at( cursRow ).empty() ) {
				ss << lines.at( cursRow ).at( cursStrPos() );
				ss << " ( " << cursStrPos() << " )";
				fileStatus( ss.str(), row );
			}
			*/
		}

		void cursLeft( ) {
			// if the cursor is beyond line, bring it back
			unsigned int cursRow = (unsigned int) cursorY-1+offset;
			if (cursorX > (unsigned int) lineSize(lines.at(cursorY-1+offset)) + 1)
				cursorX = (unsigned int) lineSize(lines.at(cursorY-1+offset)) + 1;
			
				
			// Using STRING.size() method instead of lineSize()
			//if (cursorX > (unsigned int) lines.at(cursorY-1+offset).size() )
				//cursorX = (unsigned int) lines.at(cursorY-1+offset).size() + 1;
			if (cursorX > 1)
				cursorX--;
			if ( !lines.at( cursRow ).empty() )
				if ( lines.at( cursRow ).at( cursStrPos() ) == '\t' && cursorX > 1)
					cursorX -= (unsigned int) tabLen - (cursorX % tabLen) - 1;

			return;
			/*
			unsigned int cursRow = (unsigned int) cursorY-1+offset;
			STRSTREAM ss;
			if ( !lines.at( cursRow ).empty() ) {
				ss << lines.at( cursRow ).at( cursStrPos() );
				ss << " ( " << cursStrPos() << " )";
				fileStatus( ss.str(), row );
			}
			*/
		}

		void cursDown( ) {
			if (cursorY < (unsigned int) row-2)
				cursorY++;
			else
				if (offset < (unsigned int) lines.size() + 2 - row) offset++;
			// limit cursor to only lines of the file
			if (cursorY > (unsigned int) lines.size() - offset)
				cursorY = (unsigned int) lines.size() - offset;
			// keep the cursor off space between tabs
			cursRight();
			cursLeft();
			return;
			// limit cursor to right by line size
			if (cursorX > (unsigned int) lines.at(cursorY-1+offset).size() )
				cursorX = (unsigned int) lines.at(cursorY-1+offset).size() + 1;
		}

		void cursUp( ) {
			if (cursorY > 1)
				cursorY--;
			else
				if ( offset > 0 ) offset--;
			// keep the cursor off space between tabs
			cursRight();
			cursLeft();
			return;
			// limit cursor to right by line size
			if (cursorX > (unsigned int) lines.at(cursorY-1+offset).size() )
				cursorX = (unsigned int) lines.at(cursorY-1+offset).size() + 1;
		}

		void backspaceChar( ) {
			unsigned int cursRow = (unsigned int) cursorY-1+offset;
			unsigned int cursCol = (unsigned int) cursorX-1;
			// debugging, printing cursor location
			STRSTREAM ss;
			ss << "(" << cursCol << ", " << cursRow << ")";
			//fileStatus( ss.str(), row );
			dirty = true;

			if ( lines.at(cursRow).empty() ) {
				// if the line is empty, delete the row
				// only delete row if it is not the first
				if ( cursRow > 0 ) {
					lines.erase( lines.begin() + cursRow );
					cursUp();
					cursorX = (unsigned int) lineSize(lines.at(cursRow - 1)) + 1;
				}
				return;
			} 

			if ( cursCol == 0 ) {
				// cursor at start of line, append row below and delete the row
				// only delete row if it is not the first
				if ( cursRow > 0 ) {
					cursUp();
					cursorX = (unsigned int) lineSize(lines.at(cursRow - 1)) + 1;
					if ( lines.at(cursRow - 1).empty() )
						cursorX = 1;
					lines.at(cursRow - 1).append( lines.at(cursRow) );
					lines.erase( lines.begin() + cursRow );
				}
				return;
			} 

			// otherwise, move cursor to left and delete char
			cursLeft();
			lines.at(cursRow).erase( cursStrPos(), 1 );
			
			return;
		}

		void deleteChar( ) {
			dirty = true;
			if ( lines.at(cursorY-1+offset).empty() )
				return;
			lines.at(cursorY-1+offset).erase( cursStrPos(), 1 );
		}

		void insertChar( char c ) {
			dirty = true;
			if ( !lines.at(cursorY-1+offset).empty() ) {
				if ( cursorX > (unsigned int) lines.at(cursorY-1+offset).size()+1)
					lines.at(cursorY-1+offset) += c;
				else
					lines.at(cursorY-1+offset).insert( lines.at(cursorY-1+offset).begin() + cursorX - 1, c );
				cursorX++;
			} else {
				lines.at(cursorY-1+offset).append(1,c);
				cursorX++;
			}
		}

		void addLine( ) {
			dirty = true;
			// add an extra vector to lines
			lines.insert( lines.begin() + cursorY, "" );
			// move 
			//cursorY++;
			cursDown();
		}

		void save( void ) {
			// fix this later
			if ( fileName.empty() )
				return;

			dirty = false;

			OFSTREAM outFile( fileName );
			
			for (unsigned int i = 0; i < lines.size(); i++) {
				outFile << lines.at(i) << "\n";
			}
			outFile.close();
		}

};

#endif

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
			/*
			for ( char &i : line ) {
					// check for ' '
					
					if ( i == ' ' ) {
							if ( colors.find( word ) == "" ) {
									COUT << word << " ";
									word.clear();
									continue;
							} else {
									//COUT << "test";
									COUT << CSI << colors.find( word ) << word << COLORS_NORMAL;
									word.clear();
							}
							COUT << i;
					} else {
							word.push_back(i);
					}
					
				 // COUT << i;       
			}
			if ( colors.find( word ) == "" ) {
					COUT << word << " ";
					word.clear();
			} else {
					COUT << CSI << colors.find( word ) << word << COLORS_NORMAL;
					word.clear();
			}
			COUT << ENDL;
			*/
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

		unsigned int lineSize( STRING line )
		{
			if (line.size() == 0)
				return 1;
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
					return (unsigned int) i - 1;
			}
			return (unsigned int) lines.at(cursorY-1+offset).size()-1;
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

			fileStatus( fileName, row );

			//COUT << "\033[0;0H";	// move cursor to top of terminal
			//COUT << CURS_TO_TOP;
			if (cursorX > (unsigned int) lineSize(lines.at(cursorY-1+offset)) )
				COUT << "\033[" << cursorY << ";" << lineSize(lines.at(cursorY-1+offset)) << "H";
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

		void close( ) {
			open = false;
		}

		void updateFilename( STRING fileIn ) {
			fileName = fileIn;
		}

		void cursRight( ) {
			if (cursorX < (unsigned int) col)
				cursorX++;
			// limit cursor to right by line size
			if (cursorX > (unsigned int) lineSize(lines.at(cursorY-1+offset)) )
				cursorX = (unsigned int) lineSize(lines.at(cursorY-1+offset));
			// Using STRING.size() method instead of lineSize()
			//if (cursorX > (unsigned int) lines.at(cursorY-1+offset).size() )
				//cursorX = (unsigned int) lines.at(cursorY-1+offset).size() + 1;
		}

		void cursLeft( ) {
			// if the cursor is beyond line, bring it back
			if (cursorX > (unsigned int) lineSize(lines.at(cursorY-1+offset)) )
				cursorX = (unsigned int) lineSize(lines.at(cursorY-1+offset));
			// Using STRING.size() method instead of lineSize()
			//if (cursorX > (unsigned int) lines.at(cursorY-1+offset).size() )
				//cursorX = (unsigned int) lines.at(cursorY-1+offset).size() + 1;
			if (cursorX > 1)
				cursorX--;
		}

		void cursDown( ) {
			if (cursorY < (unsigned int) row-2)
				cursorY++;
			else
				if (offset < (unsigned int) lines.size() + 2 - row) offset++;
			// limit cursor to only lines of the file
			if (cursorY > (unsigned int) lines.size() - offset)
				cursorY = (unsigned int) lines.size() - offset;
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
			return;
			// limit cursor to right by line size
			if (cursorX > (unsigned int) lines.at(cursorY-1+offset).size() )
				cursorX = (unsigned int) lines.at(cursorY-1+offset).size() + 1;
		}

		void deleteChar( ) {
			if ( !lines.at(cursorY-1+offset).empty() ) {
				if (cursorX > 1) {
					lines.at(cursorY-1+offset).erase( cursStrPos()-1, 1 );
					cursorX--;
				} else if (cursorY > 2) {
					lines.at(cursorY-2+offset).append( lines.at(cursorY-1+offset) );
					lines.erase( lines.begin() + cursorY-1+offset );
					cursorY--;
					cursorX = (unsigned int) lines.at(cursorY-2+offset).size();
				}
			} else {
				lines.erase( lines.begin() + cursorY-1+offset );
				cursorY--;
				cursorX = (unsigned int) lines.at(cursorY-2+offset).size();
			}
		}

};

#endif

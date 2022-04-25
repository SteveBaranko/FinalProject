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
#include<stack>
#include<tuple>
#include<sstream>



// C libraries to include
#include<sys/ioctl.h>
#include<unistd.h>
#include<termios.h>
#include <stdio.h>
#include "defines.h"
#include "colors.h"
#include "colorPrint.h"
#include "readIn.h"

#define TUPLE std::tuple
#define MAKE_TUPLE std::make_tuple
#define STACK std::stack
#define GET std::get
#define OSTRINGSTREAM std::ostringstream


void print_terminal(VECTOR<STRING>& lines);
void printLine( STRING& line );
void printLine( void );
void highlightBar( unsigned int rowSz );
void fileStatus( unsigned int row );
void fileStatus( STRING status, unsigned int row );
void checkParentheses ();

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
		unsigned int horizOffset;
		bool open;
		bool dirty;
                bool bad_p;
		unsigned int tabLen;
		
		// rn we are changing the line 
		// so pass by value, not reference
		//void printLine( STRING& line )
		void printLine( STRING line, size_t line_num )
		{

			Colors colors;
			
			STRING word;

			// split each character in the line into a vector of words
			VECTOR< STRING > words;
			unsigned int prevGrp;
			unsigned int currGrp;
			// if the line is empty or if line is less than horizOffset, print nothing and exit function
			if ( line.empty() || horizOffset > lineSize(line) ) {
				COUT << "\033[2K";
				COUT << COLORS_NORMAL;
				COUT << ENDL;
				return;
			}

			// only get the line at the horizontal offset
			unsigned int hInd = cursStrPos( line, horizOffset+1 );
			line = line.substr( hInd, line.size() - hInd );

			// establish what group the first char is in
			bool first = true;
			prevGrp = charGroup( line.at(0) );
			word.push_back( line.at(0) );

			// change this later, for now limit line to the size of the
			// screen so it doesn't overflow
			while ( col < (unsigned int) lineSize( line )) {
				line = line.substr( 0 , line.size() - 1);
			}
                        
			// add each word and spaces to vector 
			for ( char &i : line ) {
				// this if statement will ignore first character
				if (first) { first = false; continue; }

				// check what group the char is in
				currGrp = charGroup( i );
				// create new word to add to vector if new char group
				if ( prevGrp != currGrp ) {
					if ( !word.empty() )
						words.push_back( word );
					word.clear();
					word.push_back( i );
					prevGrp = currGrp;
					continue;
				}
				// add same group char to word
				word.push_back( i );
			}

			// add the last word to words if not empty
			if ( !word.empty() )
				words.push_back( word );

			// print each word to terminal
			// set initialized variables for printing
			unsigned int printSz = 0;
			bool comment = false;
			bool quotes = false;
			COUT << "\033[2K";
                        COUT << CSI << "48:5:166m" << line_num << COLORS_NORMAL << ' ';
			// loop through each word in words
			for ( STRING &wrd : words ) {
				// if wrd is "//", this line is a comment
				if ( wrd == "//" && !quotes ) {
					// set color to red, and comment to true
					COUT << CSI << "38;2;205;0;0m"; // RED
					comment = true;
				}
				// if a wrd is ' " ', this is a quote
				if ( wrd == "\"" && !comment ) {
					// flip bool for quotes
					quotes = !quotes;
					// now in a " "
					if ( quotes ) {
						COUT << CSI << "38;2;0;180;0m";
					} else {
						// outside of a " "
						COUT << wrd;
						COUT << COLORS_NORMAL;
						continue;
					}
				}
				// if a word is a tabbing
				if (wrd.at(0) == '\t') {
					// if multiple tabbings exist
					for (unsigned int i = 0; i < (unsigned int) wrd.size(); i++) {
						// add spaces for each tabbing
						for (unsigned int j = 0; j < (unsigned int) tabLen - (printSz % tabLen); j++) {
							// debugging for now. Tabs are now dashes so it is easier to see them
							COUT << " ";
							//COUT << "-";
						}
						// keep adding the number of spaces added to print line
						printSz += tabLen - (printSz % tabLen);
					}
					continue;
				}
				// if the word is not usually colored, or word is in a quote or a comment, then print
				if ( colors.find( wrd ) == "" || comment || quotes )
					COUT << wrd;
				// print the colored word from the dictionary
				else
					COUT << CSI << colors.find( wrd ) << wrd << COLORS_NORMAL;
				// hard printing #include for now
				if (wrd == "#include")
						COUT << CSI << "38;2;0;180;0m";
				// keep adding the word size to printSz
				printSz += (unsigned int) wrd.size();
			}

			// make colors normal and add a new line + carriage line
			COUT << COLORS_NORMAL;
			COUT << ENDL;

			return;
		}


		unsigned int charGroup( char& c )
		{
			// this function will determine which group each char is in
			// spacing would be its own group, tabs is its own group,
			// comments are its own group, groupings are its own group,
			// quotes are its own group, and everything else is left alone
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
			COUT << PNT_BAR_TO_END;
			// print fileName
			COUT << CSI << "38;2;10;10;10m";
			COUT << fileName;
			// print spaces for the rest row
			for (unsigned int i = (unsigned int) fileName.size(); i < rowSz; i++)
				COUT << " ";
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
		}
		
		unsigned int cursStrPos( void )
		{
			// return the position of the cursor in the string
			// with its current position in the screen
			// 
			// screen -> index
			unsigned int sz = 0;
			for (unsigned int i = 0; i < (unsigned int) lines.at(cursorY-1+offset).size(); i++) {
				if ( lines.at(cursorY-1+offset).at(i) == '\t') {
					sz += (unsigned int) tabLen - (sz % tabLen);
				} else {
					sz++;
				}
				if (sz == cursorX+horizOffset)
					return i;
				if (sz > cursorX+horizOffset)
					return (unsigned int) i;
			}
			return (unsigned int) lines.at(cursorY-1+offset).size()-1;
		}

		unsigned int cursStrPos( STRING line, unsigned int xPos )
		{
			// return the position of the cursor in the string
			// with its current position in the screen
			// 
			// screen -> index
			unsigned int sz = 0;
			for (unsigned int i = 0; i < (unsigned int) line.size(); i++) {
				if ( line.at(i) == '\t'){
					sz += (unsigned int) tabLen - (sz % tabLen);
				} else {
					sz++;
				}
				if (sz == xPos)
					return i;
				if (sz > xPos)
					return (unsigned int) i;
			}
			return (unsigned int) line.size()-1;
		}

		unsigned int cursLinePos( unsigned int ind )
		{
			// return the cursor position on screen given the char
			// of the cursor in the string
			//
			// index -> screen
			unsigned int cursRow = (unsigned int) cursorY-1+offset;
			unsigned int sz = 0;

			if ( ind >= (unsigned int) lines.at(cursRow).size() )
				return lineSize( lines.at(cursRow) );

			sz += 1;
			for (unsigned int i = 1; i <= ind; i++) {
				if ( lines.at(cursRow).at(i-1) == '\t') {
					if ( (sz % tabLen) == 0 )
						sz++;
					else
						sz += (unsigned int) 1 + tabLen - (sz % tabLen);
				} else {
					sz++;
				}
			}
			return (unsigned int) sz - horizOffset;		
		}

	public:
		Terminal( ): row( 0 ), col( 0 ), lines( ), fileName( "" ), cursorX( 1 ), cursorY( 1 ), offset( 0 ), horizOffset( 0 ), open( true ), dirty( false ), tabLen( 4 ){ }
		Terminal( unsigned int rowIn, unsigned int colIn ): row( rowIn ), col( colIn ), lines ( ), fileName( "" ), cursorX( 1 ), cursorY( 1 ), offset( 0 ), horizOffset( 0 ), open( true ), dirty( false ), tabLen( 4 ){ }
		Terminal( unsigned int rowIn, unsigned int colIn, STRING fileIn ): row( rowIn ), col( colIn ), lines ( ), fileName( fileIn ), cursorX( 1 ), cursorY( 1 ), offset( 0 ), horizOffset( 0 ), open( true ), dirty( false ), tabLen( 4 ) { }
		~Terminal( ) { }

		
		void updateSize( unsigned int rowIn, unsigned int colIn ) {
			row = rowIn;
			col = colIn;
		}

		void updateTerminal() {
			//COUT << CLEAR_SCREEN;		// clear the screen
			COUT << CURS_HIDE;
			COUT << CURS_TO_TOP;	// move cursor to top of terminal
			for (unsigned int i = 0; i < (unsigned int) row-2; i++) {
				if ( i < (unsigned int) lines.size() - offset ) {
					printLine( lines.at(i+offset), i + offset + 1);
				} else {
					printLine();
				}
			}

			highlightBar( col );

			//fileStatus( fileName, row );

			//COUT << "\033[0;0H";	// move cursor to top of terminal
			//COUT << CURS_TO_TOP;
			COUT << CURS_SHOW;
			if (cursorX > (unsigned int) lineSize(lines.at(cursorY-1+offset)) + 1)
				COUT << "\033[" << cursorY << ";" << lineSize(lines.at(cursorY-1+offset))+1 << "H";
			else
				COUT << "\033[" << cursorY << ";" << cursorX << "H";

		}

                void checkParentheses () {

                    // this function checks if the parenthesis entered in the file are valid, very similiar to the LeetCode "Valid Parenthesis" Problem
                    bad_p = false;
                    TUPLE <char, size_t, size_t> temp;
                    STACK <TUPLE < char, size_t, size_t>> p_stack;
                    // STACK <char> p_stack;
                    STRING warning;
                    OSTRINGSTREAM warning_draft;

                    for ( size_t i = 0; i < lines.size(); ++i ) {
                        for ( size_t j = 0; j < lines[i].size(); ++j ) {
                            // opening parenthesis
                            if ( ( lines[i][j] == '(' ) || ( lines[i][j] == '[' ) || ( lines[i][j] == '{' ) ) {
                                temp = MAKE_TUPLE( lines[i][j], i, j ); 
                                p_stack.push(temp);
                           // closing parenthesis
                            } else if ( lines[i][j] == ')' ) {
                                // if no corresponding parenthesis
                                if ( p_stack.empty() ) {
                                    bad_p = true;
                                    warning_draft << "Error: Unmatched Parenthsis terminating at: (" << i << ", " << j << ")";
                                    warning = warning_draft.str();
                                    this->addWarning( warning );
                                    return;
                                }
                                // If mismatched parenthesis
                                if ( GET<0>(p_stack.top()) != '(' ) {
                                    bad_p = true;
                                    warning_draft << "Error: Mismatched Parenthsis terminating at: (" << i << ", " << j << ")";
                                    warning = warning_draft.str();
                                    this->addWarning( warning );
                                    return;
                                } else {
                                    p_stack.pop();
                                    continue;
                                }
                            // brackets
                            } else if ( lines[i][j] == ']' ) {
                                // if no corresponding brackets
                                if ( p_stack.empty() ) {
                                    bad_p = true;
                                    warning_draft << "Error: Unmatched Parenthsis terminating at: (" << i << ", " << j << ")";
                                    warning = warning_draft.str();
                                    this->addWarning( warning );
                                    return;
                                }
                                // if mismatched brackets
                                if ( GET<0>(p_stack.top()) != '[' ) {
                                    bad_p = true;
                                    warning_draft << "Error: Unmatched Parenthsis terminating at: (" << i << ", " << j << ")";
                                    warning = warning_draft.str();
                                    this->addWarning( warning );
                                    return;
                                } else {
                                    p_stack.pop();
                                    continue;
                                }
                            // curly braces
                            } else if ( lines[i][j] == '}' ) {
                                // if no corresponding braces
                                if ( p_stack.empty() ) {
                                    bad_p = true;
                                    warning_draft << "Error: Unmatched Parenthsis terminating at: (" << i << ", " << j << ")";
                                    warning = warning_draft.str();
                                    this->addWarning( warning );
                                    return;
                                }
                                // if mismatched braces
                                if ( GET<0>(p_stack.top()) != '{' ) {
                                    bad_p = true;
                                    warning_draft << "Error: Mismatched Parenthsis terminating at: (" << i << ", " << j << ")";
                                    warning = warning_draft.str();
                                    this->addWarning( warning );
                                    return;
                                } else {
                                    p_stack.pop();
                                    continue;
                                }
                           // other (ie non parenthetical character)
                            } else {
                                continue;
                            }
                        }
                    }
                    // If unmatched open parenthesis
                    if ( !p_stack.empty() ) {
                        bad_p = true;
                        warning_draft << "Error: Unmatched Parenthsis OPENING at: (" << GET<1>(p_stack.top()) << ", " << GET<2>(p_stack.top()) << ")";
                        warning = warning_draft.str();
                        this->addWarning( warning );
                        return;
                    }
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
					// add space to end of line
					lineStr += ' ';
					// add line to vector lines
					lines.push_back(lineStr);
					// clear the string lineStr
					lineStr.clear();
					continue;
				}
				lineStr.push_back(c);
			}

			if ( lines.size() == 0 )
				createFile();

			inFile.close();
		}

		void createFile( ) {
			// create one empty string to start out with
			lines.push_back( " " );
		}

		bool isOpen( ) {
			return open;
		}

		bool isDirty( ) {
			return dirty;
		}
		bool isBadP( ) {
			return bad_p;
		}

		void addWarning( STRING warning )
		{
			// add warning to bottom of text editor
			fileStatus( warning, row);
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
			if ( lines.at(cursRow).empty() )
				return;

			unsigned int ind = cursStrPos();

			// check if at last char in string
			if ( ind == (unsigned int) lines.at(cursRow).size() - 1 ) {
				//addWarning( "BLEH" );
				return;
			}

			cursorX = cursLinePos( (unsigned int) ind + 1 );

			if (cursorX > col) {
				horizOffset += tabLen;
				cursorX = cursLinePos( (unsigned int) ind + 1 );
			}

			return;
			// Debugging
			/*
			STRSTREAM ss;
			if ( !lines.at( cursRow ).empty() ) {
				ss << lines.at( cursRow ).at( cursStrPos() );
				ss << " ( " << cursStrPos() << " )";
				ss << " | cursStrPos(): " << cursStrPos();
				ss << " | cursLinePos(): " << cursLinePos( (unsigned int) ind+1 );
				fileStatus( ss.str(), row );
			}
			*/
		}

		void cursLeft( ) {
			// if the cursor is beyond line, bring it back and return
			unsigned int cursRow = (unsigned int) cursorY-1+offset;
			if (cursorX > (unsigned int) lineSize(lines.at(cursorY-1+offset)) + 1) {
				cursorX = (unsigned int) lineSize(lines.at(cursorY-1+offset));
				return;
			}
			
			// move cursor based on the position of characters in the line
			//
			// if the line is empty, exit
			if ( lines.at(cursRow).empty() )
				return;

			// if the cursor is past the end of line, put it at last character
			//
			// get the current char position
			unsigned int ind = cursStrPos();
			// if the index is 0, set cursor to left side of screen
			if (ind == 0) {
				cursorX = 0;
				return;
			}

			if ( cursorX == 1 )
				horizOffset -= tabLen;

			// set cursor to the char position to left
			cursorX = cursLinePos( (unsigned int) ind - 1 );
			return;
			// Debugging
			/*
			STRSTREAM ss;
			if ( !lines.at( cursRow ).empty() ) {
				ss << lines.at( cursRow ).at( cursStrPos() );
				ss << " ( " << cursStrPos() << " )";
				ss << " | cursStrPos(): " << cursStrPos();
				ss << " | cursLinePos(): " << cursLinePos( (unsigned int) ind-1 );
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
			
			// move horizontal offset to keep text on screen
			unsigned int cursRow = (unsigned int) cursorY-1+offset;
			while ( horizOffset > lineSize( lines.at(cursRow) ) )
				horizOffset -= tabLen;

			// keep the cursor off space between tabs
			unsigned int ind = cursStrPos();
			cursorX = cursLinePos( ind );
			return;
		}

		void cursUp( ) {
			if (cursorY > 1)
				cursorY--;
			else
				if ( offset > 0 ) offset--;

			// move horizontal offset to keep text on screen
			unsigned int cursRow = (unsigned int) cursorY-1+offset;
			while ( horizOffset > lineSize( lines.at(cursRow) ) )
				horizOffset -= tabLen;

			// keep the cursor off space between tabs
			unsigned int ind = cursStrPos();
			cursorX = cursLinePos( ind );
			return;
		}

		void cursClick(){
			unsigned int x=0,y=0;
			struct winsize w;
			ioctl(STDOUT_FILENO,TIOCGWINSZ,&w); //gets window size
			char test;
			CIN.get(test); //flushes leading input
			CIN.get(test); //x coordinate of mouse
			x=(unsigned int) test;
			if(x<128){ //keeps x in range
				CIN.get(test); //y coordinate of mouse
				y=(unsigned int) test;
				y-=32; //converts y coordinate to window size
				if(y>(unsigned int)lines.size())
					y=(unsigned int)lines.size(); //keeps cursor in range of file
				if(y>(unsigned int) row-2)
					y=(unsigned int) row-2; // keeps cursor in usable space
				cursorY=y; //sets cursor
				x-=32;
				if(x>(unsigned int)lineSize(lines.at(cursorY-1+offset))) 
					x=(unsigned int)lineSize(lines.at(cursorY-1+offset)); //limits cursor to end of line
				cursorX=x;
			}
			else {
				CIN.get(test); //flushes y output if x out of range
				CIN.get(test); //flushes y output if x out of range
				CIN.get(test); //flushes y output if x out of range
			}
			CIN.get(test); //flush rest of mouse input that is not used
			CIN.get(test);
			CIN.get(test);
			CIN.get(test);
			CIN.get(test);
			CIN.get(test);
		}
		
		void backspaceChar( ) {
			unsigned int cursRow = (unsigned int) cursorY-1+offset;
			dirty = true;

			if ( lines.at(cursRow).size() == 1) {
				// if the line is empty, delete the row
				// only delete row if it is not the first
				if ( cursRow > 0 ) {
					lines.erase( lines.begin() + cursRow );
					cursUp();
					cursorX = (unsigned int) lineSize(lines.at(cursRow - 1));
					cursRight();
				}
				return;
			} 

			unsigned int ind = cursStrPos();

			if ( ind == 0 ) {
				// cursor at start of line, append row below and delete the row
				// only delete row if it is not the first
				if ( cursRow > 0 ) {
					cursUp();
					cursRow = (unsigned int) cursorY-1+offset;
					cursorX = (unsigned int) lineSize(lines.at(cursRow));

					// delete space at end of line
					lines.at(cursRow).erase( lines.at(cursRow).end()-1 );

					if ( lines.at(cursRow).empty() )
						cursorX = 1;
					lines.at(cursRow).append( lines.at(cursRow+1) );
					lines.erase( lines.begin() + cursRow + 1);
				}
				return;
			} 

			// if at end of screen, move horizontal offset back
			if ( cursLinePos( ind ) == 1 )
				horizOffset -= tabLen;

			// otherwise, delete char and update cursorX
			lines.at(cursRow).erase( ind-1, 1 );
			cursorX = cursLinePos( ind-1 );

			return;
		}

		void deleteChar( ) {
			dirty = true;
			unsigned int cursRow = (unsigned int) cursorY-1+offset;
			unsigned int ind = cursStrPos();
			if ( ind == (unsigned int) lines.at( cursRow ).size() - 1 )
				return;
			lines.at(cursRow).erase( cursStrPos(), 1 );
		}

		void insertChar( char c ) {
			dirty = true;
			// get the row of the cursor
			unsigned int cursRow = (unsigned int) cursorY-1+offset;
			unsigned int ind = cursStrPos();
			// if the cursor is at end of line
			lines.at( cursRow ).insert( lines.at(cursRow).begin() + ind, c );
			cursorX = cursLinePos( ind + 1 );
			while ( cursorX > col ) {
				horizOffset += tabLen;
				cursorX = cursLinePos( ind + 1 );
			}
			return;
		}

		void addLine( ) {
			dirty = true;
			// add an extra vector to lines
			unsigned int cursRow = (unsigned int) cursorY-1+offset;

			// if the line is empty or at end of line, add empty line below
			if ( lines.at( cursRow ).empty() || cursorX > lineSize( lines.at( cursRow ) ) ) {
				lines.insert( lines.begin() + cursRow + 1, " " );
				cursDown();
				return;
			}

			// move substr to the line below
			lines.insert( lines.begin() + cursRow + 1, lines.at( cursRow ).substr( cursStrPos(), lines.at( cursRow ).size() - cursStrPos() ) );
			lines.at( cursRow ).erase( lines.at( cursRow ).begin() + cursStrPos(), lines.at( cursRow ).end() );
			// add space to end of lines
			lines.at( cursRow ) += ' ';

			// move 
			cursDown();
			cursorX = 1;
			horizOffset = 0;
		}

		void pageUp( ) {
			// create an signed integer variable to check if offset goes negative
			int overflowOffset = (int) offset;
			// move the offset
			overflowOffset -= 10;
			// keep offset from going where it shouldn't go
			if ( overflowOffset <= 0 ) {
				offset = 0;
				return;
			}
			// overflow is not negative, update value
			offset = (unsigned int) overflowOffset;
		}

		void pageDown( ) {
			// move the offset
			offset += 10;
			// keep cursor on available lines
			cursorY = 1;
			// keep the offset from where it shouldn't go
			if ( offset >= (unsigned int) lines.size() - 1 ) {
				offset = (unsigned int) lines.size() - 1;
				cursorY = 1;
				return;
			}
		}

		void save( void ) {
			// in case nothing is given, default filename is vppEdit
			if ( fileName.empty() ) {
				updateFilename( "vppEdit" );
			}

			// make file clean
			dirty = false;

			OFSTREAM outFile( fileName );
			
			for (unsigned int i = 0; i < lines.size(); i++) {
				// lines.at(i).erase( lines.at(i).end() - 1 ); // erase the last space in each line
				outFile << lines.at(i) << "\n";
			}
			outFile.close();
		}

};

#endif

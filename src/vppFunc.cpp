/****************************
 * File Name: vppFunc.cpp
 * File Created: 4/9/2022
 * Contains the raw mode and other function definitions
****************************/

/*
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>
*/
#include "../include/vppFunc.h"


struct termios orig_termios;

void disableRawMode(void){
	tcsetattr(STDIN_FILENO,TCSAFLUSH,&orig_termios);
}

void enableRawMode(void){
	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disableRawMode);

	struct termios raw=orig_termios;
	raw.c_iflag &= ~(BRKINT|ICRNL|INPCK|ISTRIP|IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO|ICANON|IEXTEN|ISIG);

	tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);
}

void getInput( Terminal& Main )
{
	char c;
	//Main.cursClick();
	fprintf(stdout,"\033[?1000h");
	CIN.get(c);
	if (c == (char) 127) { Main.backspaceChar(); return; }
	if (c == '~') { Main.deleteChar(); return; }
	if (c == (char) 13) { Main.addLine(); return; }
	//if (c) Main.insertChar(c);
	if (c == CTRL('q')) { 
		if ( Main.isDirty() ) {
			Main.addWarning( "Unsaved Changes: Press Ctrl+Q again to quit without saving" );
			CIN.get(c);
			Main.addWarning( " " );
			if ( c != CTRL('q') )
				return;
		}
		Main.close(); 
		return; 
	}
	if (c == CTRL('s')) { Main.save(); return; }
	//if (c == 'p') Main.close();
	//if (c == '\x1b') { Main.close(); return; }
	if (c == '\x1b') {
		CIN.get(c);
		if (c == '[') {
			CIN.get(c);
			//system("clear");
			//fprintf(stdout,"%d\n",c);
			//fprintf(stdout,"\033[?1000l");
			exit(0);
			switch (c) {
				case 'A':
					Main.cursUp();
					break;
				case 'B':
					Main.cursDown();
					break;
				case 'C':
					Main.cursRight();
					break;
				case 'D':
					Main.cursLeft();
					break;
				case 77:
					Main.cursClick();
					break;
				default:
					break;
			}
		}
		return;
	}
	Main.insertChar( c );
	fprintf(stdout,"\033[?1000l");
}




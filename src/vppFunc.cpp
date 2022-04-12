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
	raw.c_lflag &=~(ECHO|ICANON);

	tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);
}

void getInput( Terminal& Main )
{
	char c;
	CIN.get(c);
	if (c == 'q') Main.close();
	if (c == '\x1b') {
		CIN.get(c);
		if (c == '[') {
			CIN.get(c);
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
				default:
					break;
			}
		}
	}
}




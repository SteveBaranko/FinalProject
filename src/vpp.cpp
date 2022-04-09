/****************************
 * File Name: vpp.cpp
 * File Created: 4/9/2022
 * Contains the raw mode and other function definitions
****************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>

struct termios orig_termios;

void tty_raw_mode(void){
	struct termios tty_attr;

	// set raw mode
	tty_attr.c_lflag &=(~(ICANON|ECHO));
	tty_attr.c_cc[VTIME]=0;
	tty_attr.c_cc[VMIN]=1;

	tcsetattr(0,TCSANOW,&tty_attr);
}

void disableRawMode(){
	tcsetattr(STDIN_FILENO,TCSAFLUSH,&orig_termios);
}

void enableRawMod(){
	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disableRawMode);

	struct termios raw=orig_termios;
	raw.c_lflag &=~(ECHO|ICANON);

	tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);
}

/*************************
 * Authors: Matty's Merry Militia
 * File Name: sigController.cpp
 * Date created: 4/10/2022
 * File Contents: This file will contain all signal handlers for vpp.cpp
*************************/

#include "../include/sigController.h"

void sig_handler(int signum)
{
	// this function will take the signal
	// and end the program
	// eventually this will be used properly
	// assign ctrl+z and ctrl+c and other things
	switch(signum) {
		case SIGSEGV:
			COUT << "Segmentation fault (core dumped)" << ENDL;
		//case SIGINT:
			//COUT << "SIGINT" << ENDL;
		default:
			exit(EXIT_SUCCESS);
			break;
	}
}


void setHandlers(void)
{
	// function will set each of the necessary signals 
	// we need to the handler in main
	signal(SIGINT,sig_handler);
	signal(SIGSEGV,sig_handler);
	return;
}

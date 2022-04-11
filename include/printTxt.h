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

void print_terminal(VECTOR<STRING>& lines);
void printLine( STRING& line );
void printLine( void );

#endif

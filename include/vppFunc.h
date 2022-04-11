/*****************************
 * Authors: Matty's Merry Militia
 * File name vppFunc.h
 * Date created: 4/9/2022
 * File contents: This file is the main header for our project
 ****************************/


#ifndef vppFunc_H
#define vppFunc_H

#include<termios.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<signal.h>
#include<cstdlib>

#include <cstdio>
//DLLIST AND MAP ARE NOT INCLUDED YET

#include "colorPrint.h"
#include "mouseFunc.h"
#include "printTxt.h"
#include "readIn.h"
#include "sigController.h"

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

#define COUT std::cout
#define CIN std::cin
#define ENDL std::endl
#define STRING std::string
#define VECTOR std::vector
#define IFSTREAM std::ifstream
#define OFSTREAM std::ofstream

void disableRawMode(void);
void enableRawMode(void);

#endif


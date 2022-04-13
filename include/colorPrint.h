/****************************************
 * Authors: Matty's Merry Militia 
 * colorPrint.h
 * Date created: 4/12/2022
 * This file contains the headers and structs for colorPrint.cpp
 ***************************************/
#ifndef colorPrint_H
#define colorPrint_H

// C++ libraries to include
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

// C libraries to include
#include<sys/ioctl.h>
#include<unistd.h>
#include<termios.h>
#include "defines.h"

//these functions set the colors printed to terminal. Note: It does not autoreset
void restoreDefault();
void setCyan();
void setRed();
void setMagenta();
void setGreen();
void setWhite();
void setYellow();


#endif


/*****************************
 * Authors: Matty's Merry Militia
 * File name vpp.h
 * Date created: 4/9/2022
 * File contents: This file is the main header for our project
 ****************************/


#ifndef VPP_H
#define VPP_H


#include<string.h>
#include<termios.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<signal.h>
#include<iostream>
#include<cstdlib>
#include<vector>
//DLLIST AND MAP ARE NOT INCLUDED YET

#include "colorPrint.h"
#include "mouseFunc.h"
#include "printTxt.h"
#include "readIn.h"
#include "sigController.h"

#define VECTOR std::vector
#define COUT std::cout
#define CIN std

struct termios orig_termios;

void tty_raw_mode(void);
void disableRawMode();
void enableRawMode();

#endif


/*************************
 * Authors: Matty's Merry Militia
 * File Name: sigController.h
 * Date created: 4/10/2022
 * File Contents: This file will contain all function declarations for sigController.cpp
*************************/

#ifndef sigController_H
#define sigController_H

// C++ libraries to include
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<csignal>
#include<cstdlib>
#include "defines.h"

void sig_handler(int signum);
void setHandlers(void);

#endif

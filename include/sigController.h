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

#define COUT std::cout
#define CIN std::cin
#define ENDL std::endl
#define STRING std::string
#define VECTOR std::vector
#define IFSTREAM std::ifstream
#define OFSTREAM std::ofstream

void sig_handler(int signum);
void setHandlers(void);

#endif

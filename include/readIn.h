// Filename: readIn.h
// Authors: Matty's Merry Militia
// This file is to make function declarations for readIn.cpp

#ifndef readIn_H
#define readIn_H

// C libraries to include
#include<errno.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>

// C++ libraries to include
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

int check_permissions(char*& path);
void openFile(VECTOR<STRING>& lines, IFSTREAM& inFile);


#endif

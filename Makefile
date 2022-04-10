# Author: Matty's Merry Militia
# E-mail: dadams22@nd.edu sbaranko@nd.edu ehall9@nd.edu jsteve22@nd.edu
#	Date: 4/9/2022
# This is the Makefile for creating vpp and the associated 
# libraries that would be used for vpp. 

# g++ is the GCC compiler for C++
CC := g++

# CFLAGS are the compiler flags for when we compile C++ code in CSE20312
FLAGS := -O2 -g -Wall -Wextra -Wconversion -Wshadow -Werror -lm
CXXFLAGS := -m64 -std=c++11 $(FLAGS)
CFLAGS := -std=c11 $(FLAGS)

# Folder Variables
INC := include
SRC := src
OBJ := objects
EXE := exe

# Make initialize - Create the objects and executables

initialize:
	rm -rf $(OBJ) $(EXE)
	mkdir $(OBJ) $(EXE)

# Run Compilation Command
# Command: make vpp

$(OBJ)/readIn.o: $(SRC)/readIn.cpp
	$(CC) $(CXXFLAGS) -c $(SRC)/readIn.cpp -o $@

$(OBJ)/printTxt.o: $(SRC)/printTxt.cpp
	$(CC) $(CXXFLAGS) -c $(SRC)/printTxt.cpp -o $@

$(OBJ)/vppFunc.o: $(SRC)/vppFunc.cpp 
	$(CC) $(CXXFLAGS) -c $(SRC)/vppFunc.cpp -o $@

$(OBJ)/vpp.o: $(SRC)/vpp.cpp
	$(CC) $(CXXFLAGS) -c $(SRC)/vpp.cpp -o $@

vppObjs := $(OBJ)/vpp.o $(OBJ)/vppFunc.o $(OBJ)/readIn.o $(OBJ)/printTxt.o

vpp: $(vppObjs) 
	$(CC) $(CXXFLAGS) -o $(EXE)/vpp $(vppObjs) 

clean:
	rm -rf $(OBJ)/* $(EXE)/*

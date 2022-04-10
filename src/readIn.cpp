// Filename: readIn.cpp
// Authors: Matty's Merry Militia
// This file checks to see if specified file exists, is not a directory, and is accesible then checks the permissions for that file

#include "../include/readIn.h"

//#include <errno.h>
//#include <unistd.h>
//#include <dirent.h>

// #include <string.h>
// #include <stdio.h>


// If file does not exist return -1
// If file is not accessible return -2
// If path is directory return -3
// Otherwise return octal value of file permissions for user



int check_permissions ( char*& path ) {

    int rval, permissions_val = 0;
    // Check if does not exis
    rval = access(path, F_OK); 
    if( errno == ENOENT ) {
        permissions_val = -1;
        // fprintf(stderr, strerror(errno));
        return permissions_val;

    // Check if file is not accesible
    } else if ( errno == EACCES ) {
        permissions_val = -2;
        return permissions_val;
    }

  
    // Check if path is to directory
    DIR* dir = opendir(path); 
    if ( dir != NULL ) {
        permissions_val = -3;
        // fprintf(stderr, "Path is directory\n");
        closedir(dir);
        return permissions_val;
    }

    closedir(dir);



    // check if file is executable
    rval = access(path, X_OK);
    if (rval == 0)
        permissions_val = permissions_val | 1;


    // check if file is writeable
    rval = access(path, W_OK);
    if (rval == 0)
        permissions_val = permissions_val | 2;


    // check if file is readable
    rval = access(path, R_OK);
    if (rval == 0)
        permissions_val = permissions_val | 4;



    return permissions_val;

}
        
    
void open_file(VECTOR<STRING>& lines, IFSTREAM& inFile)
{
	// this function will receive a file stream, read the lines of the 
	// file into a vector of strings passed by reference, then close
	// the file
	//
	// The function will take in the vector to be filled and the file to
	// read from
	STRING read_in;
	char c;

	while ( inFile.get(c) ) {
		//COUT << c;
		//lines.push_back(read_in);
		if ( c == '\n' ) {
			lines.push_back(read_in);
			read_in.clear();
			continue;
		}
		read_in.push_back(c);
	}
	//lines.push_back(read_in);

	inFile.close();
}





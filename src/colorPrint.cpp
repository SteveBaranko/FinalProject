
/****************************************
 * Authors: Matty's Merry Militia 
 * colorPrint.cpp
 * Date created: 4/12/2022
 * This file contains the functions to printText ... colorfully
 ***************************************/

#include "../include/colorPrint.h"

void restoreDefault(){
	COUT << COLORS_NORMAL;
}
void setCyan(){
	COUT << CSI << "38;2;0;205;205m";
}
void setRed(){
	COUT << CSI << "38;2;205;0;0m";
}
void setMagenta(){ 
	COUT << CSI << "38;2;205;0;205m";
}
void setGreen(){
	COUT << CSI << "38;2;0;205;0m";
}
void setWhite(){
	COUT << CSI << "38;2;229;229;229m";
}
void setYellow()
	COUT << CSI << "38;2;229;229;16m";
}

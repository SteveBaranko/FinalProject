/*This file includes all of our pound define statements so that all of our programs have the same 
 * global variables
 * defines.h
 * Authors: Matty's Merry Miltia
 * Date 4/12/2022
 *****************************************************************************************/

#ifndef defines_H
#define defines_H

#define COUT std::cout
#define CIN std::cin
//#define ENDL std::endl
#define ENDL "\r\n"
#define STRING std::string
#define VECTOR std::vector
#define IFSTREAM std::ifstream
#define OFSTREAM std::ofstream
#define STRSTREAM std::stringstream

#define CLEAR_SCREEN "\033[2J"
#define CURS_TO_TOP "\033[0;0H"
#define PNT_BAR_TO_END "\033[042m"
#define CLEAR_FORMAT "\033[m"
#define CSI "\033["
#define CURS_HIDE "\033[?25l"
#define CURS_SHOW "\033[?25h"
#define CURS_LOCATE "\033[6n"
#define COLORS_NORMAL "\033[m"


#endif

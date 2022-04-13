#ifndef COLORS_H
#define COLORS_H

#include "defines.h"
#include <unordered_map>
#include <iostream>

#define COUT std::cout
#define UNOR_MAP std::unordered_map
#define STRING std::string
#define ENDL std::endl




class Colors 
{

    private:
        UNOR_MAP<STRING, STRING> colors;


    public:
    
	//COUT << CSI << "38;2;229;229;16m";
        Colors(): colors( ) {
            colors["if"]  =     "38;2;255;0;0m"; // cyan
            colors["for"] =     "38;2;0;255;0m"; // red
            colors["while"] =   "38;2;0;0;255m"; // green
	    colors["else"] =    "38;2;229;229;229m"; // white
        }
        ~Colors() { }



        STRING find( STRING& input) {
            if ( colors.find( input ) == colors.end() ) {
                // COUT << "Error: " << input << " not found." << ENDL;
                return "";
            } else {
                // COUT << input << ": " << colors[input] << ENDL;
                return colors[input];
            }

        }
        


};    


#endif     

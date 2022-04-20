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
            colors["if"]  =     "38;2;229;229;16m"; // yellow
            colors["for"] =     "38;2;229;229;16m"; // yellow
            colors["while"] =   "38;2;229;229;16m"; // yellow
	    			colors["else"] =    "38;2;229;229;16m"; // yellow
						colors["void"] = 		"38;2;0;205;205m"; // blue
						colors["int"] = 		"38;2;0;205;205m"; // blue
						colors["unsigned"]=	"38;2;0;205;205m"; // blue
						colors["long"] = 		"38;2;0;205;205m"; // blue
						colors["bool"] = 		"38;2;0;205;205m"; // blue
						colors["char"] = 		"38;2;0;205;205m"; // blue
						colors["float"] =		"38;2;0;205;205m"; // blue
						colors["struct"] =	"38;2;0;205;205m"; // blue
						colors["return"] =	"38;2;0;205;205m"; // blue
						colors["include"]= "38;2;205;0;205m"; // magenta
						colors["true"]= "38;2;205;0;205m"; //magenta
						colors["false"]= "38;2;205;0;205m"; //magenta
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

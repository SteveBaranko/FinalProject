#ifndef COLORS_H
#define COLORS_H


#define COUT std::cout
#define UNOR_MAP std::unordered_map
#define STRING std::string
#define ENDL std::endl

#include <unordered_map>
#include <iostream>



class Colors 
{

    private:
        UNOR_MAP<STRING, STRING> colors;


    public:
        Colors(): colors( ) {
            colors["if"]  = "green";
            colors["for"] = "blue";
            colors["while"] = "red";
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

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <cstring>
#include "Image.hpp"
#include "processing.hpp"
#include "Matrix.hpp"
#include <sstream>
using namespace std;
int main(int argc, char *argv[])
{
    if (argc != 5 && argc != 4)
    {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl;

        return 1; // Return a non-zero value to indicate an error
    }
    string inFilename = argv[1];
    string outFilename = argv[2];
    Image *img = new Image;
    ifstream fin;
    fin.open(inFilename.c_str());
    if (!fin.is_open())
    {
        cerr << "Error opening file: " << inFilename << endl;
        delete img;
        return 1;
    }

    Image_init(img, fin);
    int orwidth=img->width;
    int orheight=img->height;
    int desiredWidth = std::stoi(argv[3]);
    int desiredHeight = (argc == 5) ? std::stoi(argv[4]) : orheight;
    fin.close();
    if (desiredWidth<0||desiredWidth>orwidth)
    {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
            << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        delete img;
        return 1;
    }
    if (desiredHeight<0||desiredHeight>orheight)
    {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
            << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        delete img;
        return 1;
    }
    seam_carve(img,desiredWidth,desiredHeight);
    std::ofstream outputFile(outFilename);

    if (!outputFile.is_open()) {
        std::cerr << "Error opening the file: "<<outFilename << std::endl;
        delete img;
        return 1; 
    }

    std::ostream& output = outputFile;
    Image_print(img,output);
    outputFile.close();
    delete img;
    return 0; // Return 0 to indicate successful execution
}

// local includes
#include "Gradient.h"


//-------------------------------------------
// constructor
//-------------------------------------------
Gradient::Gradient(int x_size, int y_size, int noise)
{
    width = x_size;
    height = y_size;
    if (width != 0 || height != 0){
        initMemory();
    }
}

//-------------------------------------------
// allocate memory
//-------------------------------------------
void Gradient::initMemory()
{
    filterX = new int[width];
    filterY = new int[height];
}

//-------------------------------------------
// destructor
//-------------------------------------------
Gradient::~Gradient()
{
    freeMemory();
}


//-------------------------------------------
// free allocated memory
//-------------------------------------------
void Gradient::freeMemory()
{
    if (filterX != 0){
        delete filterX;
        filterX = 0;
    }
    if (filterY != 0){
        delete filterY;
        filterY = 0;
    }
}


//-------------------------------------------
// get histogram entry
//-------------------------------------------
double Gradient::getHistogram(int index)
{
}


//-------------------------------------------
// calculate discrete angle for histogram
//-------------------------------------------
char Gradient::discreteAlpha(double input)
{
}

//-------------------------------------------
// calculate gradient image
//-------------------------------------------
void Gradient::calcGradient(unsigned char *input, int x_size, int y_size, int noise)
{
    if (x_size != width || y_size != height){
        x_size = width;
        y_size = height;
        initMemory();
    }
}

#ifndef BMU_GRADIENT
#define BMU_GRADIENT

// c includes
#include <stdlib.h>     // for malloc()
#include <string.h>     // for memset()
#include <math.h>       // for M_PI

#define HISTOGRAM_BINS  40

using namespace std;

class Gradient
{
private:
    int* filterX;
	int* filterY;
    unsigned char* gradient;
    int noiseThreshold;
    int width;
    int height;
    double histogram[HISTOGRAM_BINS];
    double maxHistogram;

    void initMemory();
    void freeMemory();
    char discreteAlpha(double input);

public:
    Gradient(int x_size = 0, int y_size = 0, int noise = 5);
    ~Gradient();
    void calcGradient(unsigned char *input, int x_size = 0, int y_size = 0, int noise = 5);
    int* getFilterX() { return(filterX); };
    int* getFilterY() { return(filterY); };
    unsigned char* getGradient() { return(gradient); };
    int getHeight() { return(height); };
    int getWidth() { return(width); };
    double getHistogram(int index);
    double getHistogramMax() { return(maxHistogram); };
};

#endif // BMU_GRADIENT

#include "mbed.h"
#include <vector>
#include "Pixel.cpp"

class Object {
private:
    std::vector<Pixel> objPixels;

public:
    Object()
    {
    }

    void translate(int deltaX, int deltaY)
    {
        std::vector<Pixel> oldPixels = objPixels;
        for (std::vector<Pixel>::iterator it = objPixels.begin() ; it != objPixels.end(); ++it)
        {
            (*it).translate(deltaX, deltaY);
        }
    }

    void draw()
    {

    }

    void undraw()
    {

    }

    ~Object()
    {
    }
};

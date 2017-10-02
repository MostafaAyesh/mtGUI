#include "mbed.h"

class Pixel {
private:
	int XCoord;
	int YCoord;
	uint32_t PixelColor;

public:
	Pixel(int X, int Y, uint32_t Color)
	{
		this->XCoord = X;
		this->YCoord = Y;
		this->PixelColor = Color;
	}

	Pixel(int X, int Y)
	{
		this->XCoord = X;
		this->YCoord = Y;
		this->PixelColor = (uint32_t) "0xFF000000";
	}

	int getX()
	{
		return this->XCoord;
	}

	int getY()
	{
		return this->YCoord;
	}

	uint32_t getColor()
	{
		return this->PixelColor;
	}

	void translate(int deltaX, int deltaY)
	{
		this->XCoord += deltaX;
		this->YCoord += deltaY;
	}

	~Pixel()
	{
	}
};

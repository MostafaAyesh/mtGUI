#include "LCD_DISCO_F429ZI.h"
#include "mbed.h"

class Item {
private:
	int width;
	int height;
	int XCoord;
	int YCoord;
	bool Rendered;
	LCD_DISCO_F429ZI *lcd;

public:
	Item(int X, int Y, LCD_DISCO_F429ZI lcd)
	{
		this->XCoord = X;
		this->YCoord = Y;
		this->lcd = &lcd;
		this->width = 50;
		this->height = 50;
	}

	int get_width()
	{
		return this->width;
	}

	int get_height()
	{
		return this->height;
	}

	void render()
	{
		this->Rendered = true;
		lcd->SetTextColor(0xBF00FFFF);
		this->width = 50;
		this->height = 50;
		for (int i = 1; i < 50; i++)
		{

			lcd->FillRect(XCoord, YCoord, i, i);
			wait_ms(2);
		}

	}

	void renderframe(int i)
	{
		lcd->SetTextColor(0xBF00FFFF);
		lcd->FillRect(XCoord, YCoord, i, i);
	}

	bool Clickable(int X, int Y)
	{
		if (X > XCoord & X < (XCoord + width))
		{
			if (Y > YCoord & Y < (YCoord + height))
			{
				return true;
			}
		}
		return false;
	}

	void onClick()
	{
		lcd->SetTextColor(0xBFFF00FF);
		for (int i = 1; i < 50; i++)
		{

			lcd->FillRect(XCoord, YCoord, i, i);
			wait_ms(2);
		}
	}

	void unrender()
	{
		this->Rendered = false;
	}

	~Item()
	{
		if (this->Rendered == true)
		{
			this->unrender();
		}
	}
};

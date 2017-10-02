#include <vector>
#include <Item.cpp>
#include "LCD_DISCO_F429ZI.h"

class View {
private:
	std::vector<Item> ViewItems;
	LCD_DISCO_F429ZI *lcd;

public:
	View(LCD_DISCO_F429ZI lcd)
	{
		this->lcd = &lcd;
		ViewItems.push_back(Item(0,0, lcd));
		ViewItems.push_back(Item(0,50, lcd));
		ViewItems.push_back(Item(0,100, lcd));
		ViewItems.push_back(Item(0,150, lcd));
		ViewItems.push_back(Item(50,0, lcd));
		ViewItems.push_back(Item(50,50, lcd));
		ViewItems.push_back(Item(50,100, lcd));
		ViewItems.push_back(Item(50,150, lcd));
		ViewItems.push_back(Item(100,0, lcd));
		ViewItems.push_back(Item(100,50, lcd));
		ViewItems.push_back(Item(100,100, lcd));
		ViewItems.push_back(Item(100,150, lcd));
		ViewItems.push_back(Item(150,0, lcd));
		ViewItems.push_back(Item(150,50, lcd));
		ViewItems.push_back(Item(150,100, lcd));
		ViewItems.push_back(Item(150,150, lcd));
	}

	void Draw()
	{
		for (int j = 1; j < 50; j++)
		{
			for (int i = 0; i < ViewItems.size(); i++)
			{
				ViewItems[i].renderframe(j);
			}
			wait_ms(2);
		}
	}

	void Touch(int X, int Y)
	{
		for (int i = 0; i < ViewItems.size(); i++)
		{
			if (ViewItems[i].Clickable(X, Y))
			{
				ViewItems[i].onClick();
			}
		}
	}

	~View()
	{

	}
};

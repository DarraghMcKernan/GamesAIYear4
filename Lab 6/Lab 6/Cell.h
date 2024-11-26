#pragma once
#include "globals.h"

class Cell
{
public:
	Cell(int t_cellNum);
	void update();
	void render(sf::RenderWindow& t_window);
	sf::RectangleShape getCellShape();
	int getCellType();
	void setCellType(int t_type);

private:
	int cellNum = 0;
	int type = 0;

	sf::RectangleShape cellShape;
};
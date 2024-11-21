#pragma once
#include "globals.h"

class Cell
{
public:
	Cell(int t_cellNum);
	void update();
	void render(sf::RenderWindow& t_window);
	sf::RectangleShape getCellShape();

private:
	int cellNum = 0;
	sf::RectangleShape cellShape;
};
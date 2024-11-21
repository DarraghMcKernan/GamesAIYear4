#pragma once
#include "globals.h"
#include "Cell.h"

class Grid
{
public:
	void init();
	void update();
	void render(sf::RenderWindow& t_window);

private:
	std::vector<Cell> cells;
	sf::RectangleShape boardWall;
};
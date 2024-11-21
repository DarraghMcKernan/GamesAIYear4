#pragma once
#include "globals.h"
#include "Cell.h"

class Grid
{
public:
	void init();
	void update();
	void render(sf::RenderWindow& t_window);
	sf::Vector2f returnHoveredCellPos(sf::Vector2f t_mousePos);

private:
	std::vector<Cell> cells;
	sf::RectangleShape boardWall;
};
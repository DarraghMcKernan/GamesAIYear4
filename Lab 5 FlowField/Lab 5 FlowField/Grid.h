#pragma once
#include "Cell.h"

class Grid
{
public:
	void init();
	void update();
	void setCells(int t_cellNum, int t_type);
	void render(sf::RenderWindow& t_window);

private:
	int currentCellNum = 0;
	std::vector<Cell> cells;
	sf::Vector2i mousePos;

	int startCellIndex = 0;
	int goalCellIndex = 0;

	int clickCooldown = 0;
};
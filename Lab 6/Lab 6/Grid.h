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
	std::vector<Cell> returnNearbyCellPos();
	void setCellsTo(std::vector<bool> t_cellsUsed,bool t_cathedral,int t_rotation,int t_teamNum);
	std::vector<int> getAllGridCells();

private:
	std::vector<Cell> cells;
	std::vector<int> cellsByType;
	sf::RectangleShape boardWall;
	sf::RectangleShape celllHoveredOver;
	int cellHoveredNumber;
	sf::Vector2f mousePos;
};
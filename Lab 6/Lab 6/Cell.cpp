#include "Cell.h"

Cell::Cell(int t_cellNum):cellNum(t_cellNum)
{
	cellShape.setSize({ CELL_SIZE,CELL_SIZE });
	cellShape.setOrigin({ CELL_SIZE / 2,CELL_SIZE / 2 });
	sf::Vector2f temp = { static_cast<float>(cellNum / GRID_SIZE) * CELL_SIZE,static_cast<float>(cellNum % GRID_SIZE) * CELL_SIZE };
	cellShape.setPosition({ temp.x + (CELL_SIZE),temp.y + (CELL_SIZE) });
	cellShape.setFillColor(sf::Color(100, 100, 100));
	cellShape.setOutlineColor(sf::Color(50, 50, 50));
	cellShape.setOutlineThickness(2);
}

void Cell::update()
{

}

void Cell::render(sf::RenderWindow& t_window)
{
	t_window.draw(cellShape);
}
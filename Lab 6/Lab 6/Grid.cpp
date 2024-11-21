#include "Grid.h"

void Grid::init()
{
	for (int index = 0; index < MAX_CELLS; index++)
	{
		cells.push_back(Cell(index));
	}

	boardWall.setSize({ (CELL_SIZE * MAX_CELLS / 10) + CELL_SIZE -10, (CELL_SIZE * MAX_CELLS / 10) + CELL_SIZE -10});
	boardWall.setPosition({ 5,5 });
	boardWall.setFillColor(sf::Color(80, 40, 15));
	boardWall.setOutlineThickness(5);
	boardWall.setOutlineColor(sf::Color(50, 50, 50));
}

void Grid::update()
{

}

void Grid::render(sf::RenderWindow& t_window)
{
	t_window.draw(boardWall);
	for (int index = 0; index < MAX_CELLS; index++)
	{
		cells[index].render(t_window);
	}
}

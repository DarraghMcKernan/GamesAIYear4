#include "Grid.h"

void Grid::init()
{
	for (int index = 0; index < MAX_CELLS; index++)
	{
		cells.push_back(Cell(index));
	}
}

void Grid::update()
{

}

void Grid::render(sf::RenderWindow& t_window)
{
	for (int index = 0; index < MAX_CELLS; index++)
	{
		cells[index].render(t_window);
	}
}

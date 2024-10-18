#include "Grid.h"

void Grid::init()
{
	Cell newCell;
	for (int index = 0; index < 50*50; index++)
	{
		cells.push_back(newCell);
		cells[index].init(index, 0, { (index % 50) * CELL_SIZE,(index / 50) * CELL_SIZE });
	}
}

void Grid::update()
{
	if (clickCooldown > 0)
	{
		clickCooldown--;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickCooldown <= 0)
	{
		setCells(startCellIndex, 0);
		startCellIndex = (mousePos.x / 20) + ((mousePos.y / 20) * 50);
		std::cout << startCellIndex << "\n";
		setCells(startCellIndex, 1);
		clickCooldown = 30;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && clickCooldown <= 0)
	{
		setCells(goalCellIndex, 0);
		goalCellIndex = (mousePos.x / 20) + ((mousePos.y / 20) * 50);
		std::cout << goalCellIndex << "\n";
		setCells(goalCellIndex, 2);
		clickCooldown = 30;
	}
}

void Grid::setCells(int t_cellNum, int t_type)
{
	cells[t_cellNum].setType(t_type);
}

void Grid::render(sf::RenderWindow& t_window)
{
	mousePos = sf::Mouse::getPosition(t_window);

	for (int index = 0; index < 50*50; index++)
	{
		cells[index].render(t_window);
	}
}

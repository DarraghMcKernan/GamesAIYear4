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
	t_window.draw(boardWall);
	for (int index = 0; index < MAX_CELLS; index++)
	{
		cells[index].render(t_window);
	}
}

sf::Vector2f Grid::returnHoveredCellPos(sf::Vector2f t_mousePos)
{
	mousePos = t_mousePos;

	for (int index = 0; index < MAX_CELLS; index++)
	{
		if (cells[index].getCellShape().getGlobalBounds().contains(mousePos) && cells[index].getCellType() != 1)
		{
			cellHoveredNumber = index;
			return cells[index].getCellShape().getPosition();
		}
	}
	return sf::Vector2f(-1000,-1000);
}

std::vector<Cell> Grid::returnNearbyCellPos()
{
	std::vector<Cell> nearbyCells;

	nearbyCells.push_back(cells[cellHoveredNumber - GRID_SIZE -1]);
	nearbyCells.push_back(cells[cellHoveredNumber - GRID_SIZE]);
	nearbyCells.push_back(cells[cellHoveredNumber - GRID_SIZE+1]);
	
	nearbyCells.push_back(cells[cellHoveredNumber -1]);
	nearbyCells.push_back(cells[cellHoveredNumber]);
	nearbyCells.push_back(cells[cellHoveredNumber+1]);
	
	nearbyCells.push_back(cells[cellHoveredNumber + GRID_SIZE-1]);
	nearbyCells.push_back(cells[cellHoveredNumber+ GRID_SIZE]);
	nearbyCells.push_back(cells[cellHoveredNumber+GRID_SIZE+1]);
	
	return nearbyCells;
}

void Grid::setCellsTo(std::vector<bool> t_cellsUsed)
{
	for (int row = -1; row < 1; row++)
	{
		for (int col = -1; col < 1; col++)
		{
			cells[row * (col * GRID_SIZE)].setCellType(1);
		}
	}
}
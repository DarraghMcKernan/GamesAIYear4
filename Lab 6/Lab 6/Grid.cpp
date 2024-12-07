#include "Grid.h"

void Grid::init()
{
	for (int index = 0; index < MAX_CELLS; index++)
	{
		cells.push_back(Cell(index));
	}
	for (int index = 0; index < MAX_CELLS; index++)
	{
		cellsByType.push_back(cells[index].getCellType());//store the list of types for the ai to use
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

void Grid::setCellsTo(std::vector<bool> t_cellsUsed, bool t_cathedral, int t_rotation,int t_teamNum)
{
	for (int index = 0; index < t_cellsUsed.size(); index++)
	{
		if (t_cellsUsed[index] == true)
		{
			int offset = (((index / 3) - 1) * GRID_SIZE) + ((index % 3) - 1);

			int currentCell = cellHoveredNumber + offset;

			if (t_cathedral == false || index != 0)
			{
				cells[currentCell].setCellType(t_teamNum);
				cellsByType[currentCell] = t_teamNum;
			}

			if (t_cathedral == true && index == 1 && t_rotation == 0)
			{//the last piece will be 1 out from the rotation corner
				/*std::cout << currentCell << "\n";
				std::cout << currentCell - GRID_SIZE << "\n";*/
				cells[currentCell - GRID_SIZE].setCellType(1);
				cellsByType[currentCell - GRID_SIZE] = t_teamNum;
			}
			else if (t_cathedral == true && index == 5 && t_rotation == 1)
			{
				cells[currentCell + 1].setCellType(t_teamNum);
				cellsByType[currentCell +1] = t_teamNum;
			}
			else if (t_cathedral == true && index == 7 && t_rotation == 2)
			{
				cells[currentCell + GRID_SIZE].setCellType(t_teamNum);
				cellsByType[currentCell + GRID_SIZE] = t_teamNum;
			}
			else if (t_cathedral == true && index == 3 && t_rotation == 3)
			{
				cells[currentCell - 1].setCellType(t_teamNum);
				cellsByType[currentCell - 1] = t_teamNum;
			}
		}
	}

	/*for (int row = -1; row < 1; row++)
	{
		for (int col = -1; col < 1; col++)
		{
			if (t_cellsUsed[(row + 1) * (col + 1)] == true)
			{
				cells[cellHoveredNumber + (row * (col * GRID_SIZE))].setCellType(1);
			}
		}
	}*/
}

std::vector<int> Grid::getAllGridCells()
{
	return cellsByType;
}

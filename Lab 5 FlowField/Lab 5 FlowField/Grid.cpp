#include "Grid.h"

void Grid::init()
{
	if (!font.loadFromFile("ASSETS/BebasNeue.otf"))
	{
		std::cout << "\nfont failed to load";
	}
	Cell newCell;
	int gridW = GRID_WIDTH;
	for (int index = 0; index < GRID_WIDTH * GRID_WIDTH; index++)
	{
		cells.push_back(newCell);
		cells[index].init(index, 0, { (index % gridW) * CELL_SIZE,(index / gridW) * CELL_SIZE }, font);
		//cells[index].setType(0);
	}
}

void Grid::update()
{
	if (clickCooldown > 0)
	{
		clickCooldown--;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && clickCooldown <= 0)//nothing displaying on cells
	{
		renderChoice = 0;
		clickCooldown = 10;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && clickCooldown <= 0)//weights display on cells
	{
		renderChoice = 1;
		clickCooldown = 10;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && clickCooldown <= 0)//integration field displays on cells
	{
		renderChoice = 2;
		clickCooldown = 10;
	}

	if (newWallTimer > 0)
	{
		if (newWallTimer == 1)
		{
			newWallGenerated = true;
		}
		newWallTimer--;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickCooldown <= 0)//set start
	{
		startSet = true;
		setCells(startCellIndex, 0);
		startCellIndex = (mousePos.x / CELL_SIZE_INT) + ((mousePos.y / CELL_SIZE_INT) * GRID_WIDTH);
		//std::cout << startCellIndex << "\n";
		setCells(startCellIndex, 1);

		if (goalSet = true)
		{
			drawPathToCheapest();
		}

		clickCooldown = 10;
		//clearPreviousPath();
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && clickCooldown <= 0)//set goal
	{
		goalSet = true;
		setCells(goalCellIndex, 0);
		goalCellIndex = (mousePos.x / CELL_SIZE_INT) + ((mousePos.y / CELL_SIZE_INT) * GRID_WIDTH);
		//std::cout << goalCellIndex << "\n";
		//setCells(goalCellIndex, 2);
		clickCooldown = 10;

		generateIntegrationField();

		cellCostsGenerated = false;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) != true))//create wall
	{
		wallCellIndex = (mousePos.x / CELL_SIZE_INT) + ((mousePos.y / CELL_SIZE_INT) * GRID_WIDTH);
		//std::cout << wallCellIndex << "\n";
		if (cells[wallCellIndex].getType() == 0 || cells[wallCellIndex].getType() == 4)
		{
			setCells(wallCellIndex, 3);
		}
		newWallTimer = 30;
		cellCostsGenerated = false;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))//remove wall
	{
		wallCellIndex = (mousePos.x / CELL_SIZE_INT) + ((mousePos.y / CELL_SIZE_INT) * GRID_WIDTH);
		//std::cout << wallCellIndex << "\n";
		if (cells[wallCellIndex].getType() == 3)
		{
			setCells(wallCellIndex, 0);
			cells[wallCellIndex].setCost(MAX_COST);
		}
		newWallTimer = 30;
		cellCostsGenerated = false;
	}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && clickCooldown <= 0 && goalSet == true && startSet == true)//integration field displays on cells
	//{
	//	drawPathToCheapest();
	//	clickCooldown = 10;
	//}

	if (newWallGenerated == true)//regenerate if a wall is created
	{
		newWallGenerated = false;
		generateIntegrationField();
	}
}

void Grid::setCells(int t_cellNum, int t_type)
{
	cells[t_cellNum].setType(t_type);
}

void Grid::render(sf::RenderWindow& t_window)
{
	mousePos = sf::Mouse::getPosition(t_window);

	for (int index = 0; index < GRID_WIDTH * GRID_WIDTH; index++)
	{
		cells[index].render(t_window, renderChoice);
	}
}

void Grid::generateIntegrationField()
{
	for (int i = 0; i < cells.size(); i++)
	{
		if (cells[i].getCost() != WALL_COST)
		{
			cells[i].setType(0);
			cells[i].setCost(MAX_COST);
		}
	}

	startSet = false;

	std::queue<int> cellQueue;
	cellQueue.push(goalCellIndex);//start at the goal and work outwards
	setCells(goalCellIndex, 2);
	int gridW = GRID_WIDTH;
	while (!cellQueue.empty())
	{
		int currentIndex = cellQueue.front();
		cellQueue.pop();

		int currentCost = cells[currentIndex].getCost();
		int row = currentIndex / gridW;
		int col = currentIndex % gridW;

		//scuffed way of getting the positons of the immediate surrounding cells
		std::vector<int> neighborCellNum = { currentIndex - gridW,currentIndex + gridW,currentIndex - 1,currentIndex + 1 };

		for (int neighborIndex : neighborCellNum)
		{
			int neighborRow = neighborIndex / gridW;//get the row of the neighbour we are looking at
			int neighborCol = neighborIndex % gridW;

			if (neighborIndex >= 0 && neighborIndex < cells.size() && abs(neighborRow - row) <= 1 && abs(neighborCol - col) <= 1)//prevent from going out of bounds and causing an exception error also prevents going from left to right
			{
				if (cells[neighborIndex].getCost() != WALL_COST && cells[neighborIndex].getCost() > currentCost + CELL_SIZE_INT)//make sure it isnt a value less than itself as that shows it hasnt been explored yet
				{
					cells[neighborIndex].setCost(currentCost + CELL_SIZE_INT);//cells are 20 so the distance is 20
					cellQueue.push(neighborIndex);//put the cell we just found back into the queue so we can look at its neighours next
				}
			}
		}

		std::vector<int> neighborCellNumDiagonal = { currentIndex - gridW - 1,currentIndex - gridW + 1,currentIndex + gridW - 1,currentIndex + gridW + 1 };

		for (int neighborIndex : neighborCellNumDiagonal)
		{
			int neighborRow = neighborIndex / gridW;//get the row of the neighbour we are looking at
			int neighborCol = neighborIndex % gridW;

			if (neighborIndex >= 0 && neighborIndex < cells.size() && abs(neighborRow - row) <= 1 && abs(neighborCol - col) <= 1)//prevent from going out of bounds and causing an exception error
			{
				if (cells[neighborIndex].getCost() != WALL_COST && cells[neighborIndex].getCost() > currentCost + CELL_SIZE_INT * 1.5 && preventDiagonalLeaking(neighborIndex, currentIndex) == true)//make sure it isnt a value less than itself as that shows it hasnt been explored yet
				{
					cells[neighborIndex].setCost(currentCost + CELL_SIZE_INT * 1.5);//diagonal cost is 30
					cellQueue.push(neighborIndex);//put the cell we just found back into the queue so we can look at its neighours next
				}
			}
		}
	}
	cellCostsGenerated = true;

	generateFlowField();
}

void Grid::generateFlowField()
{
	int gridW = GRID_WIDTH;
	for (int index = 0; index < cells.size(); index++)//go through all cells and check their neighbours, then point to the lowest cost one
	{
		if (cells[index].getCost() != WALL_COST)//dont check walls
		{
			int cheapest = cells[index].getCost();//must be cheaper than iself
			int cheapestIndex = index;
			int row = index / gridW;
			int col = index % gridW;

			std::vector<int> neighborCellNum = { index - gridW,index + gridW,index - 1,index + 1,index - gridW - 1,index - gridW + 1,index + gridW - 1,index + gridW + 1 };//used to check all neighbours surrounding the cell

			for (int neighborIndex : neighborCellNum)
			{
				int neighborRow = neighborIndex / gridW;
				int neighborCol = neighborIndex % gridW;

				if (neighborIndex >= 0 && neighborIndex < cells.size() && abs(neighborRow - row) <= 1 && abs(neighborCol - col) <= 1)//prevent from going out of bounds and causing an exception error
				{
					if (cells[neighborIndex].getCost() < cheapest)//if its cheaper than other neighbours
					{
						cheapest = cells[neighborIndex].getCost();
						cheapestIndex = neighborIndex;//which cell is the cheapest
					}
				}
			}
			cells[index].setCheapestNeighbour(cheapestIndex);//need to prevent the cheapest neighbour pointing to diagonals if sides are obstructed
		}
	}
}

void Grid::drawPathToCheapest()
{
	clearPreviousPath();

	int current = cells[startCellIndex].getCheapestNeighbour();
	cheapestPath.push_back(startCellIndex);
	int bombOut = 0;

	if (cells[current].getCost() != MAX_COST)//cant start on a cell without a value attached to prevent endlessly searching where there is no paths
	{
		while (current != goalCellIndex)
		{
			bombOut++;
			cheapestPath.push_back(current);//store cheapest path 
			cells[current].setType(4);
			current = cells[current].getCheapestNeighbour();
			if (bombOut == 10000)//i shoudlnt need this i dont think but just in case
			{
				continue;
			}
		}
	}
}

void Grid::clearPreviousPath()
{
	if (cheapestPath.size() != 0)
	{
		for (int index = 0; index < cheapestPath.size(); index++)
		{
			cells[cheapestPath.at(index)].setType(0);//default
		}
	}

	cheapestPath.clear();
}

bool Grid::preventDiagonalLeaking(int t_neighbour, int t_index)
{
	int gridW = GRID_WIDTH;
	std::vector<int> neighborCellNumDiagonal = { t_index - gridW - 1,t_index - gridW + 1,t_index + gridW - 1,t_index + gridW + 1 };

	bool canMoveDiagonally = false;//this is so bad, i should have gone to bed hours ago :D
	if (t_neighbour == neighborCellNumDiagonal[0] && cells[t_index - gridW].getCost() != WALL_COST && cells[t_index - 1].getCost() != WALL_COST)//get top left cell and make sure the cells up and to the left are not walls otherwise its impassable
	{
		canMoveDiagonally = true;
	}
	else if (t_neighbour == neighborCellNumDiagonal[1] && cells[t_index - gridW].getCost() != WALL_COST && cells[t_index + 1].getCost() != WALL_COST)
	{
		canMoveDiagonally = true;
	}
	else if (t_neighbour == neighborCellNumDiagonal[2] && cells[t_index + gridW].getCost() != WALL_COST && cells[t_index - 1].getCost() != WALL_COST)
	{
		canMoveDiagonally = true;
	}
	else if (t_neighbour == neighborCellNumDiagonal[3] && cells[t_index + gridW].getCost() != WALL_COST && cells[t_index + 1].getCost() != WALL_COST)
	{
		canMoveDiagonally = true;
	}

	return canMoveDiagonally;
}

#include "Grid.h"

void Grid::init()
{
	if (!font.loadFromFile("ASSETS/BebasNeue.otf"))
	{
		std::cout << "\nfont failed to load";
	}
	Cell newCell;
	for (int index = 0; index < 50*50; index++)
	{
		cells.push_back(newCell);
		cells[index].init(index, 0, { (index % 50) * CELL_SIZE,(index / 50) * CELL_SIZE },font);
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
		startCellIndex = (mousePos.x / 20) + ((mousePos.y / 20) * 50);
		//std::cout << startCellIndex << "\n";
		setCells(startCellIndex, 1);
		
		if (goalSet = true)
		{
			drawPathToCheapest();
		}

		clickCooldown =10;
		//clearPreviousPath();
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && clickCooldown <= 0)//set goal
	{
		goalSet = true;
		setCells(goalCellIndex, 0);
		goalCellIndex = (mousePos.x / 20) + ((mousePos.y / 20) * 50);
		//std::cout << goalCellIndex << "\n";
		//setCells(goalCellIndex, 2);
		clickCooldown = 10;

		generateIntegrationField();

		cellCostsGenerated = false;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) != true))//create wall
	{
		wallCellIndex = (mousePos.x / 20) + ((mousePos.y / 20) * 50);
		//std::cout << wallCellIndex << "\n";
		if (cells[wallCellIndex].getType() == 0 || cells[wallCellIndex].getType() == 4)
		{
			setCells(wallCellIndex, 3);
		}
		newWallTimer = 30;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))//remove wall
	{
		wallCellIndex = (mousePos.x / 20) + ((mousePos.y / 20) * 50);
		//std::cout << wallCellIndex << "\n";
		if (cells[wallCellIndex].getType() == 3)
		{
			setCells(wallCellIndex, 0);
			cells[wallCellIndex].setCost(9999);
		}
		newWallTimer = 30;
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

	for (int index = 0; index < 50*50; index++)
	{
		cells[index].render(t_window,renderChoice);
	}
}

void Grid::generateIntegrationField()
{
	for(int i = 0; i < cells.size(); i++)
	{
		if(cells[i].getCost() != 999)
		{
			cells[i].setType(0);
			cells[i].setCost(9999);
		}
	}

	startSet = false;

	std::queue<int> cellQueue;
	cellQueue.push(goalCellIndex);//start at the goal and work outwards
	setCells(goalCellIndex, 2);

	while(!cellQueue.empty())
	{
		int currentIndex = cellQueue.front();
		cellQueue.pop();

		int currentCost = cells[currentIndex].getCost();
		int row = currentIndex / 50;
		int col = currentIndex % 50;

		//scuffed way of getting the positons of the immediate surrounding cells
		std::vector<int> neighborCellNum = {currentIndex - 50,currentIndex + 50,currentIndex - 1,currentIndex + 1};

		for(int neighborIndex : neighborCellNum)
		{
			int neighborRow = neighborIndex / 50;//get the row of the neighbour we are looking at
			int neighborCol = neighborIndex % 50;

			if (neighborIndex >= 0 && neighborIndex < cells.size() && abs(neighborRow - row) <= 1 && abs(neighborCol - col) <= 1)//prevent from going out of bounds and causing an exception error also prevents going from left to right
			{
				if(cells[neighborIndex].getCost() != 999 && cells[neighborIndex].getCost() > currentCost + 20)//make sure it isnt a value less than itself as that shows it hasnt been explored yet
				{
					cells[neighborIndex].setCost(currentCost + 20);//cells are 20 so the distance is 20
					cellQueue.push(neighborIndex);//put the cell we just found back into the queue so we can look at its neighours next
				}
			}
		}

		std::vector<int> neighborCellNumDiagonal = {currentIndex - 50 - 1,currentIndex - 50 + 1,currentIndex + 50 - 1,currentIndex + 50 + 1};

		for(int neighborIndex : neighborCellNumDiagonal)
		{
			int neighborRow = neighborIndex / 50;//get the row of the neighbour we are looking at
			int neighborCol = neighborIndex % 50;

			if (neighborIndex >= 0 && neighborIndex < cells.size() && abs(neighborRow - row) <= 1 && abs(neighborCol - col) <= 1)//prevent from going out of bounds and causing an exception error
			{
				if(cells[neighborIndex].getCost() != 999 && cells[neighborIndex].getCost() > currentCost + 30 && preventDiagonalLeaking(neighborIndex,currentIndex) == true)//make sure it isnt a value less than itself as that shows it hasnt been explored yet
				{
					cells[neighborIndex].setCost(currentCost + 30);//diagonal cost is 30
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
	for (int index = 0; index < cells.size(); index++)//go through all cells and check their neighbours, then point to the lowest cost one
	{
		if (cells[index].getCost() != 999)//dont check walls
		{
			int cheapest = cells[index].getCost();//must be cheaper than iself
			int cheapestIndex = index;
			int row = index / 50;
			int col = index % 50;

			std::vector<int> neighborCellNum = { index - 50,index + 50,index - 1,index + 1,index - 50 - 1,index - 50 + 1,index + 50 - 1,index + 50 + 1 };//used to check all neighbours surrounding the cell

			for (int neighborIndex : neighborCellNum)
			{
				int neighborRow = neighborIndex / 50;
				int neighborCol = neighborIndex % 50;

				if (neighborIndex >= 0 && neighborIndex < cells.size() && abs(neighborRow - row) <= 1 && abs(neighborCol - col) <= 1)//prevent from going out of bounds and causing an exception error
				{
					if (cells[neighborIndex].getCost() < cheapest)//if its cheaper than other neighbours
					{
						cheapest = cells[neighborIndex].getCost();
						cheapestIndex = neighborIndex;//which cell is the cheapest
					}
				}
			}
			cells[index].setCheapestNeighbour(cheapestIndex);
		}
	}
}

void Grid::drawPathToCheapest()
{
	clearPreviousPath();

	int current = cells[startCellIndex].getCheapestNeighbour();
	cheapestPath.push_back(startCellIndex);
	
	while (current != goalCellIndex)
	{
		cheapestPath.push_back(current);//store cheapest path 
		cells[current].setType(4);
		current = cells[current].getCheapestNeighbour();
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

bool Grid::preventDiagonalLeaking(int t_neighbour ,int t_index)
{
	std::vector<int> neighborCellNumDiagonal = { t_index - 50 - 1,t_index - 50 + 1,t_index + 50 - 1,t_index + 50 + 1 };

	bool canMoveDiagonally = false;//this is so bad, i should have gone to bed hours ago :D
	if (t_neighbour == neighborCellNumDiagonal[0] && cells[t_index - 50].getCost() != 999 && cells[t_index - 1].getCost() != 999)//get top left cell and make sure the cells up and to the left are not walls otherwise its impassable
	{
		canMoveDiagonally = true;
	}
	else if (t_neighbour == neighborCellNumDiagonal[1] && cells[t_index - 50].getCost() != 999 && cells[t_index + 1].getCost() != 999)
	{
		canMoveDiagonally = true;
	}
	else if (t_neighbour == neighborCellNumDiagonal[2] && cells[t_index + 50].getCost() != 999 && cells[t_index - 1].getCost() != 999)
	{
		canMoveDiagonally = true;
	}
	else if (t_neighbour == neighborCellNumDiagonal[3] && cells[t_index + 50].getCost() != 999 && cells[t_index + 1].getCost() != 999)
	{
		canMoveDiagonally = true;
	}

	return canMoveDiagonally;
}

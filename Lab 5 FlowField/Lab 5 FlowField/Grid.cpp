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
		clickCooldown = 30;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && clickCooldown <= 0)//weights display on cells
	{
		renderChoice = 1;
		clickCooldown = 30;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && clickCooldown <= 0)//integration field displays on cells
	{
		renderChoice = 2;
		clickCooldown = 30;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickCooldown <= 0)//set start
	{
		startSet = true;
		//setCells(startCellIndex, 0);
		startCellIndex = (mousePos.x / 20) + ((mousePos.y / 20) * 50);
		//std::cout << startCellIndex << "\n";
		//setCells(startCellIndex, 1);
		if (cellCostsGenerated == true)
		{
			
		}
		clickCooldown = 30;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && clickCooldown <= 0)//set goal
	{
		goalSet = true;
		setCells(goalCellIndex, 0);
		goalCellIndex = (mousePos.x / 20) + ((mousePos.y / 20) * 50);
		//std::cout << goalCellIndex << "\n";
		//setCells(goalCellIndex, 2);
		clickCooldown = 30;

		generateIntegrationField();

		cellCostsGenerated = false;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) != true))//create wall
	{
		wallCellIndex = (mousePos.x / 20) + ((mousePos.y / 20) * 50);
		//std::cout << wallCellIndex << "\n";
		if (cells[wallCellIndex].getType() == 0)
		{
			setCells(wallCellIndex, 3);
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))//remove wall
	{
		wallCellIndex = (mousePos.x / 20) + ((mousePos.y / 20) * 50);
		std::cout << wallCellIndex << "\n";
		if (cells[wallCellIndex].getType() == 3)
		{
			setCells(wallCellIndex, 0);
		}
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
			cells[i].setCost(9999);
		}
	}

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

			if(neighborIndex >= 0 && neighborIndex < cells.size())//prevent from going out of bounds and causing an exception error
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

			if(neighborIndex >= 0 && neighborIndex < cells.size())//prevent from going out of bounds and causing an exception error
			{
				if(cells[neighborIndex].getCost() != 999 && cells[neighborIndex].getCost() > currentCost + 30)//make sure it isnt a value less than itself as that shows it hasnt been explored yet
				{
					cells[neighborIndex].setCost(currentCost + 30);//diagonal cost is 30
					cellQueue.push(neighborIndex);//put the cell we just found back into the queue so we can look at its neighours next
				}
			}
		}
	}
	cellCostsGenerated = true;
}

void Grid::generateFlowField()
{

}
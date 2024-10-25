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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickCooldown <= 0)//set start
	{
		startSet = true;
		setCells(startCellIndex, 0);
		startCellIndex = (mousePos.x / 20) + ((mousePos.y / 20) * 50);
		//std::cout << startCellIndex << "\n";
		setCells(startCellIndex, 1);
		clickCooldown = 30;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && clickCooldown <= 0)//set goal
	{
		goalSet = true;
		setCells(goalCellIndex, 0);
		goalCellIndex = (mousePos.x / 20) + ((mousePos.y / 20) * 50);
		//std::cout << goalCellIndex << "\n";
		setCells(goalCellIndex, 2);
		clickCooldown = 30;
		if (startSet == true)
		{
			assignCellCosts();
		}
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
	if (goalSet == true && startSet == true)
	{
		//goalSet = false;
		//startSet = false;

		assignCellCosts();
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

void Grid::assignCellCosts()
{
	int targetX = goalCellIndex % 50;
	int targetY = goalCellIndex / 50;
	//std::cout << "Target X: " + std::to_string(targetX*50) + "   Target Y: " + std::to_string(targetY*20) + "\n";

	for (int row = 0; row < 50; row++)
	{
		for (int column = 0; column < 50; column++)
		{
			int index = (row * 50) + column;
			float distance = std::sqrt(std::pow(targetX - column, 2) + std::pow(targetY - row, 2));

			if (cells[index].getCost() != 999 && index != goalCellIndex && index != startCellIndex)
			{
				cells[index].setCost(distance);
			}
		}
	}
}
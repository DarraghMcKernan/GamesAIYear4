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
		std::cout << startCellIndex << "\n";
		setCells(startCellIndex, 1);
		clickCooldown = 30;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && clickCooldown <= 0)//set goal
	{
		goalSet = true;
		setCells(goalCellIndex, 0);
		goalCellIndex = (mousePos.x / 20) + ((mousePos.y / 20) * 50);
		std::cout << goalCellIndex << "\n";
		setCells(goalCellIndex, 2);
		clickCooldown = 30;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) != true))//create wall
	{
		wallCellIndex = (mousePos.x / 20) + ((mousePos.y / 20) * 50);
		std::cout << wallCellIndex << "\n";
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
		goalSet = false;
		startSet = false;

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
	//cells[goalCellIndex].setCost(0);
	for (int index = 0; index < 50*50; index++)
	{
		int topCell = goalCellIndex - 50;
		int bottomCell = goalCellIndex + 50;
		int leftCell = goalCellIndex - 1;
		int rightCell = goalCellIndex + 1;

		cells[topCell].setCost(1);
		cells[topCell-1].setCost(1);
		cells[topCell+1].setCost(1);

		cells[bottomCell].setCost(1);
		cells[bottomCell-1].setCost(1);
		cells[bottomCell+1].setCost(1);

		cells[leftCell].setCost(1);
		cells[rightCell].setCost(1);
	}
}
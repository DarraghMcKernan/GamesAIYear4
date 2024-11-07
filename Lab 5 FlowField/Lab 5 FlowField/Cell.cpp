#include "Cell.h"

void Cell::init(int t_cellNum, int t_cellType, sf::Vector2f t_position, sf::Font& t_font)
{
	cellNumber = t_cellNum;
	typeOfCell = t_cellType;

	cellShape.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	cellShape.setFillColor(sf::Color(50, 50, 50));
	cellShape.setOutlineColor(sf::Color::Black);
	cellShape.setOutlineThickness(2.0f);
	cellShape.setPosition(t_position);

	arrowShape.setSize(sf::Vector2f(15, 2));
	arrowShape.setFillColor(sf::Color(250, 250, 250));
	arrowShape.setOrigin({2,1});
	arrowShape.setPosition({ t_position .x+CELL_SIZE/2,t_position .y+CELL_SIZE/2});

	weightText.setFont(t_font);
	weightText.setCharacterSize(16.0f);
	weightText.setPosition({ t_position.x,t_position.y});
}

void Cell::setType(int t_cellType)
{
	typeOfCell = t_cellType;
	if (typeOfCell == 0)//default cell
	{
		//cellShape.setFillColor(sf::Color(50, 50, 50));
		setCost(cost);
	}
	else if (typeOfCell == 1)//start
	{
		cellShape.setFillColor(sf::Color::Green);
	}
	else if (typeOfCell == 2)//goal
	{
		cellShape.setFillColor(sf::Color::Red);
		setCost(0);
	}
	else if (typeOfCell == 3)//wall
	{
		cellShape.setFillColor(sf::Color::Black);
		setCost(999);
	}
	else if (typeOfCell == 4)//path
	{
		cellShape.setFillColor(sf::Color(175, 175, 0));
	}

	weightText.setString(std::to_string(cost));
}

int Cell::getType()
{
	return typeOfCell;
}

void Cell::setCost(int t_cost)
{
	cost = t_cost;
	weightText.setString(std::to_string(cost));

	if (cost == 999)
	{
		cellShape.setFillColor(sf::Color::White);
	}
	else if (cost != 0)
	{
		int colour = 255 - (cost/5);
		if (colour < 0)
		{
			colour = 0;
		}
		cellShape.setFillColor(sf::Color(0, colour, colour));
	}
	else cellShape.setFillColor(sf::Color::Red);
}

int Cell::getCost()
{
	return cost;
}

void Cell::setCheapestNeighbour(int t_cheapest)
{
	cheapesNeighbour = t_cheapest;
	//startCellIndex = (mousePos.x / 20) + ((mousePos.y / 20) * 50);
	sf::Vector2f cheapestPos = { (t_cheapest % 50) * 20.0f,(t_cheapest / 50) * 20.0f };

	sf::Vector2f direction = cheapestPos - cellShape.getPosition();
	float angle = std::atan2(direction.y, direction.x);
	angle = angle * 180 / 3.14159265f;

	arrowShape.setRotation(angle);
}

int Cell::getCheapestNeighbour()
{
	return cheapesNeighbour;
}

void Cell::render(sf::RenderWindow& t_window, int t_renderChoice)
{
	t_window.draw(cellShape);
	if (t_renderChoice == 1)
	{
		t_window.draw(weightText);
	}
	else if (t_renderChoice == 2)
	{
		t_window.draw(arrowShape);
	}
}
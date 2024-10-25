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
	arrowShape.setOrigin({2,2});
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
		cellShape.setFillColor(sf::Color(50, 50, 50));
		setCost(0);
	}
	else if (typeOfCell == 1)//start
	{
		cellShape.setFillColor(sf::Color::Green);
	}
	else if (typeOfCell == 2)//end
	{
		cellShape.setFillColor(sf::Color::Red);
		setCost(0);
	}
	else if (typeOfCell == 3)//wall
	{
		cellShape.setFillColor(sf::Color::Black);
		setCost(999);
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
	if (cost != 0)
	{
		int colour = cost * 4;
		if (colour > 255)
		{
			colour = 255;
		}
		cellShape.setFillColor(sf::Color(colour, colour, colour));
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
	sf::Vector2f cheapestPos = { (t_cheapest % 50) * 20.0f,(t_cheapest / 50.0f) * 20.0f };

	sf::Vector2f direction = cheapestPos - cellShape.getPosition();
	float angle = std::atan2(direction.y, direction.x);
	angle = angle * 180 / 3.14159265f;

	arrowShape.setRotation(angle);
}

void Cell::render(sf::RenderWindow& t_window)
{
	t_window.draw(cellShape);
	//t_window.draw(weightText);
	t_window.draw(arrowShape);
}
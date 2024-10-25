#include "Cell.h"

void Cell::init(int t_cellNum, int t_cellType, sf::Vector2f t_position, sf::Font& t_font)
{
	cellNumber = t_cellNum;
	typeOfCell = t_cellType;

	cellShape.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	cellShape.setFillColor(sf::Color(50, 50, 200));
	cellShape.setOutlineColor(sf::Color::Black);
	cellShape.setOutlineThickness(2.0f);
	cellShape.setPosition(t_position);

	weightText.setFont(t_font);
	weightText.setCharacterSize(16.0f);
	weightText.setPosition({ t_position.x,t_position.y});
}

void Cell::setType(int t_cellType)
{
	typeOfCell = t_cellType;
	if (typeOfCell == 0)//default cell
	{
		cellShape.setFillColor(sf::Color(50, 50, 200));
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
}

void Cell::setVectors(int t_vectors)
{
	vectors = t_vectors;
}

void Cell::render(sf::RenderWindow& t_window)
{
	t_window.draw(cellShape);
	t_window.draw(weightText);
}
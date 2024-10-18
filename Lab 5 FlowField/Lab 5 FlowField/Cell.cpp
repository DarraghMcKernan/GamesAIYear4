#include "Cell.h"

void Cell::init(int t_cellNum, int t_cellType, sf::Vector2f t_position)
{
	cellNumber = t_cellNum;
	typeOfCell = t_cellType;

	cellShape.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	cellShape.setFillColor(sf::Color::Blue);
	cellShape.setOutlineColor(sf::Color::Black);
	cellShape.setOutlineThickness(2.0f);
	cellShape.setPosition(t_position);
}

void Cell::setType(int t_cellType)
{
	typeOfCell = t_cellType;
	if (typeOfCell == 0)//default cell
	{
		cellShape.setFillColor(sf::Color::Blue);
	}
	else if (typeOfCell == 1)//start
	{
		cellShape.setFillColor(sf::Color::Green);
	}
	else if (typeOfCell == 2)//end
	{
		cellShape.setFillColor(sf::Color::Red);
	}
}

void Cell::setCost(int t_cost)
{
	cost = t_cost;
}

void Cell::setVectors(int t_vectors)
{
	vectors = t_vectors;
}

void Cell::render(sf::RenderWindow& t_window)
{
	t_window.draw(cellShape);
}

#pragma once
#include "globals.h"

class Cell
{
public:
	void init(int t_cellNum,int t_cellType,sf::Vector2f t_position, sf::Font& t_font);
	void setType(int t_cellType);
	int getType();
	void setCost(int t_cost);
	int getCost();
	void setCheapestNeighbour(int t_cheapest);
	void render(sf::RenderWindow& t_window);
private:
	int cellNumber = 0;
	int cost = 0;
	int cheapesNeighbour = 0;
	int typeOfCell = 0;
	sf::RectangleShape cellShape;
	sf::RectangleShape arrowShape;
	sf::Font font;
	sf::Text weightText;
	bool renderCost = true;
};
#pragma once
#include "globals.h"

class Cell
{
public:
	void init(int t_cellNum,int t_cellType,sf::Vector2f t_position);
	void setType(int t_cellType);
	void setCost(int t_cost);
	void setVectors(int t_vectors);
	void render(sf::RenderWindow& t_window);

private:
	int cellNumber = 0;
	int cost = 0;
	int vectors = 0;
	int typeOfCell = 0;
	sf::RectangleShape cellShape;

};
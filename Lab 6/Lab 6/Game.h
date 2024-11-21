#pragma once
#include "globals.h"
#include "Grid.h"
#include "GameShapes.h"

class Game
{
public:
	void init();
	void update();
	void render(sf::RenderWindow& t_window);

private:
	Grid myGrid;
	sf::Vector2f mousePos;

	int type = 1;
	int clickCooldown=0;
	bool teamOne =true;

	std::vector<GameShapes> tempShapes;
};
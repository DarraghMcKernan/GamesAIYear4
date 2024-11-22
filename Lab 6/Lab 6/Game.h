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
	sf::Vector2f lockNearestCell();

private:
	Grid myGrid;
	sf::Vector2f mousePos;

	int type = 1;
	int clickCooldown=0;
	int teamNum = 0;
	int rotation = 0;

	std::vector<GameShapes> tempShapes;
	std::vector<GameShapes> highlighter;
};
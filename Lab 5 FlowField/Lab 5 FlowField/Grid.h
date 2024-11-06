#pragma once
#include "Cell.h"
#include <queue>

class Grid
{
public:
	void init();
	void update();
	void setCells(int t_cellNum, int t_type);
	void render(sf::RenderWindow& t_window);
	void generateIntegrationField();
	void generateFlowField();

private:
	int currentCellNum = 0;
	std::vector<Cell> cells;
	sf::Vector2i mousePos;
	sf::Font font;

	int startCellIndex = 0;
	int goalCellIndex = 0;
	int wallCellIndex = 0;

	int clickCooldown = 0;
	int renderChoice = 0;

	bool goalSet = false;
	bool startSet = false;
	bool cellCostsGenerated = false;
};
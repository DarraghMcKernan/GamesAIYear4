#pragma once
#include "globals.h"
#include "Grid.h"
#include "GameShapes.h"
#include "AIDecisionMaker.h"

class Game
{
public:
	void init();
	void update();
	void render(sf::RenderWindow& t_window);
	sf::Vector2f lockNearestCell();
	sf::Vector2f lockToKnownCell(int t_cellNum);

private:
	Grid myGrid;
	sf::Vector2f mousePos;

	AIDescisionMaker myAI;

	int type = 0;
	int clickCooldown=0;
	int teamNum = 0;
	int rotation = 0;

	/**
	* 
	* 
	*/
	bool placementValid = true;
	bool pieceSelected = false;
	bool playersTurn = true;

	std::vector<GameShapes> gamePieces;
	std::vector<GameShapes> highlighter;
	std::vector<GameShapes> pieceButtons;
};
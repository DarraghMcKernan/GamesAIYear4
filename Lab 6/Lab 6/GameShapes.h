#pragma once
#include "globals.h"

class GameShapes
{
public:
	GameShapes(int t_shapeType,int t_team, sf::Vector2f t_originPos,int t_rotation);
	void update();
	void render(sf::RenderWindow& t_window);
	void generatePiece(int t_shapeType);
	void rotatePieceRight();
	void updateOriginPos(sf::Vector2f t_newPos);
	sf::Vector2f returnOriginPos();

private:
	int type;
	int team;
	int rotation;

	std::vector<sf::RectangleShape> pieceShapes;
	sf::Vector2f originPos;
	sf::Color teamColour;

	std::vector<int>pieceShapesPositions;

};
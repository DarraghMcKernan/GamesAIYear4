#pragma once
#include "globals.h"
#include "Cell.h"

class GameShapes
{
public:
	GameShapes(int t_shapeType,int t_team, sf::Vector2f t_originPos,int t_rotation);
	void update();
	void render(sf::RenderWindow& t_window);
	void generatePiece(int t_shapeType);
	void redoShapes();
	void rotatePieceRight(int t_rotation);
	void updateOriginPos(sf::Vector2f t_newPos);
	sf::Vector2f returnOriginPos();
	void updateTeamNum(int t_num);
	bool checkCollisions(std::vector<Cell> t_nearbyCells);
	std::vector<bool> cellChecked;
	bool checkIfPieceUsed(int t_pieceNum);
	bool isCathedral();
	int getRotation();
	void scalePiece(float t_scale);
	int getHoveredType(sf::Vector2f t_mousePos);

private:
	int type;
	int team;
	int rotation = 0;
	int shapesActive = 0;
	int piecesNeeded = 9;

	std::vector<int> piecesUsed;

	std::vector<sf::RectangleShape> pieceShapes;
	sf::Vector2f originPos;
	sf::Color teamColour;

	std::vector<int>pieceShapesPositions;

};
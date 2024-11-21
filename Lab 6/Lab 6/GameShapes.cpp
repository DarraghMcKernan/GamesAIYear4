#include "GameShapes.h"

GameShapes::GameShapes(int t_shapeType, int t_team, sf::Vector2f t_originPos, int t_rotation) :type(t_shapeType), team(t_team), originPos(t_originPos), rotation(t_rotation)
{
	originPos -= sf::Vector2f{CELL_SIZE * 1.0f, CELL_SIZE* 1.0f };

	sf::RectangleShape tempPiece;

	if (team == 0)
	{
		teamColour = sf::Color(200,50,50);
		tempPiece.setFillColor(teamColour);
	}
	else if (team == 1)
	{
		teamColour = sf::Color(50, 50, 200);
		tempPiece.setFillColor(teamColour);
	}
	else if (team == 2) 
	{
		teamColour = sf::Color(50, 200, 50);
		tempPiece.setFillColor(sf::Color::Transparent);
		tempPiece.setOutlineColor(teamColour);
		tempPiece.setOutlineThickness(4);
	}

	if (t_shapeType == 0)
	{
		teamColour = sf::Color(200, 200, 200);
	}

	tempPiece.setSize({ CELL_SIZE ,CELL_SIZE });
	tempPiece.setOrigin({ CELL_SIZE / 2 ,CELL_SIZE / 2 });
	tempPiece.setPosition({ -10000,-1000 });

	for (int index = 0; index < 9; index++)
	{
		pieceShapes.push_back(tempPiece);
	}

	generatePiece(type);
}

void GameShapes::update()
{

}

void GameShapes::render(sf::RenderWindow& t_window)
{
	for (int index = 0; index < pieceShapes.size(); index++)
	{
		t_window.draw(pieceShapes[index]);
	}
}

//cathedral 0      6 pieces
//Tavern 1         1 piece
//stable 2         2 pieces
//inn 3            3 pieces
//bridge 4         3 pieces
//square 5		   4 pieces
//manor 6		   4 pieces
//abbey 7 		   4 pieces
//academy 8 	   5 pieces
//infirmary 9 	   5 pieces
//castle 10        5 pieces
//tower 11         5 pieces
void GameShapes::generatePiece(int t_shapeType)
{
	type = t_shapeType;

	sf::Vector2f offsetPos = originPos;

	if (type == 1)
	{
		pieceShapesPositions = 
			{0,0,0
			,0,1,0
			,0,0,0 };
	}
	else if (type == 2)
	{
		pieceShapesPositions =
		{0,1,0
		,0,1,0
		,0,0,0 };
	}
	else if (type == 3)
	{
		pieceShapesPositions =
		{0,1,0
		,1,1,0
		,0,0,0 };
	}
	else if (type == 4)
	{
		pieceShapesPositions =
		{0,1,0
		,0,1,0
		,0,1,0 };
	}
	else if (type == 5)
	{
		pieceShapesPositions =
		{1,1,0
		,1,1,0
		,0,0,0 };
	}
	else if (type == 6)
	{
		pieceShapesPositions =
		{0,1,0
		,1,1,0
		,0,1,0 };
	}
	else if (type == 7)
	{
		pieceShapesPositions =
		{0,1,1
		,1,1,0
		,0,0,0 };
	}
	else if (type == 8)
	{
		pieceShapesPositions =
		{1,1,0
		,0,1,1
		,0,1,0 };
	}
	else if (type == 9)
	{
		pieceShapesPositions =
		{0,1,0
		,1,1,1
		,0,1,0 };
	}
	else if (type == 10)
	{
		pieceShapesPositions =
		{0,0,0
		,1,1,1
		,1,0,1 };
	}
	else if (type == 11)
	{
		pieceShapesPositions =
		{0,1,1
		,1,1,0
		,1,0,0 };
	}

	for (int index = 0; index < 9; index++)
	{
		int row = index / 3;
		int col = index % 3;

		offsetPos = originPos + sf::Vector2f{ (col * CELL_SIZE) * 1.0f, (row * CELL_SIZE) * 1.0f };

		if (pieceShapesPositions[index] == 1)
		{
			pieceShapes[index].setPosition(offsetPos);
		}
		else pieceShapes[index].setPosition({-10000,-1000});
	}
}

void GameShapes::rotatePieceRight()
{

}

void GameShapes::updateOriginPos(sf::Vector2f t_newPos)
{
	originPos = t_newPos;
	originPos -= sf::Vector2f{ (CELL_SIZE * 1.0f) +1, (CELL_SIZE * 1.0f) +1};

	generatePiece(type);
}

sf::Vector2f GameShapes::returnOriginPos()
{
	return originPos + sf::Vector2f{ CELL_SIZE * 1.0f, CELL_SIZE * 1.0f };;
}
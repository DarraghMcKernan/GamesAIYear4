#include "GameShapes.h"

GameShapes::GameShapes(int t_shapeType, int t_team, sf::Vector2f t_originPos, int t_rotation) :type(t_shapeType), team(t_team), originPos(t_originPos), rotation(t_rotation)
{
	originPos -= sf::Vector2f{CELL_SIZE * 1.0f, CELL_SIZE* 1.0f };

	sf::RectangleShape tempPiece;

	if (team == 0)
	{
		teamColour = sf::Color(200,50,50);
		tempPiece.setFillColor(teamColour);
		tempPiece.setOutlineColor(sf::Color(50, 50, 50));
		tempPiece.setOutlineThickness(2);
	}
	else if (team == 1)
	{
		teamColour = sf::Color(50, 50, 200);
		tempPiece.setFillColor(teamColour);
		tempPiece.setOutlineColor(sf::Color(50, 50, 50));
		tempPiece.setOutlineThickness(2);
	}
	else if (team == 2)//for highlighter
	{
		teamColour = sf::Color(50, 200, 50);
		tempPiece.setFillColor(sf::Color(200, 50, 50,50));
		tempPiece.setOutlineColor(teamColour);
		tempPiece.setOutlineThickness(4);
	}
	else if (team == 3)//for highlighter
	{
		teamColour = sf::Color(50, 200, 50);
		tempPiece.setFillColor(sf::Color(50, 50, 200, 50));
		tempPiece.setOutlineColor(teamColour);
		tempPiece.setOutlineThickness(4);
	}

	if (t_shapeType == 0)
	{
		teamColour = sf::Color(200, 200, 200);
	}

	tempPiece.setSize({ CELL_SIZE -2,CELL_SIZE-2 });
	tempPiece.setOrigin({ (CELL_SIZE / 2) -1 ,(CELL_SIZE / 2) -1 });
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

	rotatePieceRight(rotation);

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

void GameShapes::redoShapes()
{
	sf::Vector2f offsetPos = originPos;
	for (int index = 0; index < 9; index++)
	{
		int row = index / 3;
		int col = index % 3;

		offsetPos = originPos + sf::Vector2f{ (col * CELL_SIZE) * 1.0f, (row * CELL_SIZE) * 1.0f };

		if (pieceShapesPositions[index] == 1)
		{
			pieceShapes[index].setPosition(offsetPos);
		}
		else pieceShapes[index].setPosition({ -10000,-1000 });
	}
}

void GameShapes::rotatePieceRight(int t_rotation)
{
	rotation = t_rotation;
	std::vector<int>rotatedPositions = pieceShapesPositions;

	/*{
	  0, 1, 2
	, 3, 4, 5
	, 6, 7, 8
	};*/
	for (int index = 0; index < rotation; index++)
	{
		rotatedPositions[0] = pieceShapesPositions[6];
		rotatedPositions[1] = pieceShapesPositions[3];
		rotatedPositions[2] = pieceShapesPositions[0];

		rotatedPositions[3] = pieceShapesPositions[7];
		//rotatedPositions[4] = pieceShapesPositions[3];
		rotatedPositions[5] = pieceShapesPositions[1];

		rotatedPositions[6] = pieceShapesPositions[8];
		rotatedPositions[7] = pieceShapesPositions[5];
		rotatedPositions[8] = pieceShapesPositions[2];

		pieceShapesPositions.clear();
		pieceShapesPositions = rotatedPositions;
	}

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

void GameShapes::updateTeamNum(int t_num)
{
	team = t_num;

	if (team == 0)
	{
		teamColour = sf::Color(200, 50, 50);
		for (int index = 0; index < 9; index++)
		{
			pieceShapes[index].setFillColor(teamColour);
		}
	}
	else if (team == 1)
	{
		teamColour = sf::Color(50, 50, 200);
		for (int index = 0; index < 9; index++)
		{
			pieceShapes[index].setFillColor(teamColour);
		}
	}
	else if (team == 2)//for highlighter
	{
		for (int index = 0; index < 9; index++)
		{
			pieceShapes[index].setFillColor(sf::Color(200, 50, 50, 50));
		}
	}
	else if (team == 3)//for highlighter
	{
		for (int index = 0; index < 9; index++)
		{
			pieceShapes[index].setFillColor(sf::Color(50, 50, 200, 50));
		}
	}
}

sf::RectangleShape GameShapes::checkCollisions(sf::RectangleShape t_shapeToCheck)
{
	sf::RectangleShape temp;
	temp.setPosition({ -100,-100 });

	for (int index = 0; index < 9; index++)
	{
		if (pieceShapes[index].getGlobalBounds().intersects(t_shapeToCheck.getGlobalBounds()))
		{
			return pieceShapes[index];
		}
	}

	return temp;
}
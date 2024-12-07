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
	else if (team == 4)//for red outline
	{
		tempPiece.setOutlineColor(sf::Color(200,50,50));
	}

	if (t_shapeType == 0)
	{
		teamColour = sf::Color(200, 200, 200);
	}

	tempPiece.setSize({ CELL_SIZE -2,CELL_SIZE-2 });
	tempPiece.setOrigin({ (CELL_SIZE / 2) -1 ,(CELL_SIZE / 2) -1 });
	tempPiece.setPosition({ -10000,-1000 });

	for (int index = 0; index < piecesNeeded; index++)
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
	for (int index = 0; index < piecesNeeded; index++)
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

	if (type == 0)
	{
		pieceShapesPositions =
		{0,1,0
		,1,1,1
		,0,1,0 };

		shapesActive = 6;
	}

	else if (type == 1)
	{
		pieceShapesPositions = 
			{0,0,0
			,0,1,0
			,0,0,0 };
		shapesActive = 1;
	}
	else if (type == 2)
	{
		pieceShapesPositions =
		{0,1,0
		,0,1,0
		,0,0,0  };
		shapesActive = 2;
	}
	else if (type == 3)
	{
		pieceShapesPositions =
		{0,1,0
		,1,1,0
		,0,0,0  };
		shapesActive = 3;
	}
	else if (type == 4)
	{
		pieceShapesPositions =
		{0,1,0
		,0,1,0
		,0,1,0  };
		shapesActive = 3;
	}
	else if (type == 5)
	{
		pieceShapesPositions =
		{1,1,0
		,1,1,0
		,0,0,0  };
		shapesActive = 4;
	}
	else if (type == 6)
	{
		pieceShapesPositions =
		{0,1,0
		,1,1,0
		,0,1,0  };
		shapesActive = 4;
	}
	else if (type == 7)
	{
		pieceShapesPositions =
		{0,1,1
		,1,1,0
		,0,0,0  };
		shapesActive = 4;
	}
	else if (type == 8)
	{
		pieceShapesPositions =
		{1,1,0
		,0,1,1
		,0,1,0  };
		shapesActive = 5;
	}
	else if (type == 9)
	{
		pieceShapesPositions =
		{0,1,0
		,1,1,1
		,0,1,0  };
		shapesActive = 5;
	}
	else if (type == 10)
	{
		pieceShapesPositions =
		{0,0,0
		,1,1,1
		,1,0,1  };
		shapesActive = 5;
	}
	else if (type == 11)
	{
		pieceShapesPositions =
		{0,1,1
		,1,1,0
		,1,0,0  };
		shapesActive = 5;
	}

	rotatePieceRight(rotation);

	for (int index = 0; index < piecesNeeded; index++)
	{
		int row = index / 3;
		int col = index % 3;

		offsetPos = originPos + sf::Vector2f{ (col * CELL_SIZE) * 1.0f, (row * CELL_SIZE) * 1.0f };

		if (pieceShapesPositions[index] == 1)
		{
			pieceShapes[index].setPosition(offsetPos);
		}
		else pieceShapes[index].setPosition({-10000,-1000});

		/*{
		  0, 1, 2
		, 3, 4, 5
		, 6, 7, 8 ,9
		};*/

		if (type == 0 && index == 1 && rotation == 0)
		{//the last piece will be 1 out from the rotation corner
			offsetPos.y -= CELL_SIZE;
			pieceShapes[0].setPosition(offsetPos);//set last piece as the offset
		}
		else if (type == 0 && index == 5 && rotation == 1)
		{
			offsetPos.x += CELL_SIZE;
			pieceShapes[0].setPosition(offsetPos);
		}
		else if (type == 0 && index == 7 && rotation == 2)
		{
			offsetPos.y += CELL_SIZE;
			pieceShapes[0].setPosition(offsetPos);
		}
		else if (type == 0 && index == 3 && rotation == 3)
		{
			offsetPos.x -= CELL_SIZE;
			pieceShapes[0].setPosition(offsetPos);
		}
	}
}

void GameShapes::redoShapes()
{
	sf::Vector2f offsetPos = originPos;
	for (int index = 0; index < piecesNeeded; index++)
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
	if (type == 0)
	{
		rotation = t_rotation;
	}
	else {
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
		for (int index = 0; index < piecesNeeded; index++)
		{
			pieceShapes[index].setFillColor(teamColour);
		}
	}
	else if (team == 1)
	{
		teamColour = sf::Color(50, 50, 200);
		for (int index = 0; index < piecesNeeded; index++)
		{
			pieceShapes[index].setFillColor(teamColour);
		}
	}
	else if (team == 2)//for highlighter
	{
		for (int index = 0; index < piecesNeeded; index++)
		{
			pieceShapes[index].setFillColor(sf::Color(200, 50, 50, 50));
			pieceShapes[index].setOutlineColor(teamColour);
		}
	}
	else if (team == 3)//for highlighter
	{
		for (int index = 0; index < piecesNeeded; index++)
		{
			pieceShapes[index].setFillColor(sf::Color(50, 50, 200, 50));
			pieceShapes[index].setOutlineColor(teamColour);
		}
	}
	else if (team == 4)//for red outline
	{
		for (int index = 0; index < piecesNeeded; index++)
		{
			pieceShapes[index].setOutlineColor(sf::Color(200, 50, 50));
		}
	}
}

bool GameShapes::checkCollisions(std::vector<Cell> t_nearbyCells)
{
	//-10000,-1000
	int collisionsValid = 0;//need 9 hits to be allowed to pass

	cellChecked = {false,false,false,false,false,false,false,false,false};

	for (int cells = 0; cells < t_nearbyCells.size(); cells++)
	{
		for (int index = 0; index < piecesNeeded; index++)
		{
			if (pieceShapes[index].getGlobalBounds().intersects(t_nearbyCells[cells].getCellShape().getGlobalBounds()) && (t_nearbyCells[index].getCellType() == 0) && cellChecked[index] == false)
			{
				cellChecked[index] = true;
				continue;//found a cell for the piece - look for more
			}
		}
	}

	for (int index = 0; index < piecesNeeded; index++)
	{
		if (cellChecked[index] == true)
		{
			collisionsValid++;
		}
	}

	if (collisionsValid == shapesActive)//if all used squares are accounted for
	{
		return true;
	}

	return false;
}

bool GameShapes::checkIfPieceUsed(int t_pieceNum)
{


	return false;
}

bool GameShapes::isCathedral()
{
	if (type == 0)
	{
		return true;
	}
	else return false;
}

int GameShapes::getRotation()
{
	return rotation;
}

void GameShapes::scalePiece(float t_scale)
{

}

int GameShapes::getHoveredType(sf::Vector2f t_mousePos)
{
	for (int index = 0; index < piecesNeeded; index++)
	{
		if (pieceShapes[index].getGlobalBounds().contains({ t_mousePos.x,t_mousePos.y }))
		{
			return type;
		}
	}

	return 0;
}

void GameShapes::useType(int t_type)
{
	if (team == 2)//player
	{
		playerPiecesUsed[t_type]++;
		std::cout << t_type << "\n";
	}
	else {//ai
		AIPiecesUsed[t_type]++;
	}
}

bool GameShapes::pieceAllowed(int t_type)
{
	if (team == 2)
	{
		if (t_type == 1 || t_type == 2 || t_type == 3)
		{
			if (playerPiecesUsed[t_type] < 2)
			{
				std::cout << t_type << "\n";
				return true;
			}
		}
		else if (playerPiecesUsed[t_type] < 1)
		{
			std::cout << t_type << "\n";
			return true;
		}
	}

	return false;
}

void GameShapes::deactivateButton()
{
	for (int index = 0; index < piecesNeeded; index++)
	{
		pieceShapes[index].setFillColor(sf::Color(100, 50, 50));
	}
}

std::vector<int> GameShapes::getMatrixOfCells()
{
	return pieceShapesPositions;//compare the matrix of positions to the list of 9 cells around the mouse and if the 1's here line up with 0's on the grid its valids
}

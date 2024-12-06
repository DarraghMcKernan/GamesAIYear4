#include "Game.h"

void Game::init()
{
	myGrid.init();

	GameShapes highlighterShape(0, 2, { mousePos.x ,mousePos.y }, 0);
	highlighter.push_back(highlighterShape);

	for(int index = 0;index < PIECES_PER_TEAM-4;index++)
	{
		int rotation = 1;
		sf::Vector2f startPos = { 1050.0f + ((index % 3) * CELL_SIZE * 4), 150.0f + (250 * (index / 3)) };
		if (index > 2)
		{
			startPos.y -= 50;
		}
		if (index > 5)
		{
			startPos.y -= 50;
		}
		if (index == 9)
		{
			rotation = 2;
			startPos.y += 25;
			startPos.x += 300;
		}
		GameShapes tempButtons(index + 1, 0, startPos, rotation);
		pieceButtons.push_back(tempButtons);
	}
}

void Game::update()
{
	if (clickCooldown > 0)
	{
		clickCooldown--;
	}

	myGrid.update();
	
	///*
	if (playersTurn == false && clickCooldown == 0)
	{
		int aiPiece = myAI.pickPieceToPlace();
		int aiCell = myAI.pickCellToPlace();
		int aiRotation = myAI.pickRotation();

		

		highlighter[0].updateOriginPos(lockToKnownCell(aiCell));
		highlighter[0].rotatePieceRight(aiRotation);
		highlighter[0].generatePiece(aiPiece);
		

		if (highlighter[0].checkCollisions(myGrid.returnNearbyCellPos()) == true)
		{
			myGrid.setCellsTo(highlighter[0].cellChecked, highlighter[0].isCathedral(), highlighter[0].getRotation());
			std::cout << "position is valid\n";
			GameShapes tempShape(aiPiece, 1, highlighter[0].returnOriginPos(), aiRotation);
			gamePieces.push_back(tempShape);

			if (teamNum == 0)
			{
				teamNum = 1;
			}
			else teamNum = 0;

			//pieceSelected = false;

			highlighter[0].updateTeamNum(teamNum + 2);

			playersTurn = true;

			highlighter[0].updateOriginPos(lockNearestCell());
			highlighter[0].rotatePieceRight(rotation);
			highlighter[0].generatePiece(type);
		}
	}
	//*/

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (int index = 0; index < PIECES_PER_TEAM - 4; index++)
		{			
			int temp = pieceButtons[index].getHoveredType(mousePos);
			if (highlighter[0].pieceAllowed(temp) == true)
			{
				pieceButtons[index].updateTeamNum(teamNum);
				type = temp;
				pieceSelected = true;
				highlighter[0].useType(type);
				highlighter[0].generatePiece(type);
			}			
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && clickCooldown == 0)
	{
		clickCooldown = 30;
		rotation++;
		if (rotation == 4)
		{
			rotation = 0;
		}
		highlighter[0].rotatePieceRight(rotation);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && clickCooldown == 0)
	{
		clickCooldown = 30;
		rotation--;
		if (rotation == -1)
		{
			rotation = 3;
		}
		highlighter[0].rotatePieceRight(rotation);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickCooldown == 0 && pieceSelected == true)
	{
		//std::cout << "shape placed\n";
		clickCooldown = 30;
		if (highlighter[0].checkCollisions(myGrid.returnNearbyCellPos()) == true)
		{
			myGrid.setCellsTo(highlighter[0].cellChecked,highlighter[0].isCathedral(), highlighter[0].getRotation());
			//std::cout << "position is valid\n";
			GameShapes tempShape(type, teamNum, highlighter[0].returnOriginPos(), rotation);
			gamePieces.push_back(tempShape);

			if (teamNum == 0)
			{
				teamNum = 1;
			}
			else teamNum = 0;

			pieceSelected = false;

			highlighter[0].updateTeamNum(teamNum + 2);

			playersTurn = false;
			//clickCooldown = 30;
		}
	}

	if (placementValid == false)//if placement is invalid
	{
		highlighter[0].updateTeamNum(4);//set outline to red
	}
	else 
	{ 
		highlighter[0].updateTeamNum(teamNum + 2);
	}
}

void Game::render(sf::RenderWindow& t_window)
{
	mousePos = { static_cast<float>(sf::Mouse::getPosition(t_window).x),static_cast<float>(sf::Mouse::getPosition(t_window).y)};
	highlighter[0].updateOriginPos(lockNearestCell());
	myGrid.render(t_window);

	for (int index = 0; index < gamePieces.size(); index++)
	{
		gamePieces[index].render(t_window);
	}
	highlighter[0].render(t_window);

	for (int index = 0; index < PIECES_PER_TEAM-4 ; index++)
	{
		pieceButtons[index].render(t_window);
	}
}

sf::Vector2f Game::lockNearestCell()
{
	sf::Vector2f temp = myGrid.returnHoveredCellPos(mousePos);
	if (temp == sf::Vector2f({ -1000,-1000 }))
	{
		return mousePos;
	}
	return temp;
}

sf::Vector2f Game::lockToKnownCell(int t_cellNum)
{
	sf::Vector2f tempFakeMousePos = { ((t_cellNum / GRID_SIZE) * CELL_SIZE * 1.0f) + CELL_SIZE / 3,((t_cellNum % GRID_SIZE) * CELL_SIZE * 1.0f) + CELL_SIZE / 3 };

	sf::Vector2f temp = myGrid.returnHoveredCellPos(tempFakeMousePos);
	
	return temp;
}
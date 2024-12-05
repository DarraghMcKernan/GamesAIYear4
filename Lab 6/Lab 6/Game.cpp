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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (int index = 0; index < PIECES_PER_TEAM - 4; index++)
		{
			int temp = pieceButtons[index].getHoveredType(mousePos);
			if (temp != 0)
			{
				type = temp;
			}			
		}
		highlighter[0].generatePiece(type);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		type = 1;
		highlighter[0].generatePiece(type);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		type = 2;
		highlighter[0].generatePiece(type);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		type = 3;
		highlighter[0].generatePiece(type);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		type = 4;
		highlighter[0].generatePiece(type);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		type = 5;
		highlighter[0].generatePiece(type);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
	{
		type = 6;
		highlighter[0].generatePiece(type);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
	{
		type = 7;
		highlighter[0].generatePiece(type);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
	{
		type = 8;
		highlighter[0].generatePiece(type);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
	{
		type = 9;
		highlighter[0].generatePiece(type);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
	{
		type = 10;
		highlighter[0].generatePiece(type);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen))
	{
		type = 11;
		highlighter[0].generatePiece(type);
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickCooldown == 0)
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

			highlighter[0].updateTeamNum(teamNum + 2);
		}
	}
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && clickCooldown == 0)
	{
		clickCooldown = 30;
		if (teamNum == 0)
		{
			teamNum = 1;
		}
		else teamNum = 0;

		highlighter[0].updateTeamNum(teamNum + 2);
	}*/

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
	return myGrid.returnHoveredCellPos(mousePos);
}
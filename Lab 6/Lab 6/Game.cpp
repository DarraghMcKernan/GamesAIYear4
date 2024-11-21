#include "Game.h"

void Game::init()
{
	myGrid.init();

	GameShapes highlighterShape(1, 2, { mousePos.x ,mousePos.y }, 0);
	highlighter.push_back(highlighterShape);
}

void Game::update()
{
	if (clickCooldown > 0)
	{
		clickCooldown--;
	}

	myGrid.update();
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickCooldown == 0)
	{
		std::cout << "shape placed\n";
		clickCooldown = 30;
		GameShapes tempShape(type, teamNum, highlighter[0].returnOriginPos(), 0);
		tempShapes.push_back(tempShape);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && clickCooldown == 0)
	{
		clickCooldown = 30;
		if (teamNum == 0)
		{
			teamNum = 1;
		}
		else teamNum = 0;

		highlighter[0].updateTeamNum(teamNum + 2);
	}
}

void Game::render(sf::RenderWindow& t_window)
{
	mousePos = { static_cast<float>(sf::Mouse::getPosition(t_window).x),static_cast<float>(sf::Mouse::getPosition(t_window).y)};
	highlighter[0].updateOriginPos(lockNearestCell());
	myGrid.render(t_window);

	for (int index = 0; index < tempShapes.size(); index++)
	{
		tempShapes[index].render(t_window);
	}
	highlighter[0].render(t_window);
}

sf::Vector2f Game::lockNearestCell()
{
	return myGrid.returnHoveredCellPos(mousePos);
}
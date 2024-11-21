#include "Game.h"

void Game::init()
{
	myGrid.init();
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
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		type = 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		type = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		type = 4;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		type = 5;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
	{
		type = 6;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
	{
		type = 7;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
	{
		type = 8;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
	{
		type = 9;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
	{
		type = 10;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen))
	{
		type = 11;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clickCooldown == 0)
	{
		clickCooldown = 30;
		GameShapes tempShape(type, teamOne, { mousePos.x ,mousePos.y }, 0);
		tempShapes.push_back(tempShape);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && clickCooldown == 0)
	{
		clickCooldown = 30;
		teamOne = !teamOne;
	}
}

void Game::render(sf::RenderWindow& t_window)
{
	mousePos = { static_cast<float>(sf::Mouse::getPosition(t_window).x),static_cast<float>(sf::Mouse::getPosition(t_window).y)};
	myGrid.render(t_window);

	for (int index = 0; index < tempShapes.size(); index++)
	{
		tempShapes[index].render(t_window);
	}
}
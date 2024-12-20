#include "Player.h"

void Player::init()
{
	playerShape.setPointCount(3);
	playerShape.setScale(3, 5);
	playerShape.setFillColor(sf::Color::Green);
	playerShape.setRadius(5);
	position = { 400, 500 };
	playerShape.setPosition(position);
	playerShape.setOrigin(5, 5);
}

void Player::update()
{
	playerMovement();
	playerRotation();

	float radians = rotation * 3.14 / 180;

	position.x += sin(radians) * velocity;
	position.y -= cos(radians) * velocity;

	keepPlayerOnScreen();

	playerShape.setRotation(rotation);
	playerShape.setPosition(position);
}

void Player::render(sf::RenderWindow& t_window)
{
	t_window.draw(playerShape);
}

void Player::playerMovement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (velocity == 0)
		{
			velocity = 0.3;//kickstart movement so there is a value to add velocity to
		}
		velocity *= acceleration;
		if (velocity > maxVelocity)
		{
			velocity = maxVelocity;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocity *= decceleration;
		if (velocity < 0.3)//stop moving once the player has slowed down enough
		{
			velocity = 0;
		}
	}
	else velocity *= drag;//slow down over time
}

void Player::playerRotation()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		rotation -= 1.5;
		if (rotation < 0)
		{
			rotation = 359;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		rotation += 1.5;
		if (rotation > 360)
		{
			rotation = 1;
		}
	}
}

void Player::keepPlayerOnScreen()
{
	if (position.x > SCREEN_SIZE.x + 10)
	{
		position.x = -10;
	}
	if (position.x < -10)
	{
		position.x = SCREEN_SIZE.x + 10;
	}

	if (position.y > SCREEN_SIZE.y + 10)
	{
		position.y = -10;
	}
	if (position.y < -10)
	{
		position.y = SCREEN_SIZE.y + 10;
	}
}
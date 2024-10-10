#include "Player.h"

void Player::init()
{
	playerShape.setPointCount(3);
	playerShape.setScale(3, 5);
	playerShape.setFillColor(sf::Color::Green);
	playerShape.setRadius(5);
	position = { 400, 200 };
	playerShape.setPosition(position);
	playerShape.setOrigin(5, 5);

	VisionCone.setPointCount(3);
	VisionCone.setScale(3.3, -5);
	VisionCone.setFillColor(sf::Color(0, 0, 255, 50));
	VisionCone.setRadius(40);
	VisionCone.setPosition(position);
	VisionCone.setOrigin(40, 0);

	if (!playerTexture.loadFromFile("Assets/Images/F-22.png"))
	{
		std::cout << "error loading player sprite\n";
	}
	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(position);
	playerSprite.setScale(.1, .1);
	playerSprite.setOrigin((playerSprite.getTextureRect().getSize().x/2)+50, playerSprite.getTextureRect().getSize().y/2);
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
	
	playerSprite.setRotation(rotation + 90);
	playerSprite.setPosition(position);

	VisionCone.setRotation(rotation);
	VisionCone.setPosition(position);
}

void Player::render(sf::RenderWindow& t_window)
{
	//t_window.draw(VisionCone);
	t_window.draw(playerSprite);
	//t_window.draw(playerShape);	
}

void Player::playerMovement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (velocity <= 0.1f)
		{
			velocity = 0.3f;//kickstart movement so there is a value to add velocity to
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
	}
	else velocity *= drag;//slow down over time

	if (velocity < 0.3)//stop moving once the player has slowed down enough
	{
		velocity = 0;
	}
}

void Player::playerRotation()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		rotation -= rotationSpeed;
		if (rotation < 0)
		{
			rotation = 359;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		rotation += rotationSpeed;
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

void Player::visionCone(sf::Vector2f t_target)
{
	int angleForward = normalizeAngle(playerShape.getRotation());

	int angleToTarget = normalizeAngle(rotateToTarget(t_target));

	int left = normalizeAngle(angleForward - 30);
	int right = normalizeAngle(angleForward + 30);

	bool angleInRange = false;
	if (left < right && angleToTarget > left && angleToTarget < right)//if the angle is between 0 and 360
	{
		angleInRange = true;
	}
	else if (left > right && (angleToTarget > left || angleToTarget < right))//if the angle is lying between 330 and 30 just check if its between one of the angles as it must then be between both
	{
		angleInRange = true;
	}
	
	if(angleInRange == true)
	{
		sf::Vector2f vectorToPoint = t_target - position;
		float distance = sqrt((vectorToPoint.x * vectorToPoint.x) + (vectorToPoint.y * vectorToPoint.y));
		if (distance < 320)
		{
			VisionCone.setFillColor(sf::Color(0, 255, 0, 50));
		}
		else VisionCone.setFillColor(sf::Color(0, 0, 255, 50));
	}
	else VisionCone.setFillColor(sf::Color(0, 0, 255, 50));
}

float Player::rotateToTarget(sf::Vector2f t_target)
{
	sf::Vector2f angleToTarget = t_target - position;

	float radians = atan2(angleToTarget.y, angleToTarget.x);

	return (radians * 180 / 3.14f) + 90;
}

sf::Vector2f Player::returnPlayerPos()
{
	return position;
}

sf::Vector2f Player::returnPlayerPredictedPos()
{
	sf::Vector2f predictedPos;

	predictedPos = position;

	float radians = rotation * 3.14 / 180;

	predictedPos.x += sin(radians) * (velocity*30);//the position the player will approximately be at in 30 updates
	predictedPos.y -= cos(radians) * (velocity*30);

	return predictedPos;
}

int Player::normalizeAngle(int t_angle)
{
	t_angle = t_angle % 360;//make sure its in the range of 360

	if (t_angle < 0)//if negative make positive
	{
		t_angle += 360;
	}

	return t_angle;
}
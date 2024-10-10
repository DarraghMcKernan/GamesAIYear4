#include "Behaviour.h"

sf::Vector2f Behaviour::vectorToTarget(const sf::Vector2f t_thisPos, const sf::Vector2f t_targetPos)
{
	vectorToPoint = t_targetPos - t_thisPos;//get angle to target
	float distance = sqrt((vectorToPoint.x * vectorToPoint.x) + (vectorToPoint.y * vectorToPoint.y));//get distance between 2 points
	vectorToPoint = sf::Vector2f{ vectorToPoint.x / (distance*1.3f),vectorToPoint.y / (distance * 1.3f) };//normalise vector

	return vectorToPoint;
}

sf::Vector2f Behaviour::wander(const sf::Vector2f t_thisPos)
{
	wanderTimer--;
	if (wanderTimer < 0)
	{
		wanderTimer = (rand()%200) + 100;

		sf::Vector2f randomPoint;

		std::random_device rand;
		std::mt19937 gen(rand());
		std::uniform_int_distribution<> distrX(0, SCREEN_SIZE.x);
		randomPoint.x = distrX(gen);
		std::uniform_int_distribution<> distrY(0, SCREEN_SIZE.y);
		randomPoint.y = distrY(gen);
		
		vectorToPoint = randomPoint - t_thisPos;//get angle to target
		float distance = sqrt((vectorToPoint.x * vectorToPoint.x) + (vectorToPoint.y * vectorToPoint.y));//get distance between 2 points
		vectorToPoint = sf::Vector2f{ vectorToPoint.x / (distance * 1.3f),vectorToPoint.y / (distance * 1.3f) };//normalise vector

		if (distance <= 50)
		{
			vectorToPoint = sf::Vector2f{ 0,0 };
		}
	}

	return vectorToPoint;
}

sf::Vector2f Behaviour::arrive(const sf::Vector2f t_thisPos, const sf::Vector2f t_targetPos)
{
	vectorToPoint = t_targetPos - t_thisPos;//get angle to target
	float distance = sqrt((vectorToPoint.x * vectorToPoint.x) + (vectorToPoint.y * vectorToPoint.y));//get distance between 2 points
	
	if (distance < 300 && distance > 50)
	{
		vectorToPoint = sf::Vector2f{ vectorToPoint.x / (distance * 1.3f),vectorToPoint.y / (distance * 1.3f) };//normalise vector
		vectorToPoint = vectorToPoint * ( (distance / 300));
	}
	else if (distance <= 50)
	{
		vectorToPoint = sf::Vector2f{ 0,0 };
	}
	else vectorToPoint = sf::Vector2f{ vectorToPoint.x / (distance * 1.3f),vectorToPoint.y / (distance * 1.3f) };//normalise vector

	return vectorToPoint;
}

sf::Vector2f Behaviour::arriveSlow(const sf::Vector2f t_thisPos, const sf::Vector2f t_targetPos)
{
	vectorToPoint = t_targetPos - t_thisPos;//get angle to target
	float distance = sqrt((vectorToPoint.x * vectorToPoint.x) + (vectorToPoint.y * vectorToPoint.y));//get distance between 2 points

	if (distance < 300 && distance > 50)
	{
		vectorToPoint = sf::Vector2f{ vectorToPoint.x / (distance * 2),vectorToPoint.y / (distance * 2) };
		vectorToPoint = vectorToPoint * ((distance / 300));
	}
	else if (distance <= 50)
	{
		vectorToPoint = sf::Vector2f{ 0,0 };
	}
	else vectorToPoint = sf::Vector2f{ vectorToPoint.x / (distance * 1.3f),vectorToPoint.y / (distance * 1.3f) };//normalise vector

	return vectorToPoint;
}

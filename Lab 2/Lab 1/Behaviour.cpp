#include "Behaviour.h"

sf::Vector2f Behaviour::vectorToTarget(const sf::Vector2f t_thisPos, const sf::Vector2f t_targetPos)
{
	vectorToPoint = t_targetPos - t_thisPos;//get angle to target
	float distance = sqrt((vectorToPoint.x * vectorToPoint.x) + (vectorToPoint.y * vectorToPoint.y));//get distance between 2 points
	vectorToPoint = sf::Vector2f{ vectorToPoint.x / distance,vectorToPoint.y / distance };//normalise vector
	return vectorToPoint;
}

sf::Vector2f Behaviour::wander(const sf::Vector2f t_thisPos)
{
	wanderTimer--;
	if (wanderTimer < 0)
	{
		wanderTimer = wanderTimerMax;

		sf::Vector2f randomPoint;

		std::random_device rand;
		std::mt19937 gen(rand());
		std::uniform_int_distribution<> distrX(0, SCREEN_SIZE.x);
		randomPoint.x = distrX(gen);
		std::uniform_int_distribution<> distrY(0, SCREEN_SIZE.y);
		randomPoint.y = distrY(gen);
		
		vectorToPoint = randomPoint - t_thisPos;//get angle to target
		float distance = sqrt((vectorToPoint.x * vectorToPoint.x) + (vectorToPoint.y * vectorToPoint.y));//get distance between 2 points
		vectorToPoint = sf::Vector2f{ vectorToPoint.x / distance,vectorToPoint.y / distance };//normalise vector
	}

	return vectorToPoint;
}

#pragma once
#include "Globals.h"
#include "BehaviourEnum.h"
#include "random"

class Behaviour
{
public:
	sf::Vector2f vectorToTarget(const sf::Vector2f t_thisPos, const sf::Vector2f t_targetPos);
	sf::Vector2f wander(const sf::Vector2f t_thisPos);

private:
	sf::Vector2f vectorToPoint;

	int wanderTimer = 0;
	int wanderTimerMax = 180;
};
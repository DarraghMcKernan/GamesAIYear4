#pragma once
#include "Globals.h"
#include "BehaviourEnum.h"

class Behaviour
{
public:
	sf::Vector2f seekTarget(const sf::Vector2f t_thisPos, const sf::Vector2f t_targetPos);
};
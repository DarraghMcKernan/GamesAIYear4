#include "Behaviour.h"

sf::Vector2f Behaviour::seekTarget(const sf::Vector2f t_thisPos, const sf::Vector2f t_targetPos)
{
	sf::Vector2f vectorToTarget = t_thisPos - t_targetPos;
	vectorToTarget = sqrt(vectorToTarget.x * vectorToTarget.x + vectorToTarget.y*vectorToTarget.y) ;
	return vectorToTarget;
}

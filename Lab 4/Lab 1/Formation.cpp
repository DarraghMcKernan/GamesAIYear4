#include "Formation.h"

void Formation::init()
{
	formationCircle.setRadius(10);
	formationCircle.setFillColor(sf::Color(0, 255, 0, 100));
	formationCircle.setPosition(sf::Vector2f(-100, -100));
	formationCircle.setOrigin(10, 10);

	for (int i = 0; i < 4; i++)
	{
		formationPositions.push_back(sf::Vector2f(0, 0));
	}
}

void Formation::setLeaderPos(sf::Vector2f t_leaderPos)
{
	FormationLeaderPos = t_leaderPos;
}

void Formation::render(sf::RenderWindow& t_window)
{
	formationCircle.setPosition(formationPositions[0]);
	t_window.draw(formationCircle);

	formationCircle.setPosition(formationPositions[1]);
	t_window.draw(formationCircle);

	formationCircle.setPosition(formationPositions[2]);
	t_window.draw(formationCircle);

	formationCircle.setPosition(formationPositions[3]);
	t_window.draw(formationCircle);
}

sf::Vector2f Formation::getFormationPoint(int t_position, float t_rotation, sf::Vector2f t_fighterPos, bool t_altMode)
{
	float radians = t_rotation * (3.14159f / 180.0f);

	sf::Vector2f offset;

	if (t_position == 0)
	{
		//tempPos = rotateWithFormation(sf::Vector2f(-formationXOffset/2, formationYOffset), radians);
		offset = sf::Vector2f(-formationXOffset / 2, formationYOffset);
	}
	else if (t_position == 1)
	{
		//tempPos = rotateWithFormation(sf::Vector2f(-formationXOffset*1.5, formationYOffset*2), radians);
		offset = sf::Vector2f(- formationXOffset * 1.5, formationYOffset * 2);
	}
	else if (t_position == 2)
	{
		//tempPos = rotateWithFormation(sf::Vector2f(formationXOffset/2, formationYOffset * 2), radians);
		offset = sf::Vector2f(formationXOffset / 2, formationYOffset * 2);
	}
	else if (t_position == 3)
	{
		//tempPos = rotateWithFormation(sf::Vector2f(formationXOffset * 1.5, formationYOffset * 3), radians);
		offset = sf::Vector2f(formationXOffset * 1.5, formationYOffset * 3);
	}
	//tempPos = rotateWithFormation(offset, radians);

	sf::Vector2f actualFormationPoint = rotateWithFormation(offset, radians);
	actualFormationPoint += FormationLeaderPos;


	if (t_altMode == true)
	{
		float distance = distanceBetween(actualFormationPoint, t_fighterPos);
		distance /= 100;

		sf::Vector2f backwardsOffset(offset.x, offset.y * distance);
		if (backwardsOffset.y < offset.y)
		{
			backwardsOffset.y = offset.y;
		}

		backwardsOffset = rotateWithFormation(backwardsOffset, radians);
		backwardsOffset += FormationLeaderPos;

		formationPositions[t_position] = backwardsOffset;
		return formationPositions[t_position];
	}
	formationPositions[t_position] = actualFormationPoint;
	return actualFormationPoint;
}

sf::Vector2f Formation::rotateWithFormation(sf::Vector2f t_position, float t_angle)
{
	sf::Vector2f tempPos = t_position;

	float cosTheta = std::cos(t_angle);
	float sinTheta = std::sin(t_angle);

	tempPos = sf::Vector2f(tempPos.x * cosTheta - tempPos.y * sinTheta, tempPos.x * sinTheta + tempPos.y * cosTheta);
	
	return tempPos;
}

float Formation::distanceBetween(sf::Vector2f t_point1, sf::Vector2f t_point2)
{
	sf::Vector2f distance = sf::Vector2f(t_point1.x - t_point2.x, t_point1.y - t_point2.y);

	return std::sqrt(distance.x * distance.x + distance.y * distance.y);
}
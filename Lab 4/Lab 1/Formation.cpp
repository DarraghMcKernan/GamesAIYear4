#include "Formation.h"

void Formation::init()
{
	formationCircle.setRadius(10);
	formationCircle.setFillColor(sf::Color(0, 255, 0, 100));
	formationCircle.setPosition(sf::Vector2f(-100, -100));

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

sf::Vector2f Formation::getFormationPoint(int t_position, float t_rotation)
{
	float radians = t_rotation * (3.14 / 180);

	if (t_position == 0)
	{
		formationPositions[0] = rotateWithFormation(sf::Vector2f(-formationXOffset/2, formationYOffset), radians);
	}
	else if (t_position == 1)
	{
		formationPositions[1] = rotateWithFormation(sf::Vector2f(-formationXOffset*1.5, formationYOffset*2), radians);
	}
	else if (t_position == 2)
	{
		formationPositions[2] = rotateWithFormation(sf::Vector2f(formationXOffset/2, formationYOffset * 2), radians);
	}
	else if (t_position == 3)
	{
		formationPositions[3] = rotateWithFormation(sf::Vector2f(formationXOffset * 1.5, formationYOffset * 3), radians);
	}

	formationPositions[t_position] += FormationLeaderPos;
	return formationPositions[t_position];
}

sf::Vector2f Formation::rotateWithFormation(sf::Vector2f t_position, float t_angle)
{
	sf::Vector2f tempPos = t_position;

	float cosTheta = std::cos(t_angle);
	float sinTheta = std::sin(t_angle);

	tempPos = sf::Vector2f(tempPos.x * cosTheta - tempPos.y * sinTheta, tempPos.x * sinTheta + tempPos.y * cosTheta);
	
	return tempPos;
}
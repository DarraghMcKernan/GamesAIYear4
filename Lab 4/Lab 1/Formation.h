#pragma once
#include "Globals.h"

class Formation 
{
public:
	void init();
	void setLeaderPos(sf::Vector2f t_leaderPos);
	void render(sf::RenderWindow& t_window);
	sf::Vector2f getFormationPoint(int t_position, float t_rotation,sf::Vector2f t_fighterPos,bool t_altMode);

private:
	sf::Vector2f rotateWithFormation(sf::Vector2f t_position, float t_angle);

	float distanceBetween(sf::Vector2f t_point1, sf::Vector2f t_point2);

	sf::Vector2f FormationLeaderPos;
	std::vector<sf::Vector2f> formationPositions;
	sf::Vector2f firstPos;
	sf::Vector2f secondPos;

	sf::CircleShape formationCircle;

	int formationXOffset = 80;
	int formationYOffset = 40;
};
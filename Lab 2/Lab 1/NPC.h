#pragma once
#include "Globals.h"
#include "Behaviour.h"
#include "BehaviourEnum.h"

class NPC
{
public:
	NPC(sf::Vector2f SpawnPosition, float speed, BehaviourEnum startBehaviour);
	void init();
	void update(sf::Vector2f t_playerPos);
	void render(sf::RenderWindow& t_window);
	void keepNPCOnScreen();
	void rotateToTarget(sf::Vector2f t_target);

private:
	sf::Vector2f position = { 0,0 };
	sf::Vector2f playerPosition = { 0,0 };
	sf::Vector2f newPosition = { 0,0 };

	float speed = 1.0f;

	sf::Text NPCNametag;
	sf::Font font;

	sf::CircleShape NPCShape;
	sf::CircleShape VisionCone;

	BehaviourEnum currentBehaviour = BehaviourEnum::Wander;
	Behaviour NPCBehaviour;
};
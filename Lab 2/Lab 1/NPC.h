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

private:
	sf::Vector2f position = { 0,0 };
	sf::Vector2f playerPosition = { 0,0 };

	sf::CircleShape NPCShape;

	BehaviourEnum currentBehaviour = BehaviourEnum::Wander;
	Behaviour NPCBehaviour;
};
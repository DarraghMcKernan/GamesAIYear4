#include "NPC.h"
#include "random"

NPC::NPC(sf::Vector2f SpawnPosition, float speed, BehaviourEnum startBehaviour)
	: currentBehaviour(startBehaviour)
{
	init();
}

void NPC::init()
{
	NPCShape.setPointCount(3);
	NPCShape.setScale(3, 5);
	NPCShape.setFillColor(sf::Color::Red);
	NPCShape.setRadius(5);
	position = { 800, 500 };
	NPCShape.setPosition(position);
	NPCShape.setOrigin(5, 5);
}

void NPC::update(sf::Vector2f t_playerPos)
{
	playerPosition = t_playerPos;

	position = NPCBehaviour.seekTarget(position, playerPosition);

	keepNPCOnScreen();

	NPCShape.setPosition(position);
}

void NPC::render(sf::RenderWindow& t_window)
{
	t_window.draw(NPCShape);
}

void NPC::keepNPCOnScreen()
{
	if (position.x > SCREEN_SIZE.x + 10)
	{
		position.x = -10;
	}
	if (position.x < -10)
	{
		position.x = SCREEN_SIZE.x + 10;
	}

	if (position.y > SCREEN_SIZE.y + 10)
	{
		position.y = -10;
	}
	if (position.y < -10)
	{
		position.y = SCREEN_SIZE.y + 10;
	}
}
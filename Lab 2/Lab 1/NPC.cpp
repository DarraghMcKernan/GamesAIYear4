#include "NPC.h"
#include "random"

NPC::NPC(sf::Vector2f SpawnPosition, float speed, BehaviourEnum startBehaviour)
	: currentBehaviour(startBehaviour) ,speed(speed), position(SpawnPosition)
{
	init();
}

void NPC::init()
{
	NPCShape.setPointCount(3);
	NPCShape.setScale(3, 5);
	NPCShape.setFillColor(sf::Color::Red);
	NPCShape.setRadius(5);
	NPCShape.setPosition(position);
	NPCShape.setOrigin(5, 5);

	VisionCone.setPointCount(3);
	VisionCone.setScale(3, -5);
	VisionCone.setFillColor(sf::Color(255, 0, 0, 50));
	VisionCone.setRadius(40);
	VisionCone.setPosition(position);
	VisionCone.setOrigin(40, 0);
}

void NPC::update(sf::Vector2f t_playerPos)
{
	playerPosition = t_playerPos;

	newPosition = position;

	if (currentBehaviour == BehaviourEnum::Seek || currentBehaviour == BehaviourEnum::Pursue)
	{
		newPosition = NPCBehaviour.vectorToTarget(position, playerPosition);
	}
	else if (currentBehaviour == BehaviourEnum::Wander)
	{
		newPosition = NPCBehaviour.wander(position);
	}
	else if (currentBehaviour == BehaviourEnum::Arrive)
	{
		newPosition = NPCBehaviour.arrive(position, playerPosition);
	}
	else if (currentBehaviour == BehaviourEnum::ArriveSlow)
	{
		newPosition = NPCBehaviour.arriveSlow(position, playerPosition);
	}

	position = sf::Vector2f{ position.x + (newPosition.x * speed),position.y + (newPosition.y * speed) };

	keepNPCOnScreen();

	if (currentBehaviour == BehaviourEnum::Wander)
	{
		sf::Vector2f wanderRotate = sf::Vector2f{ position.x + (newPosition.x * 10),position.y + (newPosition.y * 10) };// look at a position that is ahead of where we are moving 
		rotateToTarget(wanderRotate);
	}
	else rotateToTarget(playerPosition);

	NPCShape.setPosition(position);
	VisionCone.setPosition(position);
}

void NPC::render(sf::RenderWindow& t_window)
{
	t_window.draw(VisionCone);
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

void NPC::rotateToTarget(sf::Vector2f t_target)
{
	sf::Vector2f angleToTarget = t_target - position;

	float radians = atan2(angleToTarget.y, angleToTarget.x);

	NPCShape.setRotation((radians * 180 / 3.14f) + 90);
	VisionCone.setRotation((radians * 180 / 3.14f) + 90);
}

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
	float rotateToTarget(sf::Vector2f t_target);
	void visionConeView(sf::Vector2f t_target);
	void setRealPlayerPos(sf::Vector2f t_realPos);
	sf::Vector2f getPos();
private:
	int normalizeAngle(int t_angle);

	sf::Vector2f position = { 0,0 };
	sf::Vector2f playerPosition = { 0,0 };
	sf::Vector2f newPosition = { 0,0 };
	sf::Vector2f velocity = { 0,0 };
	sf::Vector2f pursuitRealPlayerPos = { 0,0 };

	float speed = 1.0f;
	float friction = 0.8f;
	float acceleration = 1.01f;

	sf::Text NPCNametag;
	sf::Font font;

	sf::CircleShape NPCShape;
	sf::CircleShape VisionCone;

	sf::Sprite NPCSprite;
	sf::Texture NPCTexture;

	BehaviourEnum currentBehaviour = BehaviourEnum::Wander;
	Behaviour NPCBehaviour;
};
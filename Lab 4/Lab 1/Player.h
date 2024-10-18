#pragma once
#include "Globals.h"

class Player
{
public:
	void init();
	void update();
	void render(sf::RenderWindow& t_window);
	void visionCone(sf::Vector2f t_target);
	sf::Vector2f returnPlayerPos();
	sf::Vector2f returnPlayerPredictedPos();
	float rotation = 180.0f;
private:
	int normalizeAngle(int t_angle);
	float rotateToTarget(sf::Vector2f t_target);
	void playerMovement();
	void playerRotation();
	void keepPlayerOnScreen();


	float velocity = 0.0;
	float maxVelocity = 4.0;
	float acceleration = 1.06;
	float decceleration = 0.94;
	float drag = 0.9;
	float rotationSpeed = 1.0f;

	sf::Vector2f position = { 0,0 };

	sf::CircleShape playerShape;
	sf::CircleShape VisionCone;

	sf::Sprite playerSprite;
	sf::Texture playerTexture;
};
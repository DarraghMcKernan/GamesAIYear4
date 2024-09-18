#pragma once
#include "Globals.h"

class NPC
{
public:
	void init();
	void update();
	void render(sf::RenderWindow& t_window);
	void NPCMovement();
	void NPCRotation();
	void keepNPCOnScreen();

private:
	float rotation = 0.0;
	float velocity = 0.0;
	float maxVelocity = 4.0;
	float acceleration = 1.06;
	float decceleration = 0.94;
	float drag = 0.99;

	bool pickNewPosition = true;

	sf::Vector2f position = { 0,0 };

	sf::CircleShape NPCShape;
};
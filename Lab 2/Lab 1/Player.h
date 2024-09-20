#pragma once
#include "Globals.h"

class Player
{
public:
	void init();
	void update();
	void render(sf::RenderWindow& t_window);
	void playerMovement();
	void playerRotation();
	void keepPlayerOnScreen();

	sf::Vector2f returnPlayerPos();

private:
	float rotation = 0.0;
	float velocity = 0.0;
	float maxVelocity = 4.0;
	float acceleration = 1.06;
	float decceleration = 0.94;
	float drag = 0.99;

	sf::Vector2f position = { 0,0 };

	sf::CircleShape playerShape;

	sf::Sprite playerSprite;
	sf::Texture playerTexture;
};
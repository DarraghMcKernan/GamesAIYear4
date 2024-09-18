#include "NPC.h"
#include "random"

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

void NPC::update()
{
	NPCMovement();
	NPCRotation();

	float radians = rotation * 3.14 / 180;

	position.x += sin(radians) * velocity;
	position.y -= cos(radians) * velocity;

	keepNPCOnScreen();

	NPCShape.setRotation(rotation);
	NPCShape.setPosition(position);
}

void NPC::render(sf::RenderWindow& t_window)
{
	t_window.draw(NPCShape);
}

void NPC::NPCMovement()
{
	if (velocity == 0)
	{
		velocity = 0.3;
	}
	velocity *= acceleration;
	if (velocity > maxVelocity)
	{
		velocity = maxVelocity;
	}
}

void NPC::NPCRotation()
{
	if (pickNewPosition == true)
	{
		pickNewPosition = false;
		
		std::random_device rand;
		std::mt19937 gen(rand());
		std::uniform_int_distribution<> distr(0, 360);
		int randomNumber = distr(gen);

		rotation = randomNumber;
	}
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
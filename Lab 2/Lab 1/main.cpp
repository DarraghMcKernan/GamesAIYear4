#ifdef _DEBUG  
#pragma comment(lib,"sfml-graphics-d.lib")  
#pragma comment(lib,"sfml-audio-d.lib")  
#pragma comment(lib,"sfml-system-d.lib")  
#pragma comment(lib,"sfml-window-d.lib")  
#pragma comment(lib,"sfml-network-d.lib")  
#else  
#pragma comment(lib,"sfml-graphics.lib")  
#pragma comment(lib,"sfml-audio.lib")  
#pragma comment(lib,"sfml-system.lib")  
#pragma comment(lib,"sfml-window.lib")  
#pragma comment(lib,"sfml-network.lib")  
#endif  

#include <iostream>
#include <SFML/Graphics.hpp> 

#include "Globals.h"
#include "Player.h"
#include "NPC.h"
#include "BehaviourEnum.h"

void main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y), "AI Lab 2", sf::Style::Default);

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock clock;
	clock.restart();
	
	Player myPlayer;
	NPC seekNPC(sf::Vector2f{ 100, 100 },2.0f,BehaviourEnum::Seek);
	NPC pursueNPC(sf::Vector2f{ 400, 100 },2.0f,BehaviourEnum::Pursue);
	NPC wanderNPC(sf::Vector2f{ 100, 700 },2.0f,BehaviourEnum::Wander);
	NPC arriveNPC(sf::Vector2f{ 800, 700 },2.0f,BehaviourEnum::Arrive);
	NPC arriveSlowNPC(sf::Vector2f{ 1000, 400 },2.0f,BehaviourEnum::ArriveSlow);

	bool seekActive = false;
	bool pursueActive = false;
	bool wanderActive = false;
	bool arriveActive = false;
	bool arriveSlowActive = false;

	int buttonPressCooldown = 0;

	myPlayer.init();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		timeSinceLastUpdate += clock.restart();

		if (timeSinceLastUpdate > timePerFrame)
		{
			myPlayer.update();

			if (buttonPressCooldown > 0)
			{
				buttonPressCooldown--;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && buttonPressCooldown == 0)
			{
				if (seekActive == true)
				{
					seekActive = false;
				}
				else seekActive = true;
				buttonPressCooldown = 10;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && buttonPressCooldown == 0)
			{
				if (pursueActive == true)
				{
					pursueActive = false;
				}
				else pursueActive = true;
				buttonPressCooldown = 10;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && buttonPressCooldown == 0)
			{
				if (wanderActive == true)
				{
					wanderActive = false;
				}
				else wanderActive = true;
				buttonPressCooldown = 10;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && buttonPressCooldown == 0)
			{
				if (arriveActive == true)
				{
					arriveActive = false;
				}
				else arriveActive = true;
				buttonPressCooldown = 10;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && buttonPressCooldown == 0)
			{
				if (arriveSlowActive == true)
				{
					arriveSlowActive = false;
				}
				else arriveSlowActive = true;
				buttonPressCooldown = 10;
			}

			window.clear(sf::Color::Black);
			myPlayer.render(window);

			if (seekActive == true)
			{
				seekNPC.update(myPlayer.returnPlayerPos());
				seekNPC.render(window);
			}
			if (pursueActive == true)
			{
				pursueNPC.update(myPlayer.returnPlayerPredictedPos());
				pursueNPC.render(window);
			}
			if (wanderActive == true)
			{
				wanderNPC.update(myPlayer.returnPlayerPredictedPos());
				wanderNPC.render(window);
			}
			if (arriveActive == true)
			{
				arriveNPC.update(myPlayer.returnPlayerPos());
				arriveNPC.render(window);
			}
			if (arriveSlowActive == true)
			{
				arriveSlowNPC.update(myPlayer.returnPlayerPos());
				arriveSlowNPC.render(window);
			}

			window.display();

			timeSinceLastUpdate = sf::Time::Zero;
		}
	}
}
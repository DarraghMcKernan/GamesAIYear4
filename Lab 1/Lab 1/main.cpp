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

void main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y), "AI Lab 1", sf::Style::Default);

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock clock;
	clock.restart();
	
	Player myPlayer;
	NPC myNPC;

	myPlayer.init();
	myNPC.init();

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
			myNPC.update();


			window.clear(sf::Color::Black);

			myPlayer.render(window);
			myNPC.render(window);

			window.display();

			timeSinceLastUpdate = sf::Time::Zero;
		}
	}
}
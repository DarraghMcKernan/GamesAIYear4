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

#include "globals.h"
#include "Game.h"

void main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE + WINDOW_SIZE / 2, WINDOW_SIZE*0.75), "Cathedral");

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock clock;
	clock.restart();

	Game myGame;
	myGame.init();

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
			myGame.update();

			window.clear(sf::Color::Black);

			myGame.render(window);

			window.display();

			timeSinceLastUpdate = sf::Time::Zero;
		}
	}
}
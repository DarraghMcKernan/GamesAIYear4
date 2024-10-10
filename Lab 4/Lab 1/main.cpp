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
#include "Formation.h"

void main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y), "AI Lab 2", sf::Style::Default);

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock clock;
	clock.restart();
	
	Player myPlayer;
	//NPC seekNPC(sf::Vector2f{ 100, 400 },2.0f,BehaviourEnum::Seek);
	//NPC pursueNPC(sf::Vector2f{ 400, 100 },2.0f,BehaviourEnum::Pursue);
	//NPC wanderNPC(sf::Vector2f{ 600, 400 },2.0f,BehaviourEnum::Wander);
	//NPC arriveNPC(sf::Vector2f{ 800, 700 },2.0f,BehaviourEnum::Arrive);
	//NPC arriveSlowNPC(sf::Vector2f{ 1000, 400 },2.0f,BehaviourEnum::ArriveSlow);

	NPC fighterOne(sf::Vector2f{ 50, 100 }, 2.0f, BehaviourEnum::ArriveSlow);
	NPC fighterTwo(sf::Vector2f{ 100, 100 }, 2.0f, BehaviourEnum::ArriveSlow);
	NPC fighterThree(sf::Vector2f{ 150, 100 }, 2.0f, BehaviourEnum::ArriveSlow);
	NPC fighterFour(sf::Vector2f{ 200, 100 }, 2.0f, BehaviourEnum::ArriveSlow);

	Formation myFormation;

	sf::Text prompt;
	sf::Font font;

	if (!font.loadFromFile("Assets/Fonts/BebasNeue.otf"))
	{
		std::cout << "Error loading font\n";
	}
	prompt.setFont(font);
	prompt.setCharacterSize(30);
	prompt.setString("Toggle enemies using 1-5");

	bool seekActive = false;
	bool pursueActive = false;
	bool wanderActive = false;
	bool arriveActive = false;
	bool arriveSlowActive = false;

	int buttonPressCooldown = 0;

	myPlayer.init();
	myFormation.init();

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
			myFormation.setLeaderPos(myPlayer.returnPlayerPos());

			if (buttonPressCooldown > 0)
			{
				buttonPressCooldown--;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && buttonPressCooldown == 0)
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
			myFormation.render(window);

			if (arriveSlowActive == true)
			{
				fighterOne.update(myFormation.getFormationPoint(0, myPlayer.rotation));
				fighterOne.render(window);

				fighterTwo.update(myFormation.getFormationPoint(1, myPlayer.rotation));
				fighterTwo.render(window);

				fighterThree.update(myFormation.getFormationPoint(2, myPlayer.rotation));
				fighterThree.render(window);

				fighterFour.update(myFormation.getFormationPoint(3, myPlayer.rotation));
				fighterFour.render(window);
			}

			window.draw(prompt);

			window.display();

			timeSinceLastUpdate = sf::Time::Zero;
		}
	}
}
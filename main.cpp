#include <iostream>
#include <map>
#include <cstdlib>
#include <string>
using namespace std;

#include "Level.h"

int main (int argc, const char * argv[])
{	
	map<string, sf::Texture> textures;
	
	Level level(textures, "1");
	
	sf::RenderWindow window(sf::VideoMode(1280, 720), "test");
	
	sf::Clock clock;
	sf::Time previousTick=clock.getElapsedTime();
	sf::Time deltaTime;
	
	sf::Time counter=clock.getElapsedTime();
	int fps=0;
	
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}
		
		deltaTime=clock.getElapsedTime()-previousTick;
		previousTick=clock.getElapsedTime();
		
		fps++;
		counter+=deltaTime;
		if(counter.asSeconds()>=1)
		{
			//cout << fps << endl;
			fps=0;
			counter=sf::Time::Zero;
		}
		
		//UPDATE SECTION
		level.update(deltaTime.asSeconds());
		//UPDATE SECTION
		
		window.clear();
		
		//DRAW SECTION
		level.draw(window);
		//DRAW SECTION
		
		window.display();
	}
}


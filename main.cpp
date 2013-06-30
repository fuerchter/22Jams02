#include <iostream>
#include <map>
#include <cstdlib>
#include <string>
using namespace std;

#include <SFGUI/SFGUI.hpp>

#include "Level.h"

int main (int argc, const char * argv[])
{	
	sfg::SFGUI sfgui;
	sfg::Desktop desktop;

	map<string, sf::Texture> textures;
	
	sf::RenderWindow window(sf::VideoMode(1280, 720), "test");
	
	Level level(textures, "1", window.getSize(), desktop);
	
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
			desktop.HandleEvent(event);
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
		level.update(deltaTime.asSeconds(), window, textures);
		desktop.Update(deltaTime.asSeconds());
		//UPDATE SECTION
		
		window.clear();
		
		//DRAW SECTION
		level.draw(window);
		sfgui.Display(window);
		//DRAW SECTION
		
		window.display();
	}
}


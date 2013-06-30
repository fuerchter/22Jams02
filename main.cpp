#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <string>
using namespace std;

#include "SFML/Audio.hpp"

#include <SFGUI/SFGUI.hpp>

#include "Level.h"

int main (int argc, const char * argv[])
{	
	sfg::SFGUI sfgui;
	sfg::Desktop desktop;

	map<string, sf::Texture> textures;
	map<string, sf::SoundBuffer> sounds;
	
	sf::RenderWindow window(sf::VideoMode(1280, 720), "22Jams02");
	
	int levelCounter=1;
	
	
	ifstream save ("save.txt");
	if (save.is_open())
	{
		string line;
		getline(save,line);
		levelCounter=atoi(line.c_str());
		save.close();
	}
	stringstream s;
	s << levelCounter;
	cout << s.str() << endl;
	Level level(textures, sounds, s.str(), window.getSize(), desktop);
	
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
		if(level.getStatus()==Level::Win)
		{
			levelCounter++;
			if(levelCounter>3)
			{
				levelCounter=3;
				window.close();
			}
			ofstream save;
			save.open ("save.txt");
			stringstream s;
			s << levelCounter;
			save << s.str();
			save.close();
		}
		if(level.getStatus()!=Level::Playing)
		{
			ifstream save ("save.txt");
			if (save.is_open())
			{
				string line;
				getline(save,line);
				levelCounter=atoi(line.c_str());
				save.close();
			}
			stringstream s;
			s << levelCounter;
			desktop.RemoveAll();
			level=Level(textures, sounds, s.str(), window.getSize(), desktop);
		}
		//UPDATE SECTION
		
		window.clear();
		
		//DRAW SECTION
		level.draw(window);
		sfgui.Display(window);
		//DRAW SECTION
		
		window.display();
	}
}


#ifndef LEVEL
#define LEVEL

#include <map>
#include <iostream>
#include <cstdlib>
#include <queue>
using namespace std;

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
using namespace rapidxml;

#include "Map.h"
#include "Wave.h"

class Level
{
public:
	Level(map<string, sf::Texture> &textures, string name);
	void update(float dt);
	void draw(sf::RenderWindow &window);
private:
	Map map_;
	queue<Wave> waves_;
	//sf::Clock clock_;
};

#endif
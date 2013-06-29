#ifndef LEVEL
#define LEVEL

#include <map>
#include <iostream>
#include <cstdlib>
using namespace std;

#include "SFML/Graphics.hpp"

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
using namespace rapidxml;

#include "Map.h"
#include "Wave.h"

class Level
{
public:
	Level(map<string, sf::Texture> &textures, string name);
	void draw(sf::RenderWindow &window);
private:
	Map map_;
	vector<Wave> waves_;
};

#endif
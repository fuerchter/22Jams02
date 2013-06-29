#ifndef MAP
#define MAP

#include <map>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "SFML/Graphics.hpp"

#include "NLTmxMap.h"

class Map
{
public:
Map();
Map(map<string, sf::Texture> &textures, string name);
sf::Vector2u getMapSize();
void draw(sf::RenderWindow &window);

private:
vector<vector<sf::Sprite>> sprites_;
sf::Vector2u mapSize_;

void* loadFile( const char * filename, bool appendNull );
};

#endif
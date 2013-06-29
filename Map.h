#ifndef MAP
#define MAP

#include <map>
#include <cstdlib>
using namespace std;

#include "SFML/Graphics.hpp"

#include "NLTmxMap.h"

class Map
{
public:
Map(map<string, sf::Texture> &textures, string name);
void draw(sf::RenderWindow &window);

private:
vector<vector<sf::Sprite>> sprites_;

void* loadFile( const char * filename, bool appendNull );
};

#endif
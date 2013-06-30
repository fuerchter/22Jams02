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
#include "Building.h"
#include "GuiBuildingChoice.h"
#include "GuiBottomRight.h"

class Level
{
public:
	Level(map<string, sf::Texture> &textures, string name, sf::Vector2u windowSize, sfg::Desktop &desktop);
	sf::FloatRect getViewBounds();
	void update(float dt, sf::RenderWindow &window, map<string, sf::Texture> &textures);
	void draw(sf::RenderWindow &window);
private:
	Map map_;
	queue<Wave> waves_;
	vector<Building> buildings_;
	int gold_;
	sf::View view_;
	int scrollThreshold_;
	int scrollSpeed_;
	sf::Sprite cursor_;
	GuiBuildingChoice guiBuildingChoice_;
	GuiBottomRight guiBottomRight_;
	sf::Clock incomeClock_;
	int incomeClockTime_;
};

#endif
#ifndef LEVEL
#define LEVEL

#include <map>
#include <iostream>
#include <cstdlib>
#include <queue>
using namespace std;

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
using namespace rapidxml;

#include "Map.h"
#include "Wave.h"
#include "Building.h"
#include "BuildingStats.h"
#include "EnemyStats.h"
#include "GuiBuildingChoice.h"
#include "GuiBottomRight.h"
#include "GuiBalancing.h"

class Level
{
public:
	enum Status
	{
		Playing,
		Win,
		Lose
	};
	Level(map<string, sf::Texture> &textures, map<string, sf::SoundBuffer> &sounds, string name, sf::Vector2u windowSize, sfg::Desktop &desktop);
	sf::FloatRect getViewBounds();
	Status getStatus();
	void update(float dt, sf::RenderWindow &window, map<string, sf::Texture> &textures);
	void draw(sf::RenderWindow &window);
private:
	Map map_;
	vector<Wave> waves_;
	vector<Building> buildings_;
	int gold_;
	sf::View view_;
	int scrollThreshold_;
	int scrollSpeed_;
	sf::Sprite cursor_;
	GuiBuildingChoice guiBuildingChoice_;
	GuiBottomRight guiBottomRight_;
	GuiBalancing guiBalancing_;
	GuiBalancing guiBuildingBalancing_;
	GuiBalancing guiEnemyBalancing_;
	sf::Clock incomeClock_;
	int incomeClockTime_;
	sf::Sound waveDefeated_;
	sf::Sound income_;
	int baseDamage_;
	map<Building::BuildingType, BuildingStats> buildingStats_;
	map<Enemy::EnemyType, EnemyStats> enemyStats_;
	Status status_;
};

#endif
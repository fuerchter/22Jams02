#ifndef BUILDING
#define BUILDING

#include <vector>
using namespace std;

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

#include "BuildingStats.h"

class Building
{
public:
	enum BuildingType
	{
		TownCenter,
		House,
		Wall,
		Turret,
		Bank,
		None
	};
	Building(BuildingType type, sf::Vector2i position, map<string, sf::Texture> &textures, sf::Vector2i tileSize, BuildingStats buildingStats);
	//Balancing stuff!
	static sf::IntRect getRect(BuildingType type, sf::Vector2i position);
	static sf::Vector2i getTilesetPosition(BuildingType type);
	BuildingType getType();
	//Balancing stuff!
	int getMoney();
	void setMoney(int amount);
	int getDamagePerSecond();
	void setDamagePerSecond(int amount);
	int decreaseHp(int amount, int maxHp);
	float getSlowing();
	void setSlowing(float amount);
	sf::Vector2i getPosition();
	void draw(sf::RenderWindow &window);
private:
	BuildingType type_;
	int moneyPerMinute_;
	int damagePerSecond_;
	int hp_;
	float slowing_;
	sf::Vector2i position_;
	sf::Sprite sprite_;
	sf::Sprite lifeBar_;
	sf::Vector2i tileSize_;
};

#endif
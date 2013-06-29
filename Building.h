#ifndef BUILDING
#define BUILDING

#include <vector>
using namespace std;

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

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
	Building(BuildingType type, sf::Vector2i position);
	static int getCost(BuildingType type);
	static sf::IntRect getRect(BuildingType type, sf::Vector2i position);
	BuildingType getType();
private:
	BuildingType type_;
	int moneyPerMinute_;
	int damagePerSecond_;
	int hp_;
	int slowing_;
	sf::Vector2i position_;
};

#endif
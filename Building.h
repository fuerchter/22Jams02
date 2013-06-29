#ifndef BUILDING
#define BUILDING

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
	Building(BuildingType type);
	static int getCost(BuildingType type);
	BuildingType getType();
private:
	BuildingType type_;
	int moneyPerMinute_;
	sf::Vector2i size_;
	int damagePerSecond_;
	int hp_;
	int slowing_;
	
};

#endif
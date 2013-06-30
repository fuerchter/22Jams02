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
	Building(BuildingType type, sf::Vector2i position, map<string, sf::Texture> &textures, sf::Vector2i tileSize);
	//Balancing stuff!
	static int getCost(BuildingType type);
	
	static sf::IntRect getRect(BuildingType type, sf::Vector2i position);
	static sf::Vector2i getTilesetPosition(BuildingType type);
	BuildingType getType();
	//Balancing stuff!
	int getMoney();
	
	sf::Vector2i getPosition();
	void draw(sf::RenderWindow &window);
private:
	BuildingType type_;
	int moneyPerMinute_;
	int damagePerSecond_;
	int hp_;
	int slowing_;
	sf::Vector2i position_;
	sf::Sprite sprite_;
};

#endif
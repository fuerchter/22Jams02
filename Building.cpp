#include "Building.h"

Building::Building(BuildingType type, sf::Vector2i position):
type_(type), position_(position)
{
	switch(type_)
	{
	case TownCenter:
		break;
	case House:
		break;
	case Wall:
		break;
	case Turret:
		break;
	case Bank:
		break;
	default:
		break;
	}
}

int Building::getCost(BuildingType type)
{
	switch(type)
	{
	case TownCenter:
		return 10;
		break;
	case House:
		return 10;
		break;
	case Wall:
		return 10;
		break;
	case Turret:
		return 10;
		break;
	case Bank:
		return 10;
		break;
	default:
		return -1;
		break;
	}
}

sf::IntRect Building::getRect(BuildingType type, sf::Vector2i position)
{
	switch(type)
	{
	case TownCenter:
		return sf::IntRect(position.x, position.y, 3, 3);
		break;
	case House:
		return sf::IntRect(position.x, position.y, 2, 2);
		break;
	case Wall:
		return sf::IntRect(position.x, position.y, 3, 1);
		break;
	case Turret:
		return sf::IntRect(position.x, position.y, 1, 1);
		break;
	case Bank:
		return sf::IntRect(position.x, position.y, 4, 4);
		break;
	default:
		return sf::IntRect(-1, -1, -1, -1);
		break;
	}
}

Building::BuildingType Building::getType()
{
	return type_;
}
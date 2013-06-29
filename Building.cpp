#include "Building.h"

Building::Building(BuildingType type):
type_(type)
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
		return 10;
		break;
	}
}

Building::BuildingType Building::getType()
{
	return type_;
}
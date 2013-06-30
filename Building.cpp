#include "Building.h"

Building::Building(BuildingType type, sf::Vector2i position, map<string, sf::Texture> &textures, sf::Vector2i tileSize):
type_(type), position_(position)
{
	switch(type_)
	{
	case TownCenter:
		moneyPerMinute_=5;
		hp_=100;
		damagePerSecond_=0;
		slowing_=0;
		break;
	case House:
		moneyPerMinute_=20;
		hp_=100;
		damagePerSecond_=0;
		slowing_=0;
		break;
	case Wall:
		moneyPerMinute_=0;
		hp_=100;
		damagePerSecond_=0;
		slowing_=1;
		break;
	case Turret:
		moneyPerMinute_=0;
		hp_=100;
		damagePerSecond_=10;
		slowing_=0;
		break;
	case Bank:
		moneyPerMinute_=50;
		hp_=100;
		damagePerSecond_=0;
		slowing_=0;
		break;
	default:
		break;
	}
	
	sprite_=sf::Sprite(textures["assets/buildings.png"]);
	sprite_.setTextureRect(sf::IntRect(getTilesetPosition(type_).x*tileSize.x, getTilesetPosition(type_).y*tileSize.y, getRect(type_, position_).width*tileSize.x, getRect(type_, position_).height*tileSize.y));
	sprite_.setPosition(position_.x*tileSize.x, position_.y*tileSize.y);
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

sf::Vector2i Building::getTilesetPosition(BuildingType type)
{
	switch(type)
	{
	case TownCenter:
		return sf::Vector2i(0, 1);
		break;
	case House:
		return sf::Vector2i(3, 0);
		break;
	case Wall:
		return sf::Vector2i(0, 0);
		break;
	case Turret:
		return sf::Vector2i(0, 0);
		break;
	case Bank:
		return sf::Vector2i(0, 4);
		break;
	default:
		return sf::Vector2i(-1, -1);
		break;
	}
}

Building::BuildingType Building::getType()
{
	return type_;
}

int Building::getMoney()
{
	return moneyPerMinute_;
}

int Building::getDamagePerSecond()
{
	return damagePerSecond_;
}

int Building::decreaseHp(int amount)
{
	return hp_-=amount;
}

float Building::getSlowing()
{
	return slowing_;
}

sf::Vector2i Building::getPosition()
{
	return position_;
}

void Building::draw(sf::RenderWindow &window)
{
	window.draw(sprite_);
}
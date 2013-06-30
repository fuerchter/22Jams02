#include "Building.h"

Building::Building(BuildingType type, sf::Vector2i position, map<string, sf::Texture> &textures, sf::Vector2i tileSize, BuildingStats buildingStats):
type_(type), moneyPerMinute_(buildingStats.moneyPerMinute), damagePerSecond_(buildingStats.damagePerSecond), hp_(buildingStats.maxHp), slowing_(buildingStats.slowing), position_(position)
{	
	sprite_=sf::Sprite(textures["assets/buildings.png"]);
	sprite_.setTextureRect(sf::IntRect(getTilesetPosition(type_).x*tileSize.x, getTilesetPosition(type_).y*tileSize.y, getRect(type_, position_).width*tileSize.x, getRect(type_, position_).height*tileSize.y));
	sprite_.setPosition(position_.x*tileSize.x, position_.y*tileSize.y);
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
		return sf::Vector2i(3, 2);
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

void Building::setMoney(int amount)
{
	moneyPerMinute_=amount;
}

int Building::getDamagePerSecond()
{
	return damagePerSecond_;
}

void Building::setDamagePerSecond(int amount)
{
	damagePerSecond_=amount;
}

int Building::decreaseHp(int amount)
{
	return hp_-=amount;
}

float Building::getSlowing()
{
	return slowing_;
}

void Building::setSlowing(float amount)
{
	slowing_=amount;
}

sf::Vector2i Building::getPosition()
{
	return position_;
}

void Building::draw(sf::RenderWindow &window)
{
	window.draw(sprite_);
}
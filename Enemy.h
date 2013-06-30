#ifndef ENEMY
#define ENEMY

#include "SFML/System.hpp"

class Enemy
{
public:
	enum EnemyType
	{
		Zombie,
		Ghost,
		Godzilla
	};
	Enemy(EnemyType type);
	sf::Clock hitTimer;
	EnemyType getType();
	int decreaseHp(int amount);
	void setHp(int amount);
	float getSecondsPerHit();
	void setSecondsPerHit(float amount);
	int getDamagePerHit();
	void setDamagePerHit(int amount);
private:
	EnemyType type_;
	int hp_;
	float secondsPerHit_;
	int damagePerHit_;
};

#endif
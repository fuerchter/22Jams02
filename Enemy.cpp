#include "Enemy.h"

Enemy::Enemy(EnemyType type):
type_(type)
{
	switch(type_)
	{
	case Zombie:
		hp_=100;
		secondsPerHit_=0.5;
		damagePerHit_=2;
		break;
	case Ghost:
		hp_=60;
		secondsPerHit_=2;
		damagePerHit_=20;
		break;
	case Godzilla:
		hp_=150;
		secondsPerHit_=4;
		damagePerHit_=25;
		break;
	default:
		break;
	}
}

Enemy::EnemyType Enemy::getType()
{
	return type_;
}

int Enemy::decreaseHp(int amount)
{
	return hp_-=amount;
}

float Enemy::getSecondsPerHit()
{
	return secondsPerHit_;
}

int Enemy::getDamagePerHit()
{
	return damagePerHit_;
}
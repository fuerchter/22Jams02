#include "Enemy.h"

Enemy::Enemy(EnemyType type):
type_(type)
{

}

Enemy::EnemyType Enemy::getType()
{
	return type_;
}

int Enemy::decreaseHp(int amount)
{
	return hp_-=amount;
}

void Enemy::setHp(int amount)
{
	hp_=amount;
}

float Enemy::getSecondsPerHit()
{
	return secondsPerHit_;
}

void Enemy::setSecondsPerHit(float amount)
{
	secondsPerHit_=amount;
}

int Enemy::getDamagePerHit()
{
	return damagePerHit_;
}

void Enemy::setDamagePerHit(int amount)
{
	damagePerHit_=amount;
}
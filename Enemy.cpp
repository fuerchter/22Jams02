#include "Enemy.h"

Enemy::Enemy(EnemyType type):
type_(type)
{
	switch(type_)
	{
	case Zombie:
		hp_=100;
		hitsPerSecond_=0.5;
		damagePerHit_=20;
		break;
	case Ghost:
		hp_=60;
		hitsPerSecond_=2;
		damagePerHit_=20;
		break;
	case Godzilla:
		hp_=150;
		hitsPerSecond_=4;
		damagePerHit_=25;
		break;
	default:
		break;
	}
}
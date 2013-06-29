#ifndef ENEMY
#define ENEMY

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
private:
	EnemyType type_;
	int hp_;
	float hitsPerSecond_;
	int damagePerHit_;
};

#endif
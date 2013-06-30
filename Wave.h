#ifndef WAVE
#define WAVE

#include <iostream>
#include <vector>
using namespace std;

#include "Enemy.h"

class Wave
{
public:
	Wave(float timeInSeconds, vector<int> enemies);
	float getTimeInSeconds();
	vector<Enemy> getEnemies();
	vector<int> getEnemyTypes();
	int update(float dt, int damageTaken=0, int slowing=0);
private:
	float timeInSeconds_;
	vector<Enemy> enemies_;
	vector<int> enemyTypes_;
	sf::Clock takenDamageTimer_;
};

#endif
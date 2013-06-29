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
	vector<int> getEnemyTypes();
	void update(float dt);
private:
	float timeInSeconds_;
	vector<Enemy> enemies_;
	vector<int> enemyTypes_;
};

#endif
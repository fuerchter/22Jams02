#include "Wave.h"

Wave::Wave(float timeInSeconds, vector<int> enemies):
timeInSeconds_(timeInSeconds)
{
	for(int enemyIndex=0; enemyIndex<enemies.size(); enemyIndex++)
	{
		for(int enemyAmount=0; enemyAmount<enemies[enemyIndex]; enemyAmount++)
		{
			enemies_.push_back(Enemy((Enemy::EnemyType)enemyIndex));
		}
	}
}

float Wave::getTimeInSeconds()
{
	return timeInSeconds_;
}

void Wave::update(float dt)
{
	cout << "Next wave: " << timeInSeconds_ << endl;
	timeInSeconds_-=dt;
}
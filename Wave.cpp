#include "Wave.h"

Wave::Wave(float timeInSeconds, vector<int> enemies):
timeInSeconds_(timeInSeconds), enemyTypes_(enemies)
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

vector<Enemy>Wave::getEnemies()
{
	return enemies_;
}

vector<int> Wave::getEnemyTypes()
{
	return enemyTypes_;
}

void Wave::changeEnemyStats(map<Enemy::EnemyType, EnemyStats> enemyStats, bool first)
{
	for(vector<Enemy>::iterator enemyIt=enemies_.begin(); enemyIt!=enemies_.end(); enemyIt++)
	{
		if(!first)
		{
			enemyIt->setHp(enemyStats[enemyIt->getType()].hp);
		}
		enemyIt->setSecondsPerHit(enemyStats[enemyIt->getType()].secondsPerHit);
		enemyIt->setDamagePerHit(enemyStats[enemyIt->getType()].damagePerHit);
	}
}

int Wave::update(float dt, int damageTaken, int slowing)
{
	int damage=0;
	if(timeInSeconds_>0)
	{
		timeInSeconds_-=dt;
	}
	else
	{
		for(vector<Enemy>::iterator enemyIt=enemies_.begin(); enemyIt!=enemies_.end(); enemyIt++)
		{
			float secondsPerHit=enemyIt->getSecondsPerHit();
			if(enemyIt->getType()!=Enemy::Ghost)
			{
				secondsPerHit+=slowing;
			}
			
			//cout << enemyIt->hitTimer.getElapsedTime().asSeconds() << endl;
			//If the enemy cooldown is over, increases damage
			if(enemyIt->hitTimer.getElapsedTime().asSeconds()>=secondsPerHit)
			{
				damage+=enemyIt->getDamagePerHit();
				enemyIt->hitTimer.restart();
			}
			
			//If one second has passed attack enemy and erase if dead
			if(takenDamageTimer_.getElapsedTime().asSeconds()>=1)
			{
				//cout << "Enemy HP: " << enemyIt->decreaseHp(0) << endl;
				if(enemyIt->decreaseHp(damageTaken)<=0)
				{
					//Updating information ui
					enemyTypes_[enemyIt->getType()]--;
					
					enemies_.erase(enemyIt);
					enemyIt--;
				}
			}
		}
		if(takenDamageTimer_.getElapsedTime().asSeconds()>=1)
		{
			takenDamageTimer_.restart();
		}
	}
	return damage;
}
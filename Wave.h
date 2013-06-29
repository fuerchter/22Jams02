#ifndef WAVE
#define WAVE

#include <vector>
using namespace std;

#include "Enemy.h"

class Wave
{
public:
	Wave(float timeInSeconds, vector<int> enemies);
private:
	float timeInSeconds_;
	vector<Enemy> enemies_;
};

#endif
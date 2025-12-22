#include "Enemy.h"
#include "Character.h"

using namespace std;

int Enemy::nEnemies_ = 0;

Enemy::Enemy(int health, int maxHealth, bool usedUlt, const string& type, bool debuffed, int atk1, int atk2, int enemyUlt) :
    Entity(type, health, maxHealth), usedUlt_(usedUlt), atk1_(atk1), atk2_(atk2), enemyUlt_(enemyUlt)
{
    nEnemies_++;
}

Enemy::~Enemy()
{
    nEnemies_--;
}

bool Enemy::getUltUsed()
{
    return usedUlt_;
}

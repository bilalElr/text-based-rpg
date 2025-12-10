#include "Enemy.h"
#include "Character.h"

using namespace std;

int Enemy::nEnemies_ = 0;

Enemy::Enemy(int health, int maxHealth, const string& type, bool debuffed, int atk1, int atk2) :
    Entity(type, health, maxHealth), atk1_(atk1), atk2_(atk2)
{
    nEnemies_++;
}

Enemy::~Enemy()
{
    nEnemies_--;
}



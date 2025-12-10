#pragma once

#include <memory>
#include <string>
#include "Entity.h"

using namespace std;

class Character;

class Enemy : public Entity
{
public:

	Enemy(int health, int maxHealth, const string& type, bool debuffed,
		int atk1, int atk2);
	virtual ~Enemy();

	
	virtual int getAtk1() const = 0;
	virtual int getAtk2() const = 0;
	virtual string getAttack1() const = 0;
	virtual string getAttack2() const = 0;

	virtual void atk1(Character& c) = 0;
	virtual void atk2(Character& c) = 0;

protected:
	
	int atk1_, atk2_;
	string attack1, attack2;

private:
	static int nEnemies_;
};
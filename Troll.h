#pragma once

#include "Enemy.h"
#include "Character.h"

using namespace std;

class Troll : public Enemy
{
public:

	Troll(int ultDmg);
	void trollUlt();
	void atk1(Character& c) override;
	void atk2(Character& c) override;

	int getAtk1() const override;
	int getAtk2() const override;
	string getAttack1() const override;
	string getAttack2() const override;
	int getUltDmg() const;

private:
	int ultDmg_;
};
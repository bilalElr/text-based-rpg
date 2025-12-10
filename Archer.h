#pragma once

#include "Character.h"
#include "Enemy.h"

using namespace std;

class Archer : public Character
{
public:

	Archer();
	void ultimate(Enemy& e, vector<unique_ptr<Character>>& p) override;

	void light(Enemy& e) override;
	void heavy(Enemy& e) override;
	//void ultimate(Enemy& e);

	int getLightDmg() const override;
	int getHeavyDmg() const override;
	int getUltDmg() const override;
	string getUltDescription() const override;

};
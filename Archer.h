#pragma once

#include "Character.h"
#include "Enemy.h"

using namespace std;

class Archer : public Character
{
public:

	Archer();
	//Archer(const Archer& copy) = default;
	void ultimate(Enemy& e, vector<unique_ptr<Character>>& p) override;

	void light(Enemy& e) override;
	void heavy(Enemy& e) override;

	int getLightDmg() const override;
	int getHeavyDmg() const override;
	int getUltDmg() const override;
	string getUltDescription() const override;

	//unique_ptr<Character> clone() const override;
};
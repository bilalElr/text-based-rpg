#pragma once

#include "Character.h"
#include "Enemy.h"
#include <algorithm>
#include "CheckInput.h"

using namespace std;

class Mage : public Character
{
public:

	Mage();
	//Mage(const Mage& copy) = default;
	void ultimate(Enemy& e, vector<unique_ptr<Character>>& p) override;
	
	void light(Enemy& e) override;
	void heavy(Enemy& e) override;
	
	int getLightDmg() const override;
	int getHeavyDmg() const override;
	int getUltDmg() const override;
	string getUltDescription() const override;

	void heal(Character& target, int amount);

	//unique_ptr<Character> clone() const override;
};
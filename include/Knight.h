#pragma once

#include "character.h"
#include "Enemy.h"
#include <string>

using namespace std;

class Knight : public Character
{
public:

	Knight();
	//Knight(const Knight& copy) = default;
	void ultimate(Enemy& e, vector<unique_ptr<Character>>& p) override;

	void light(Enemy& e) override;
	void heavy(Enemy& e) override;
	
	int getLightDmg() const override;
	int getHeavyDmg() const override;
	int getUltDmg() const override;
	string getUltDescription() const override;

	//unique_ptr<Character> clone() const override;
};
#include "Knight.h"

using namespace std;

Knight::Knight():
	Character("Knight", 500, 500, 35, 45, 80, 2, 5)
{
	lightCooldown_ = 2;
	heavyCooldown_ = 5;
}

void Knight::light(Enemy& e)
{
	e.takeDamage(35);
}

void Knight::heavy(Enemy& e)
{
	e.takeDamage(45);
	if (randomNumberGenerator(1, 100) <= 30) {
		e.applyDebuff(Debuff::Dazed, 2);
		cout << "Heavy attack inflicted daze for 2 turns!\n";
	}
}

void Knight::ultimate(Enemy& e, vector<unique_ptr<Character>>& p)
{
	e.setIgnoreDodge(true);
	e.takeDamage(80);
	e.setIgnoreDodge(false);

	e.applyDebuff(Debuff::Dazed, 5);
	ultUsed_ = true;
}

int Knight::getLightDmg() const
{
	return lightDmg_;
}

int Knight::getHeavyDmg() const
{
	return heavyDmg_;
}

int Knight::getUltDmg() const
{
	return ultDmg_;
}

string Knight::getUltDescription() const
{
	return "The ult will deal 80 damage and daze the enemy for the next 5 turns\n";
}

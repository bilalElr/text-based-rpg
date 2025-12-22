#include "Archer.h"

using namespace std;

Archer::Archer() :
Character("Archer", 400, 400, 20, 30, 60, 1, 2)
{
	lightCooldown_ = 1;
	heavyCooldown_ = 2;
}

void Archer::light(Enemy& e)
{
	e.takeDamage(20);
}

void Archer::heavy(Enemy& e)
{
	int currentHealth = e.getHealth();
	e.takeDamage(30);
	if ((randomNumberGenerator(1, 100) <= 10) && currentHealth != e.getHealth()) {
		e.applyDebuff(Debuff::Bleeding, 2);
		cout << "Heavy attack inflicted bleed for 2 turns!\n";
	}
}

void Archer::ultimate(Enemy& e, vector<unique_ptr<Character>>& p)
{
	e.setIgnoreDodge(true);
	e.takeDamage(60);
	e.setIgnoreDodge(false);

	e.applyDebuff(Debuff::Bleeding, 5);
	ultUsed_ = true;
}

int Archer::getLightDmg() const
{
	return lightDmg_;
}

int Archer::getHeavyDmg() const
{
	return heavyDmg_;
}

int Archer::getUltDmg() const
{
	return ultDmg_;
}

string Archer::getUltDescription() const
{
	return "The ult will shoot an arrow that deals 60 damage and will inflict bleeding for 5 turns\n";
}

//unique_ptr<Character> Archer::clone() const
//{
//	return make_unique<Archer>(*this);
//}

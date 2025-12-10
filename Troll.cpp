#include "Troll.h"

using namespace std;

Troll::Troll(int ultDmg):
	Enemy(1000, 1000, "Troll", false, 40, 50), ultDmg_(ultDmg)
{
}

void Troll::trollUlt()
{

}

void Troll::atk1(Character& c)
{
	c.takeDamage(40);
}

void Troll::atk2(Character& c)
{
	c.takeDamage(55);
}

int Troll::getAtk1() const
{
	return atk1_;
}

int Troll::getAtk2() const
{
	return atk2_;
}

string Troll::getAttack1() const
{
	return "Ground Pound";
}

string Troll::getAttack2() const
{
	return "Throw rock";
}

int Troll::getUltDmg() const
{
	return ultDmg_;
}
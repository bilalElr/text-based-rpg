#include "Goblin.h"

using namespace std;

Goblin::Goblin():
	Enemy(100, 100, "Goblin", false, 10, 20)
{
}

void Goblin::atk1(Character& c)
{
	c.takeDamage(10);
}

void Goblin::atk2(Character& c)
{
	c.takeDamage(20);
}

int Goblin::getAtk1() const
{
	return atk1_;
}

int Goblin::getAtk2() const
{
	return atk2_;
}

string Goblin::getAttack1() const
{
	return "Claw";
}

string Goblin::getAttack2() const
{
	return "Poisonous spit";
}

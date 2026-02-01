#include "Goblin.h"

using namespace std;

Goblin::Goblin():
	Enemy(100, 100, false, "Goblin", false, 20, 30, 45)
{
}

void Goblin::atk1(Character& c)
{
	c.takeDamage(20);
}

void Goblin::atk2(Character& c)
{
	c.takeDamage(30);
}

void Goblin::enemyUlt(Character& c)
{
	c.takeDamage(45);
	c.applyDebuff(Debuff::Petrified, 3);
	cout << endl << getUltDesc() << " inclficted petrify for 3 turns!\n";
	usedUlt_ = true;
}

int Goblin::getAtk1() const
{
	return atk1_;
}

int Goblin::getAtk2() const
{
	return atk2_;
}

int Goblin::getEnemyUlt() const
{
	return enemyUlt_;
}

string Goblin::getAttack1() const
{
	return "Claw";
}

string Goblin::getAttack2() const
{
	return "Poisonous spit";
}

string Goblin::getUltDesc() const
{
	return "Fit of rage";
}

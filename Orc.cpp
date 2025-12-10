#include "Orc.h"

Orc::Orc():
	Enemy(200, 200, "Orc", false, 15, 25)
{
}

void Orc::atk1(Character& c)
{
	c.takeDamage(15);
	if (randomNumberGenerator(1, 100) <= 5) {
		c.applyDebuff(Debuff::Bleeding, 2);
		cout << getAttack1() << " inflicted bleeding damage for 2 turns!\n";
	}
}

void Orc::atk2(Character& c)
{
	c.takeDamage(25);
	if (randomNumberGenerator(1, 100) <= 10) {
		c.applyDebuff(Debuff::Dazed, 2);
		cout << getAttack2() << " inflicted daze for 2 turns!\n";
	}
}

int Orc::getAtk1() const
{
	return atk1_;
}

int Orc::getAtk2() const
{
	return atk2_;
}

string Orc::getAttack1() const
{
	return "Throw spear.";
}

string Orc::getAttack2() const
{
	return "Swing club";
}

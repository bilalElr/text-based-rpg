#include "Orc.h"

Orc::Orc():
	Enemy(200, 200, false, "Orc", false, 25, 35, 55)
{
}

void Orc::atk1(Character& c)
{
	int currentHealth = c.getHealth();
	c.takeDamage(25);
	if ((randomNumberGenerator(1, 100) <= 5) && currentHealth != c.getHealth()) {
		c.applyDebuff(Debuff::Bleeding, 2);
		cout << getAttack1() << " inflicted bleeding damage for 2 turns!\n";
	}
}

void Orc::atk2(Character& c)
{
	int currentHealth = c.getHealth();
	c.takeDamage(35);
	if ((randomNumberGenerator(1, 100) <= 10) && currentHealth != c.getHealth()) {
		c.applyDebuff(Debuff::Dazed, 2);
		cout << getAttack2() << " inflicted daze for 2 turns!\n";
	}
}

void Orc::enemyUlt(Character& c)
{
	c.takeDamage(55);
	c.applyDebuff(Debuff::Petrified, 3);
	cout << endl << getUltDesc() << " inflicted petirfy for 3 turns!\n";
	usedUlt_ = true;
}

int Orc::getAtk1() const
{
	return atk1_;
}

int Orc::getAtk2() const
{
	return atk2_;
}

int Orc::getEnemyUlt() const
{
	return enemyUlt_;
}

string Orc::getAttack1() const
{
	return "Throw spear";
}

string Orc::getAttack2() const
{
	return "Swing club";
}

string Orc::getUltDesc() const
{
	return "Barrage of hits";
}

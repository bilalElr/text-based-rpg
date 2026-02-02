#include "Werewolf.h"

using namespace std;

Werewolf::Werewolf():
	Enemy(350, 350, false, "Werewolf", false, 35, 45, 70)
{
}

void Werewolf::atk1(Character& c)
{
	int currentHealth = c.getHealth();
	c.takeDamage(35);
	if ((randomNumberGenerator(1, 100) <= 10) && currentHealth != c.getHealth()) {
		c.applyDebuff(Debuff::Bleeding, 2);
		cout << getAttack1() << " inflicted bleeding for 2 turns!\n";
	}
}

void Werewolf::atk2(Character& c)
{
	int currentHealth = c.getHealth();
	c.takeDamage(45);
	if ((randomNumberGenerator(1, 100) <= 15) && currentHealth != c.getHealth()) {
		c.applyDebuff(Debuff::Bleeding, 2);
		cout << getAttack2() << " inflicted bleeding for 2 turns!\n";
	}
}

void Werewolf::enemyUlt(Character& c)
{
	c.takeDamage(70);
	c.applyDebuff(Debuff::Petrified, 3);
	cout << endl << getUltDesc() << " inflicted petrify for 3 turns!\n";
	usedUlt_ = true;
}

int Werewolf::getAtk1() const
{
	return atk1_;
}

int Werewolf::getAtk2() const
{
	return atk2_;
}

int Werewolf::getEnemyUlt() const
{
	return 70;
}

string Werewolf::getAttack1() const
{
	return "Claw";
}

string Werewolf::getAttack2() const
{
	return "Bite";
}

string Werewolf::getUltDesc() const
{
	return "Maul";
}
